/*
Implementation for common win32 implementation functions
*/

#include <cpaf/win32/win.h>

cpaf::win32::gui::WidgetMap cpaf::win32::gui::widget_map;

void cpaf::win32::gui::widget_map_add_hwnd(HWND h, cpaf::win32::gui::Widget *wnd)
{
    widget_map[h] = wnd;
}

void cpaf::win32::gui::widget_map_remove_hwnd(HWND h)
{
    cpaf::win32::gui::WidgetMap::iterator i = widget_map.find(h);

    if( i != widget_map.end() )
        widget_map.erase(i);
    //! todo I should probably throw if the above is not true because this is bad...
}
