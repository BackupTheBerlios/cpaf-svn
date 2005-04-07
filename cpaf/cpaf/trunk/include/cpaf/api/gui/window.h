/*
Window interface definition
*/

#ifndef CPAF_API_GUI_WINDOW_H
#define CPAF_API_GUI_WINDOW_H

#include <cpaf/api/gui/toplevel.h>

namespace cpaf {
    namespace api {
        namespace gui {
/*!
    \brief A Window is a top level widget which has a title bar and contains subwindows
*/
class Window : public TopLevel
{
public:
    static int factory_key;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_WINDOW_H
