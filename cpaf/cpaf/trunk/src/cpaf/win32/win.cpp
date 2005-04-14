/*
Implementation for common win32 implementation functions
*/

#include <cpaf/win32/win.h>

static cpaf::win32::gui::WidgetMap widget_map;

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

cpaf::win32::gui::Widget *cpaf::win32::gui::get_widget_from_hwnd(HWND h)
{
    cpaf::win32::gui::WidgetMap::iterator i = widget_map.find(h);
    if( i != widget_map.end() )
        //return dynamic_cast<T*>(i->second);
        return i->second;
    else
        return NULL;
}
