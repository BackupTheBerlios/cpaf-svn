/*!
    \file include/cpaf/api/gui/eventloop.h
    \brief Declares the EventLoop object API
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

#ifndef CPAF_API_GUI_EVENTLOOP_H
#define CPAF_API_GUI_EVENTLOOP_H

namespace cpaf {
    namespace api {
        namespace gui {

class EventLoop
{
public:
    virtual ~EventLoop();

    virtual void run() = 0;
    virtual void run_once() = 0;
    virtual void run_until() = 0;
    virtual void stop() = 0;
    virtual bool is_running() const = 0;

    // I'm lazy, so this will be the factory function implemented by a port
    // to return their derivative of this interface
    static EventLoop *create();
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_EVENTLOOP_H
