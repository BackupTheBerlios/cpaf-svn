/*!
    \file src/cpaf/event/id.cpp
    \brief Event id declarations
    \date Created: 2005-07-07
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

#include <cpaf/event/id.h>

using namespace cpaf::event;

event_id cpaf::event::get_unique_id()
{
    static int next = 0;
    return ++next;
}

namespace cpaf { 
    namespace event {

// widget
CPAF_IMPLEMENT_EXPORTED_EVENT(WIDGET_CREATE)
CPAF_IMPLEMENT_EXPORTED_EVENT(WIDGET_DESTROY)
CPAF_IMPLEMENT_EXPORTED_EVENT(WIDGET_SIZE_CHANGED)

// mouse
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_ENTER)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_LEAVE)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_MOVE)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_HOVER)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_LEFT_DOWN)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_LEFT_UP)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_LEFT_DOUBLECLICK)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_MIDDLE_DOWN)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_MIDDLE_UP)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_MIDDLE_DOUBLECLICK)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_RIGHT_DOWN)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_RIGHT_UP)
CPAF_IMPLEMENT_EXPORTED_EVENT(MOUSE_RIGHT_DOUBLECLICK)

// button
CPAF_IMPLEMENT_EXPORTED_EVENT(BUTTON_CLICK)

// edit
CPAF_IMPLEMENT_EXPORTED_EVENT(TEXT_CHANGED)

    } // event
} // cpaf
