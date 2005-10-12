/*!
    \file include/cpaf/event/id.h
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

#ifndef CPAF_EVENT_ID_H
#define CPAF_EVENT_ID_H

#include <cpaf/dllimpexp.h>

namespace cpaf { 
    namespace event {

typedef int event_id; // event identifier

/*!
    This function generates a unique event id.
    \return A unique event id
*/
event_id get_unique_id();

//! Helper macro for the declaration of event ids in header files
#define CPAF_DECLARE_EXPORTED_EVENT(name)    CPAF_API extern const event_id name;

//! Helper macro for implementing event ids in source files
#define CPAF_IMPLEMENT_EXPORTED_EVENT(name)  const event_id name = get_unique_id();

// event id declarations

/*******************************************
 *                  Widget                 *
 *******************************************/

//! The widget was created
CPAF_DECLARE_EXPORTED_EVENT(WIDGET_CREATE)

//! The widget is about to be destroyed
CPAF_DECLARE_EXPORTED_EVENT(WIDGET_DESTROY)

//! The size of a widget has changed
CPAF_DECLARE_EXPORTED_EVENT(WIDGET_SIZE_CHANGED)

/*******************************************
 *                  Mouse                  *
 *******************************************/

 //! The mouse entered the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_ENTER)

//! The mouse left the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_LEAVE)

//! The mouse moved within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_MOVE)

//! The mouse was stationary within the widget's client area for a period of time
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_HOVER)

//! The left mouse button was pressed within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_LEFT_DOWN)

//! The left mouse button was released within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_LEFT_UP)

//! The left mose button was double clicked within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_LEFT_DOUBLECLICK)

//! The middle mouse button was pressed within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_MIDDLE_DOWN)

//! The middle mouse button was released within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_MIDDLE_UP)

//! The middle mose button was double clicked within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_MIDDLE_DOUBLECLICK)

//! The right mouse button was pressed within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_RIGHT_DOWN)

//! The right mouse button was released within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_RIGHT_UP)

//! The middle mose button was double clicked within the widget's area
CPAF_DECLARE_EXPORTED_EVENT(MOUSE_MIDDLE_DOUBLECLICK)

/*******************************************
 *                  Button                 *
 *******************************************/

//! The button was clicked
CPAF_DECLARE_EXPORTED_EVENT(BUTTON_CLICK)

/*******************************************
 *                TextWidget               *
 *******************************************/

//! The text in the text widget has changed
CPAF_DECLARE_EXPORTED_EVENT(TEXT_CHANGED)

    } // event
} // cpaf

#endif
