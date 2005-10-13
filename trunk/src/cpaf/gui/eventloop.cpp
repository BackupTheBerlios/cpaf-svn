/*!
    \file src/cpaf/gui/eventloop.cpp
    \brief Implements the EventLoop object
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

#include <cpaf/gui/eventloop.h>
#include <cpaf/api/gui/eventloop.h>

using cpaf::gui::EventLoop;

cpaf::api::gui::EventLoop::~EventLoop() { }

EventLoop::EventLoop()
: m_impl(cpaf::api::gui::EventLoop::create())
{

}

EventLoop::~EventLoop()
{

}

void EventLoop::run()
{
    m_impl->run();
}

void EventLoop::stop()
{
    m_impl->stop();
}

void EventLoop::run_once()
{
    m_impl->run_once();
}

bool EventLoop::is_running() const
{
    return m_impl->is_running();
}
