/*!
    \file src/cpaf/win32/panel.cpp
    \brief Implementation of cpaf::win32::gui::Panel
    \date Created: 
*/

#include <cpaf/win32/gui/panel.h>

namespace {

const TCHAR CLASSNAME[] = TEXT("cpaf::Panel");

WNDCLASSEX wnd_class = {
    sizeof(WNDCLASSEX),
    CS_DBLCLKS,
    (WNDPROC)cpaf::win32::gui::panel_wndproc,
    0,
    0,
    GetModuleHandle(NULL),
    NULL,
    LoadCursor(NULL, IDC_ARROW),
    (HBRUSH)(COLOR_BTNFACE+1),
    NULL,
    CLASSNAME
};

} // unnamed namespace

LRESULT CALLBACK cpaf::win32::gui::panel_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    //DBG_MSG_2("cpaf::win32::gui::panel_wndproc: %s", cpaf::win32::MessageTypeNames[msg]);
    return ::DefWindowProc(hwnd, msg, w_param, l_param);
}

void cpaf::win32::gui::Panel::create(const cpaf::gui::initializer::PanelData &params)
{
    static bool registered = false;

    if( !registered )
        ::RegisterClassEx(&wnd_class);

    // Create a panel
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, false, CLASSNAME, 0,
        WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_CONTROLPARENT);
}
