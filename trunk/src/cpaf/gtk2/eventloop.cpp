/*!
    \file src/cpaf/gtk2/gui/eventloop.cpp
    \brief Implements the EventLoop object for gtk2
    \date Created: 2005-10-13
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
