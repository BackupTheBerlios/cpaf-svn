/*!
    \file src/cpaf/event/event.cpp
    \brief Implementation of the event system
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

#include <cpaf/event/event.h>

using namespace cpaf::event;
using cpaf::object_id;

namespace {
    // pointer to the cpaf::App's event object
    // initialized via Manager ctor
    Manager *manager;
}

Manager &cpaf::event::get_manager()
{
    return *manager;
}

const int Manager::BEFORE_MAP = 0;
const int Manager::AFTER_MAP = 1;

/*
Manager
*/
Manager::Manager()
{
    // initialize the private pointer
    manager = this;
}

SlotChain &Manager::create_event_chain(object_id from, event_id id, SLOT_CHAIN_TYPE type)
{
    // create the event chain
    slot_chain_ptr chain( new SlotChain(from, id) );

    int map = 0;
    switch(type)
    {
    case BEFORE:
        map = BEFORE_MAP;
        break;
    case AFTER:
        map = AFTER_MAP;
        break;
    default:
        //! \todo Throw
        ;
    }

    // add the event chain to the appropriate map
    if( from == OBJECT_ID_ANY )
        m_evt_map[map][id].push_back(chain);
    else if( id == EVENT_ID_ANY )
        m_obj_map[map][from].push_back(chain);
    else
        m_obj_evt_map[map][from][id].push_back(chain);

    return *chain;
}

inline bool Manager::get_slot_chain
(object_event_vector_map &map, slot_chain_vector *&chain, object_id from, event_id id)
{
    object_event_vector_map::iterator event_map = map.find(from);
    if( event_map != map.end() )
        return get_slot_chain(event_map->second, chain, id);
    else
        return false;
}

template<typename M, typename T> inline bool Manager::get_slot_chain
(M &map, slot_chain_vector *&chain, T key)
{
    typename M::iterator element = map.find(key);
    if( element != map.end() )
    {
        chain = &element->second;
        return true;
    }

    return false;
}

void Manager::send_event(Event &event)
{
    // send the event through all the maps
    event_id id = event.get_id();
    object_id from = event.get_object_id();
    bool veto = false;

    slot_chain_vector *chain;

    // regular maps
    if( get_slot_chain(m_obj_evt_map[BEFORE_MAP], chain, from, id) ) // {object, event} map
        send_event(*chain, event, veto);
    if( get_slot_chain(m_evt_map[BEFORE_MAP], chain, id) ) // {[any], event} map
        send_event(*chain, event, veto);
    if( get_slot_chain(m_obj_map[BEFORE_MAP], chain, from) ) // {object, [any]} map
        send_event(*chain, event, veto);

    // if the event was veto'd, after slots do not get executed
    if( !veto )
    {
        // "post processing" maps
        if( get_slot_chain(m_obj_evt_map[AFTER_MAP], chain, from, id) ) // {object, event} map
            send_event(*chain, event, veto);
        if( get_slot_chain(m_evt_map[AFTER_MAP], chain, id) ) // {[any], event} map
            send_event(*chain, event, veto);
        if( get_slot_chain(m_obj_map[AFTER_MAP], chain, from) ) // {object, [any]} map
            send_event(*chain, event, veto);
    }

    // return the veto'd state through the event object
    event.veto(veto);
}

inline void Manager::send_event(slot_chain_vector &chain, Event &event, bool &veto)
{
    for( slot_chain_vector::iterator i = chain.begin(), end = chain.end(); i != end; ++i )
        (*i)->process_event(event, veto);
}

/*
cpaf::event::SlotChain
*/
cpaf::event::SlotChain::SlotChain(object_id object, event_id event)
    : m_object_id(object),
    m_event_id(event)
{ }

SlotChain &cpaf::event::SlotChain::connect(Slot *func)
{
    // add the event listener to the end for now
    //! \todo allow insertions into an arbitrary position in the chain
    m_slots.push_back(slot_type(func));

    return *this;
}

void cpaf::event::SlotChain::process_event(Event &event, bool &veto)
{
    // initialize the veto state
    event.veto(false);

    // send the event to all listeners in our chain starting from the back
    for( slot_chain_type::reverse_iterator i = m_slots.rbegin(), end = m_slots.rend(); i != end; ++i )
    {
        // initialize the event
        event.continue_processing(false);

        // send the event
        (*(*i)) (event); // dereference the iterator, and the shared_ptr, then invoke operator()

        // continue processing only if necessary
        if( !event.should_continue() )
            break;
    }

    // accumulate the veto'd state
    veto |= event.get_veto();
}

/*******************************************
 *     Event Object Implementations        *
 *******************************************/

Event::Event(event_id id, object_id obj)
    : m_id(id),
    m_obj_id(obj),
    m_continue(false)
{ }

Event::Event(const Event &other)
    : m_id(other.m_id),
    m_obj_id(other.m_obj_id),
    m_continue(other.m_continue)
{ }

Event::~Event() { }

Event *Event::clone() const
{
    return new Event(*this);
}

event_id Event::get_id() const
{
    return m_id;
}

object_id Event::get_object_id() const
{
    return m_obj_id;
}

void Event::veto(bool v) const
{
    m_veto = v;
}

bool Event::get_veto() const
{
    return m_veto;
}

bool Event::can_veto() const
{
    return false;
}

void Event::continue_processing(bool c) const
{
    m_continue = c;
}

bool Event::should_continue() const
{
    return m_continue;
}

MouseEvent::MouseEvent(event_id id, object_id obj, const cpaf::Point &pos, int button_flags, int key_flags)
: Event(id, obj),
m_position(pos),
m_button_flags(button_flags),
m_key_flags(key_flags)
{ }

cpaf::Point MouseEvent::get_position() const
{
    return m_position;
}

int MouseEvent::get_button_flags() const
{
    return m_button_flags;
}

bool MouseEvent::get_button_state(BUTTON_FLAGS button) const
{
    return m_button_flags & button;
}

int MouseEvent::get_key_flags() const
{
    return m_key_flags;
}

bool MouseEvent::get_key_state(KEY_FLAGS key) const
{
    return m_key_flags & key;
}
