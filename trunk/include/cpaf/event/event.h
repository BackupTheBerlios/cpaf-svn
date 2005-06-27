/*!
    \file include/cpaf/event/event.h
    \brief Declarations for the event system
    \date Created: 2005-05-29
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
class Manager;

/*!
    This function generates a unique event id.
    \return A unique event id
*/
int get_unique_id();

//! Helper macro for the declaration of event ids in header files
#define CPAF_DECLARE_EXPORTED_EVENT(name)    CPAF_API extern const int name;

//! Helper macro for implementing event ids in source files
#define CPAF_IMPLEMENT_EXPORTED_EVENT(name)  const int name = cpaf::event::get_unique_id();

// event declarations
CPAF_DECLARE_EXPORTED_EVENT(WIDGET_CREATE);
CPAF_DECLARE_EXPORTED_EVENT(WIDGET_DESTROY);
CPAF_DECLARE_EXPORTED_EVENT(BUTTON_CLICK);

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
    object_id m_obj_id;
    bool m_continue;

public:
    /*!
        Construct an event with the given event_id \a id being sent from the object \a obj
    */
    Event(event_id id, object_id obj);

    virtual ~Event() { }

    /*!
        \return The id of this event
    */
    event_id get_id() { return m_id; }

    /*!
        \return The id of the object sending this event
    */
    object_id get_object_id() { return m_obj_id; }

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
    Main event system object. Manages sending events and connecting listeners which form chains.
*/
class CPAF_API Manager
{
    template<typename Event, bool After, typename Listener> friend EventChainWrapper<Event> connect(event_id event, object_id object, Listener &l, typename ListenerFunctor<Listener, Event>::ptr_type function);

private:
    // storage related typedefs
    typedef std::vector<event_chain_ptr> event_chain_vector;
    typedef std::map<event_id, event_chain_vector> event_vector_map;
    typedef std::map<object_id, event_chain_vector> object_vector_map;
    typedef std::map<object_id, event_vector_map> object_event_vector_map;

    // there are two of each map, one for regular event chains, and one for "post processing" chains
    static const int BEFORE_MAP;
    static const int AFTER_MAP;

    // {object, event, chain} map
    object_event_vector_map m_obj_evt_map[2];

    // {[any], event, chain} map
    event_vector_map m_evt_map[2];

    // {object, [any], chain} map
    object_vector_map m_obj_map[2];

public:
    Manager();

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
    void send_event(Event &e);

private:
    void send_event(event_chain_vector &chain, Event &e);
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
        m_chain.connect(new ListenerFunctor<L,E>(l, function));
        return *this;
    }
};

/*!
    Return an reference to the main threads Manager object
*/
CPAF_API cpaf::event::Manager &get_manager();

/*!
    This is a convenience function which allows you to more easliy connect events.

    Template parameters:
    Event       Event type being connected
    After       True if you want to recieve the event after it has been processed by the normal event listeners
    Listener    The Object connecting the event

    \param l Listening object connecting this event
    \param event Id of the event
    \param object The object to recieve events from
    \param function The listening function
*/
template<typename Event, bool After, typename Listener> EventChainWrapper<Event> connect(event_id event, object_id object, Listener &l, typename ListenerFunctor<Listener, Event>::ptr_type function)
{
    ListenerFunctor<Listener, Event> *functor = new ListenerFunctor<Listener, Event>(l, function);
    return EventChainWrapper<Event>(cpaf::event::get_manager().create_event_chain(object, event, After).connect(functor));
}

    } // event
} // cpaf

#endif // CPAF_EVENT_H
