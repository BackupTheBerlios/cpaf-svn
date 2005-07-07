/*!
    \file src/cpaf/event/id.cpp
    \brief Event id declarations
    \date Created: 2005-07-07
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

// button
CPAF_IMPLEMENT_EXPORTED_EVENT(BUTTON_CLICK)

// edit
CPAF_IMPLEMENT_EXPORTED_EVENT(TEXT_CHANGED)

    } // event
} // cpaf
