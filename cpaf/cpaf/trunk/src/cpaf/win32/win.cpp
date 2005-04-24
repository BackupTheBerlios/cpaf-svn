/*
Implementation for common win32 implementation functions
*/

#include <cpaf/win32/win.h>
#include <cpaf/win32/gui/widget.h>
#include <cpaf/exception.h>

using cpaf::win32::gui::WidgetMap;

static cpaf::win32::gui::WidgetMap widget_map;

void cpaf::win32::gui::widget_map_add_hwnd(HWND h, cpaf::win32::gui::Widget *wnd)
{
    widget_map[h] = wnd;
}

void cpaf::win32::gui::widget_map_remove_hwnd(HWND h)
{
    WidgetMap::iterator i = widget_map.find(h);

    if( i != widget_map.end() )
        widget_map.erase(i);

    // we do not throw if the hwnd was not found in the map because this function is called by
    // win32::gui::Widget dtor. Throwing dtors are bad and cause all sorts of trouble as I recently
    // discovered...
}

cpaf::win32::gui::Widget *cpaf::win32::gui::get_widget_from_hwnd(HWND h)
{
    WidgetMap::iterator i = widget_map.find(h);
    if( i != widget_map.end() )
        return i->second;
    else
        return NULL;
}

cpaf::win32::gui::CreationInfo::CreationInfo(cpaf::win32::gui::Widget *w)
    : wnd(w)
{ }

LRESULT CALLBACK cpaf::win32::gui::widget_wndproc(WNDPROC old_proc, HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    Widget *wnd = get_widget_from_hwnd(hwnd);

    // once we can find our widget class, use it to process messages
    if( wnd )
        return wnd->process_message(hwnd, msg, w_param, l_param);

    // we can't find the widget class yet, look for WM_NCCREATE, which should always be the first
    // message sent to a window (usually, top levels get WM_MINMAXINFO first), and add the widget
    // class for this hwnd to the map
    switch(msg)
    {
        case WM_NCCREATE:
            // lpCreateParams of CREATESTRUCT specifies the address of a CreationInfo struct.
            // This struct currently contains a (properly casted) pointer to the object
            // creating this window.
            LPCREATESTRUCT create = (LPCREATESTRUCT)l_param;
            CreationInfo *info = (CreationInfo*)create->lpCreateParams;
            widget_map_add_hwnd(hwnd, info->wnd);
            
            // let the widget process everything we possibly can, even WM_NCCREATE
            return info->wnd->process_message(hwnd, msg, w_param, l_param);
    }

    // call the old window procedure if we get this far
    // this will happen if the first message sent to a window is not WM_NCCREATE,
    // which is the case for overlapped (toplevel) windows: they get WM_MINMAXINFO first
    if( old_proc )
        return ::CallWindowProc(old_proc, hwnd, msg, w_param, l_param);
    else
        return ::DefWindowProc(hwnd, msg, w_param, l_param);
}
