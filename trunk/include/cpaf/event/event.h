/*
    cpaf event system declarations
*/

#ifndef CPAF_EVENT_H
#define CPAF_EVENT_H

#include <cpaf/dllimpexp.h>

#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace cpaf {
    namespace event {

// prototypes
class ListenerFunctorBase;
class EventChain;
template<typename E> class EventChainWrapper;

/*!
    This function generates a unique event id.
    \return A unique event id
*/
int get_unique_id();

//! Helper macro for the declaration of event ids in header files
#define CPAF_DECLARE_EVENT(name)    CPAF_API extern const int name;

//! Helper macro for implementing event ids in source files
#define CPAF_IMPLEMENT_EVENT(name)  const int name = cpaf::event::get_unique_id();


CPAF_DECLARE_EVENT(foo);

//! \todo decide wether we use addresses or object id's here
typedef int object_id; // value specifying which object sent the event
typedef int event_id; // event identifier
typedef boost::shared_ptr<EventChain> event_chain_ptr;

const event_id EVENT_ID_ANY     = 0;
const object_id OBJECT_ID_ANY   = 0;

class CPAF_API Event
{
private:
    event_id m_id;
    bool m_continue;

public:
    /*!
        Construct an event with the given event_id \a id
    */
    Event(event_id id);

    virtual ~Event() { }

    /*!
        \return The id of this event
    */
    event_id get_id() { return m_id; }

    /*!
        Specify wether or not processing of this event continue to further links in the event chain.
        If you do not wish an event to be processed further, you do not need to do anything. To allow
        further links in the chain to process the event, specify true to this function.
    */
    void continue_processing(bool c = true) { m_continue = c; }

    /*!
        \return Wether or not processing of this event will continue down the event chain
    */
    bool should_continue() { return m_continue; }
};

/*!
    Base functor class providing a virtual operator().
*/
class ListenerFunctorBase
{
public:

    /*!
        Virtual dtor
    */
    virtual ~ListenerFunctorBase() { }

    /*!
        Invoke the event listener
    */
    virtual void operator() (Event &e) = 0;

};

/*!
    Templated specialization of the base functor class for type safety
*/
template<typename L, typename E> class ListenerFunctor : public ListenerFunctorBase
{
public:
    typedef void(L::*ptr_type)(Event &e); // the function pointer for this functor
    typedef Event event_type; // the type of event that this functor works with

private:
    ptr_type m_ptr;
    L &m_listener;

public:
    ListenerFunctor(L &listener, ptr_type function)
        : m_ptr(function),
        m_listener(listener)
    { }

    /*!
        Invokes the event listener function via the function pointer.
        Type safety is gaurenteed via dynamic_cast.
    */
    void operator() (Event &e)
    {
        (m_listener.*m_ptr)(dynamic_cast<E&>(e));
    }
};

/*!
    Main event system object. Manages sending events and connecting listeners which form chains.
*/
class CPAF_API Manager
{
private:
    // storage related typedefs
    typedef std::vector<event_chain_ptr> event_chain_vector;
    typedef std::map<event_id, event_chain_vector> event_vector_map;
    typedef std::map<object_id, event_chain_vector> object_vector_map;
    typedef std::map<object_id, event_vector_map> object_event_vector_map;

    // there are two of each map, one for regular event chains, and one for "post processing" chains
    static const int BEFORE_MAP = 0;
    static const int AFTER_MAP = 1;

    // {object, event, chain} map
    object_event_vector_map m_obj_evt_map[2];

    // {[any], event, chain} map
    event_vector_map m_evt_map[2];

    // {object, [any], chain} map
    object_vector_map m_obj_map[2];

public:
    /*!
        Creates an EventChain object to connect event listeners to.
        
        \param from     Object to recieve events from
        \param event_id Event id to recieve
        \param after    If true, this event chain will be a "post processing" event chain. If false,
                        it is a regular event chain. "Post processing" event chains will recieve events
                        only after all regular event chains have processed the event.

        \return Reference to the EventChain object.
    */
    EventChain &create_event_chain(object_id from, event_id id, bool after = false);

    /*!
        Sends an event
    */
    void send_event(object_id from, Event &e);

    /*!
        Templated wrapper around the create_event_chain function used
        to create an EventChain wrapped in a templated wrapper to allow
        for convenient type safety in the events system.
    */
    template<typename E> EventChainWrapper<E> create_event_chain(object_id from, event_id id, bool after = false)
    {
        return EventChainWrapper<E>(create_event_chain(from, id));
    }

    /*!
        This is a convenience function which allows you to more easliy create an event chain with only
        one listener.

        Template params:
        L   Object connecting the event
        E   Event type being connected

        \param from Object to recieve events from
        \param id   ID of the event to recieve
        \param l Listening object connecting this event
        \param function The listening function

    */
    template<typename E, typename L> void connect(object_id from, event_id id, L &l, typename ListenerFunctor<L, E>::ptr_type function)
    {
        EventChain &chain = create_event_chain(from, id, false);
        LisaaaaaaaaatenerFunctor<L,E> *functor = new ListenerFunctor<L,E>(l, function);
        chain.connect(functor);
    }

    /*!
        This is a convenience function which allows you to more easliy create an event chain with only
        one listener. It creates a "post processing" event chain.

        Template params:
        L   Object connecting the event
        E   Event type being connected

        \param from Object to recieve events from
        \param id   ID of the event to recieve
        \param l Listening object connecting this event
        \param function The listening function
    */
    template<typename E, typename L> void connect_after(object_id from, event_id id, L &l, typename ListenerFunctor<L, E>::ptr_type function)
    {
        EventChain &chain = create_event_chain(from, id, true);
        ListenerFunctor<L,E> *functor = new ListenerFunctor<L,E>(l, function);
        chain.connect(functor);
    }

private:
    void send_event(event_chain_vector &chain, Event &e);
};

/*!
    Represents a chain of event listeners
*/
class CPAF_API EventChain
{
    friend class Manager;

private:
    typedef boost::shared_ptr<ListenerFunctorBase> functor_ptr_type;
    typedef std::vector<functor_ptr_type> listener_vector_type;    
    listener_vector_type m_listeners;

    Manager *m_manager;

    object_id m_object_id; // the object that this eventchain recieves events from
    event_id m_event_id; // the event id that this eventchain recieves events from

    /*
        Private constructor for use via the friended Manager class
    */
    EventChain(Manager *manager, object_id object, event_id event);

public:
    /*!
        \return The event id that this chain recieves events for
    */
    event_id get_event_id() { return m_event_id; }

    /*!
        \return The object that this event chain recieves events from
    */
    object_id get_object_id() { return m_object_id; }

    /*!
        Process an event.
    */
    void process_event(Event &e);

    /*!
        Connect an event listener
    */
    EventChain &connect(ListenerFunctorBase *func);
};

/*!
    A templated wrapper around the EventChain class to allow for clean, typesafe code
*/
template<typename E> class EventChainWrapper
{
private:
    EventChain &m_chain;

public:

    /*!
        Construct a wrapper around an EventChain object
    */
    EventChainWrapper(EventChain &chain)
      : m_chain(chain)
    { }

    /*!
        Templated wrapper around the EventChain::connect function. This function is used to
        cleany create a ListenerFunctor which will provide type-safety to event
        processing.

        Template params:
        L   Object connecting the event

        \param l Listening object connecting this event
        \param function The listening function
    */
    template<typename L> EventChainWrapper<E> &connect(L &l, typename ListenerFunctor<L, E>::ptr_type function)
    {
        ListenerFunctor<L,E> *functor = new ListenerFunctor<L,E>(l, function);
        m_chain.connect(functor);
        return *this;
    }
};

    } // event
} // cpaf

#endif // CPAF_EVENT_H
