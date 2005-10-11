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

namespace {
    // pointer to the cpaf::App's event object
    // initialized via Manager ctor
    cpaf::event::Manager *manager;
}

cpaf::event::Manager &cpaf::event::get_manager()
{
    return *manager;
}

const int cpaf::event::Manager::BEFORE_MAP = 0;
const int cpaf::event::Manager::AFTER_MAP = 1;

/*
cpaf::event::Manager
*/
cpaf::event::Manager::Manager()
{
    // initialize the private pointer
    manager = this;
}

EventChain &cpaf::event::Manager::create_event_chain(object_id from, event_id id, bool after)
{
    // create the event chain
    event_chain_ptr chain( new EventChain(this, from, id) );

    int map = (after == true) ? AFTER_MAP : BEFORE_MAP;

    // add the event chain to the appropriate map
    if( from == OBJECT_ID_ANY )
        m_evt_map[map][id].push_back(chain);
    else if( id == EVENT_ID_ANY )
        m_obj_map[map][from].push_back(chain);
    else
        m_obj_evt_map[map][from][id].push_back(chain);

    return *chain;
}

void cpaf::event::Manager::send_event(Event &e)
{
    // send the event through all the maps
    event_id id = e.get_id();
    object_id from = e.get_object_id();

    // regular maps
    send_event(m_obj_evt_map[BEFORE_MAP][from][id], e); // {object, event} map
    send_event(m_evt_map[BEFORE_MAP][id], e);           // {[any], event} map
    send_event(m_obj_map[BEFORE_MAP][from], e);         // {object, [any]} map

    // "post processing" maps
    send_event(m_obj_evt_map[AFTER_MAP][from][id], e); // {object, event} map
    send_event(m_evt_map[AFTER_MAP][id], e);           // {[any], event} map
    send_event(m_obj_map[AFTER_MAP][from], e);         // {object, [any]} map
}

inline void cpaf::event::Manager::send_event(event_chain_vector &chain, Event &e)
{
    for( event_chain_vector::iterator i = chain.begin(), end = chain.end(); i != end; ++i )
        (*i)->process_event(e);
}

/*
cpaf::event::EventChain
*/
cpaf::event::EventChain::EventChain(Manager *manager, object_id object, event_id event)
    : m_manager(manager),
    m_object_id(object),
    m_event_id(event)
{ }

EventChain &cpaf::event::EventChain::connect(Slot *func)
{
    // add the event listener to the end for now
    //! \todo allow insertions into an arbitrary position in the chain
    m_slots.push_back(slot_type(func));

    return *this;
}

void cpaf::event::EventChain::process_event(Event &e)
{
    // send the event to all listeners in our chain starting from the back
    for( slot_chain_type::reverse_iterator i = m_slots.rbegin(), end = m_slots.rend(); i != end; ++i )
    {
        // initialize the event
        e.continue_processing(false);

        // send the event
        (*(*i)) (e); // dereference the iterator, and the shared_ptr, then invoke operator()

        // continue processing only if necessary
        if( !e.should_continue() )
            break;
    }
}

/*
cpaf::event::Event
*/
cpaf::event::Event::Event(event_id id, object_id obj)
    : m_id(id),
    m_obj_id(obj),
    m_continue(false)
{ }
