/*
common header for win32 implementation
*/

#if _MSC_VER
#   pragma warning(disable:4786) // truncated to 255 characters in the debug info
#endif

#include <windows.h>

#include <map>

namespace cpaf {

    namespace win32 {
        namespace gui {

class Window;

typedef std::map<HWND, cpaf::win32::gui::Window *> WidgetMap;

extern WidgetMap widget_map;

template <typename T> T *get_widget_from_hwnd(HWND h)
{
    return static_cast<T*>(widget_map[h]);
}

void widget_map_add_hwnd(HWND h, cpaf::win32::gui::Window *wnd);

        } // gui
    } // win32
} // cpaf
