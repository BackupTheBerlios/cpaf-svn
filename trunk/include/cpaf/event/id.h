/*!
    \file include/cpaf/event/id.h
    \brief Event id declarations
    \date Created: 2005-07-07
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

// event declarations

// widget
CPAF_DECLARE_EXPORTED_EVENT(WIDGET_CREATE)
CPAF_DECLARE_EXPORTED_EVENT(WIDGET_DESTROY)

// button
CPAF_DECLARE_EXPORTED_EVENT(BUTTON_CLICK)

// edit
CPAF_DECLARE_EXPORTED_EVENT(TEXT_CHANGED)

    } // event
} // cpaf

#endif
