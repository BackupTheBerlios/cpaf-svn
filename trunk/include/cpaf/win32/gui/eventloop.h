/*!
    \file include/cpaf/win32/gui/eventloop.h
    \brief Declares the EventLoop object
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

#ifndef CPAF_WIN32_GUI_EVENTLOOP_H
#define CPAF_WIN32_GUI_EVENTLOOP_H

#include <cpaf/api/gui/EventLoop.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class EventLoop : public cpaf::api::gui::EventLoop
{
public:
    EventLoop();

    void run();
    void run_once();
    void run_until();
    void stop();
    bool is_running() const;

private:
    bool m_running, m_stop;
};

        } // gui
    } // win32
} // cpaf
#endif // CPAF_WIN32_GUI_EVENTLOOP_H
