/*
common header for win32 implementation
*/

#ifndef CPAF_WIN32_WIN_H
#define CPAF_WIN32_WIN_H

#if _MSC_VER
#   pragma warning(disable:4786) // truncated to 255 characters in the debug info
#endif

#include <windows.h>

#include <map>

namespace cpaf {

    namespace win32 {
        namespace gui {

class Widget;

typedef std::map<HWND, cpaf::win32::gui::Widget *> WidgetMap;

extern WidgetMap widget_map;

template <typename T> T *get_widget_from_hwnd(HWND h)
{
    return dynamic_cast<T*>(widget_map[h]);
}

void widget_map_add_hwnd(HWND h, cpaf::win32::gui::Widget *wnd);

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_WIN_H
