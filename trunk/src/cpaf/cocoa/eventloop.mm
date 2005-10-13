/*!
    \file src/cpaf/cocoa/gui/eventloop.cpp
    \brief Implements the EventLoop object for cocoa
    \date Created: 2005-10-13
*/

#include <cpaf/cocoa/gui/EventLoop.h>

// implement factory
cpaf::api::gui::EventLoop *cpaf::api::gui::EventLoop::create()
{
    return new cpaf::cocoa::gui::EventLoop;
}

using cpaf::cocoa::gui::EventLoop;

EventLoop::EventLoop()
: m_running(false),
m_stop(false)
{

}

void EventLoop::run()
{
    //! \todo Implement the API for EventLoop properly
    [NSApp run]; // Run the application
}

void EventLoop::run_once()
{

}

void EventLoop::run_until()
{

}

void EventLoop::stop()
{
    m_stop = true;
}

bool EventLoop::is_running() const
{
    return m_running;
}
