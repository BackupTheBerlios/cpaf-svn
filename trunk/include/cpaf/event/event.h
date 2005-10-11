/*!
    \file include/cpaf/event/event.h
    \brief Declarations for the event system
    \date Created: 2005-05-29
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CPAF_EVENT_H
#define CPAF_EVENT_H

#include <cpaf/dllimpexp.h>
#include <cpaf/event/id.h>
#include <cpaf/types.h>

#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace cpaf {
    namespace event {

// prototypes
class Slot;
class EventChain;
class Manager;

template<typename E> class EventChainWrapper;
template<typename L, typename E> class SafeSlot;

/*!
    Return an reference to the main threads Manager object
*/
CPAF_API cpaf::event::Manager &get_manager();

typedef boost::shared_ptr<EventChain> event_chain_ptr;

const event_id EVENT_ID_ANY = 0;
const object_id OBJECT_ID_ANY = 0;

class CPAF_API Event
{
public:
    /*!
        Construct an event with the given event_id \a id being sent from the object \a obj
    */
    Event(event_id id, object_id obj);

    /*!
        Copy constructors are needed for all event types because event objects must
        be duplicated during internal event processing.

        \todo This copying process is candidate for a memory pooling optimization to avoid
        the overhead of too many heap allocations.
    */
    Event(const Event &other)
        : m_id(other.m_id),
        m_obj_id(other.m_obj_id),
        m_continue(other.m_continue)
    { }

    virtual ~Event() { }

    /*!
        Creates a clone of this event All event derivatives must implement their own
        version of this function because event objects must be duplicated during
        interal event processing.

        \todo This can be optimized by utilizing a memory pool allocation strategy
    */
    virtual Event *clone()
    {
        return new Event(*this);
    }

    /*!
        \return The id of this event
    */
    event_id get_id() { return m_id; }

    /*!
        \return The id of the object sending this event
    */
    object_id get_object_id() { return m_obj_id; }

    /*!
        Specify whether or not processing of this event continue to further links in the event chain.
        If you do not wish an event to be processed further, you do not need to do anything. To allow
        further links in the chain to process the event, specify true to this function.
    */
    void continue_processing(bool c = true) { m_continue = c; }

    /*!
        \return Whether or not processing of this event will continue down the event chain
    */
    bool should_continue() { return m_continue; }

private:
    event_id m_id;
    object_id m_obj_id;
    bool m_continue;
};

/*!
    Base functor class providing a virtual operator().
*/
class Slot
{
public:

    /*!
        Virtual dtor
    */
    virtual ~Slot() { }

    /*!
        Invoke the event listener
    */
    virtual void operator() (Event &e) = 0;

};

/*!
    Represents a chain of event listeners
*/
class CPAF_API EventChain
{
    friend class Manager;

private:
    typedef boost::shared_ptr<Slot> slot_type;
    typedef std::vector<slot_type> slot_chain_type;
    slot_chain_type m_slots;

    Manager *m_manager;

    object_id m_object_id; // the object that this eventchain recieves events from
    event_id m_event_id; // the event id that this eventchain recieves events from

    /*!
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
        Add a slot to this event chain.
    */
    EventChain &connect(Slot *func);
};



/*!
    Main event system object. Manages sending events and connecting listeners which form chains.
*/
class CPAF_API Manager
{
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

    // {event, chain} map
    event_vector_map m_evt_map[2];

    // {object, chain} map
    object_vector_map m_obj_map[2];

    void send_event(event_chain_vector &chain, Event &e);
};

/*!
    This is a convenience function which allows you to more easliy connect events. The purpose of this
    function is to create a templated wrapper around an EventChain object which you use to add
    event listeners forming a chain. Example usage:

    // connect one listener
    connect<Event, false>(WIDGET_CREATE, OBJECT_ID_ANY) (*this, &Foo::on_create);

    // connect two listeners
    connect<Event, false>(WIDGET_CREATE, OBJECT_ID_ANY) (*this, &Foo::on_create) (*this, &Foo::on_create2);

    Template parameters:
    Event       Event type being connected
    After       True if you want to recieve the event after it has been processed by the normal event listeners

    \param event    Id of the event
    \param object   The object to recieve events from
    \param manager  An event manager to connect to
*/
template<typename Event, bool After> EventChainWrapper<Event> connect(event_id event, object_id object, cpaf::event::Manager &manager = cpaf::event::get_manager())
{
    return EventChainWrapper<Event>(manager.create_event_chain(object, event, After));
}

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
    template<typename L> EventChainWrapper<E> &operator()(typename SafeSlot<L, E>::ptr_type function, L &l)
    {
        m_chain.connect(new SafeSlot<L,E>(l, function));
        return *this;
    }
};

/*!
    Templated specialization of the base functor class for type safety
*/
template<typename L, typename E> class SafeSlot : public Slot
{
public:
    typedef void(L::*ptr_type)(Event &e); // the function pointer for this functor
    typedef Event event_type; // the type of event that this functor works with

private:
    ptr_type m_ptr;
    L &m_listener;

public:
    SafeSlot(L &listener, ptr_type function)
        : m_ptr(function),
        m_listener(listener)
    { }

    /*!
        Invokes the slot via the function pointer.
        Type safety is gaurenteed via dynamic_cast.
    */
    void operator() (Event &e)
    {
        (m_listener.*m_ptr)(dynamic_cast<E&>(e));
    }
};

    } // event
} // cpaf

#endif // CPAF_EVENT_H
