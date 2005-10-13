/*!
    \file include/cpaf/gtk2/gui/eventloop.h
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

#ifndef CPAF_GTK2_GUI_EVENTLOOP_H
#define CPAF_GTK2_GUI_EVENTLOOP_H

#include <cpaf/api/gui/EventLoop.h>

namespace cpaf {
    namespace gtk2 {
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
    } // gtk2
} // cpaf
#endif // CPAF_GTK2_GUI_EVENTLOOP_H
