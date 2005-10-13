/*!
    \file src/cpaf/gtk2/gui/eventloop.cpp
    \brief Implements the EventLoop object for gtk2
    \date Created: 2005-10-13
*/

#include <cpaf/gtk2/gui/EventLoop.h>

// implement factory
cpaf::api::gui::EventLoop *cpaf::api::gui::EventLoop::create()
{
    return new cpaf::gtk2::gui::EventLoop;
}

using cpaf::gtk2::gui::EventLoop;

EventLoop::EventLoop()
: m_running(false),
m_stop(false)
{

}

void EventLoop::run()
{
    //! \todo Implement the EventLoop api properly
    gtk_main();
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
