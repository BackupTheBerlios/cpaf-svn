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
class SlotChain;
class Manager;

template<typename E> class SlotChainWrapper;
template<typename L, typename E> class SafeSlot;

/*!
    Return an reference to the main threads Manager object
*/
CPAF_API cpaf::event::Manager &get_manager();

typedef boost::shared_ptr<SlotChain> slot_chain_ptr;

const event_id EVENT_ID_ANY = 0;
const object_id OBJECT_ID_ANY = 0;

/*!
    This enum describes the different types of slot chains.
    A slot chain's type influences when it will be executed
    during event processing.

    \todo Document when each type of chain is executed
*/
enum SLOT_CHAIN_TYPE {
    BEFORE = 1,
    AFTER = 2,
};

class CPAF_API Event
{
public:
    /*!
        Construct an event.

        \param id   The ID of the event being sent
        \param obj  The ID of the object sending this event
    */
    Event(event_id id, object_id obj);

    Event(const Event &other);

    virtual ~Event();

    /*!
        Creates a clone of this event object.
    */
    virtual Event *clone() const;

    /*!
        \return The id of this event
    */
    event_id get_id() const;

    /*!
        \return The id of the object sending this event
    */
    object_id get_object_id() const;

    /*!
        Specify whether or not processing of this event continue to further slot in the slot chain.
        If you do not wish an event to be processed further, you do not need to do anything. To allow
        further slot in the chain to process the event, call this function.
    */
    void continue_processing(bool c = true) const;

    /*!
        \return Whether or not processing of this event should continue down the slot chain
    */
    bool should_continue() const;

    /*!
        Vetos the event.
    */
    void veto(bool v = false) const;

    /*!
        \return Whether or not this event has been vetoed.
    */
    bool get_veto() const;

    /*!
        \reteurn True if this event is allowed t be vetoed
    */
    virtual bool can_veto() const;

private:
    const event_id m_id;
    const object_id m_obj_id;
    mutable bool m_continue, m_veto;
};

/*!
    Base slot class providing a virtual operator().
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
    virtual void operator() (const Event &e) = 0;

};

/*!
    Represents a chain of slots.
*/
class CPAF_API SlotChain
{
public:
    /*!
        \return The event id that this chain recieves events for
    */
    event_id get_event_id() const { return m_event_id; }

    /*!
        \return The object that this event chain recieves events from
    */
    object_id get_object_id() const { return m_object_id; }

    /*!
        Add a slot to this event chain.
    */
    SlotChain &connect(Slot *func);

private:
    typedef boost::shared_ptr<Slot> slot_type;
    typedef std::vector<slot_type> slot_chain_type;
    slot_chain_type m_slots;

    object_id m_object_id; // the object that this SlotChain recieves events from
    event_id m_event_id; // the event id that this SlotChain recieves events from

    /*!
        Private constructor for use via the friended Manager class
    */
    SlotChain(object_id object, event_id event);
    
    /*!
        Process an event.
    */
    void process_event(Event &event, bool &veto);

    friend class Manager;
};

/*!
    Main event system object. Manages sending events and connecting listeners which form chains.
*/
class CPAF_API Manager
{
public:
    Manager();

    /*!
        Creates an SlotChain object to connect event listeners to.

        \param from     Object to recieve events from
        \param event_id Event id to recieve
        \param type     Specifies what type of slot chain this is. Different types of slot
                        chains are executed at different times during event processing.

        \return Reference to the SlotChain object.
    */
    SlotChain &create_event_chain(object_id from, event_id id, SLOT_CHAIN_TYPE type);

    /*!
        Sends an event
    */
    void send_event(Event &event);

private:
    // storage related typedefs
    typedef std::vector<slot_chain_ptr> slot_chain_vector;
    typedef std::map<event_id, slot_chain_vector> event_vector_map;
    typedef std::map<object_id, slot_chain_vector> object_vector_map;
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

    void send_event(slot_chain_vector &chain, Event &event, bool &veto);

    /*!
        \return Whether a slot chain exists for this object_id event_id pair. If a slot chain
            exists, the value of chain will point to that slot chain. If a chain does not exist,
            the value of chain is undefined.
    */
    bool get_slot_chain(object_event_vector_map &map, slot_chain_vector *&chain, object_id from, event_id id);

    /*!
        \return Whether or not a slot chain exists for the given key.
    */
    template<typename M, typename T> bool get_slot_chain(M &map, slot_chain_vector *&chain, T key);
};

/*!
    This is a convenience function which allows you to more easliy connect slots. The purpose of this
    function is to create a templated wrapper around an SlotChain object which you use to add slots
    forming a chain. Example usage:

    // connect a single slot
    connect<Event, BEFORE>(WIDGET_CREATE, object_id) (&Foo::on_create, *this);

    // connect two slots in the same slot chain
    connect<Event, BEFORE>(WIDGET_CREATE, object_id) (&Foo::on_create, *this) (&Foo::on_create2, *this);

    Template parameters:
    E   Event type being connected
    T   The type of slot chain being created. The type of slot chain effects when it executes in
        relation to other slot chains.

    \param event    Id of the event
    \param object   The object to recieve events from
    \param manager  An event manager to connect to
*/
template<typename E, SLOT_CHAIN_TYPE T> SlotChainWrapper<E> connect(event_id event, object_id object, cpaf::event::Manager &manager = cpaf::event::get_manager())
{
    return SlotChainWrapper<E>(manager.create_event_chain(object, event, T));
}

/*!
    This is a convenience overload of the connect() function which allows you to omit
    the SLOT_CHAIN_TYPE template parameter. A default parameter value of BEFORE is used
*/
template<typename E> SlotChainWrapper<E> connect(event_id event, object_id object, cpaf::event::Manager &manager = cpaf::event::get_manager())
{
    return SlotChainWrapper<E>(manager.create_event_chain(object, event, BEFORE));
}

/*!
    A templated wrapper around the SlotChain class to allow for clean, typesafe code
*/
template<typename E> class SlotChainWrapper
{
private:
    SlotChain &m_chain;

public:

    /*!
        Construct a wrapper around an SlotChain object
    */
    SlotChainWrapper(SlotChain &chain)
      : m_chain(chain)
    { }

    /*!
        Templated wrapper around the SlotChain::connect function. This function is used to
        cleany create a ListenerFunctor which will provide type-safety to event
        processing.

        Template params:
        L   Object connecting the event

        \param l Listening object connecting this event
        \param function The listening function
    */
    template<typename L> SlotChainWrapper<E> &operator()(typename SafeSlot<L, E>::ptr_type function, L &l)
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
    typedef void(L::*ptr_type)(const E &e); // the function pointer for this functor
    typedef E event_type; // the type of event that this functor works with

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
    void operator() (const Event &e)
    {
        (m_listener.*m_ptr)(dynamic_cast<const event_type&>(e));
    }
};

/*******************************************
 *       Event Object Declarations         *
 *******************************************/

class MouseEvent : public Event
{
public:
    /*!
        Constructs a mouse event

        \param id       The id of the event
        \param obj      The id of the object sending the event
        \param pos      Position of the mouse in client coordinates of the widget
        \param button_flags Identifies what mouse buttons were pressed when the mouse event was generated
        \param key_flags Identifies what keys were pressed when the mouse event was generated
    */
    MouseEvent(event_id id, object_id obj, const cpaf::Point &pos, int button_flags, int key_flags);

    /*!
        Bit flags for the keys that may have been pressed when the event was sent
    */
    enum KEY_FLAGS {
        NONE =      0x0,
        SHIFT =     0x1,
        ALT =       0x2,
        CONTROL =   0x4,
    };

    /*!
        Bit flags for identifying which mouse buttons are pressed, if any.
    */
    enum BUTTON_FLAGS {
        LEFT =      0x1,
        RIGHT =     0x2,
        MIDDLE =    0x4
    };

    /*!
        \return A bitmask identifying which keys were pressed when the event was sent
    */
    int get_button_flags() const;

    /*!
        \return Whether or not the given mouse button was pressed when the event was sent
    */
    bool get_button_state(BUTTON_FLAGS button) const;

    /*!
        \return A bitmask identifying which keys were pressed when the event was sent
    */
    int get_key_flags() const;

    /*!
        \return Whether or not the given key was pressed when the event was sent
    */
    bool get_key_state(KEY_FLAGS key) const;

    /*!
        \return Position of the mouse in client coordinates when this event was sent
    */
    cpaf::Point get_position() const;

private:
    //! position of the mouse event in client coordinates
    cpaf::Point m_position;

    //! Identifies what mouse buttons were pressed whe the event was generated
    int m_button_flags;

    //! Identifies what keys were pressed when the event was generated
    int m_key_flags;
};

    } // event
} // cpaf

#endif // CPAF_EVENT_H
