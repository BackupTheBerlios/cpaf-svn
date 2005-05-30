/*
    Event system implementation
*/

#include <cpaf/event/event.h>

using namespace cpaf::event;

CPAF_IMPLEMENT_EVENT(cpaf::event::foo)

int cpaf::event::get_unique_id()
{
    static int next = 0;
    return ++next;
}

/*
cpaf::event::Manager
*/
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

void cpaf::event::Manager::send_event(object_id from, Event &e)
{
    // send the event through all the maps
    int id = e.get_id();

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

EventChain &cpaf::event::EventChain::connect(ListenerFunctorBase *func)
{
    // add the event listener to the end for now
    //! \todo allow insertions into an arbitrary position in the chain
    m_listeners.push_back(functor_ptr_type(func));

    return *this;
}

void cpaf::event::EventChain::process_event(Event &e)
{
    // send the event to all listeners in our chain starting from the back
    for( listener_vector_type::reverse_iterator i = m_listeners.rbegin(), end = m_listeners.rend(); i != end; ++i )
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
cpaf::event::Event::Event(event_id id)
    : m_id(id),
    m_continue(false)
{ }
