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
    WidgetMap::iterator i = widget_map.find(h);
    if( i != widget_map.end() )
        return dynamic_cast<T*>(i->second);
    else
        return NULL;
}

void widget_map_add_hwnd(HWND h, cpaf::win32::gui::Widget *wnd);
void widget_map_remove_hwnd(HWND h);

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_WIN_H
