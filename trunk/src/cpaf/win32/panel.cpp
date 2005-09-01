/*!
    \file src/cpaf/win32/panel.cpp
    \brief Implementation of cpaf::win32::gui::Panel
    \date Created: 
*/

#include <cpaf/win32/gui/panel.h>
#include <cpaf/exception.h>

using namespace cpaf::win32::gui;

namespace {

const TCHAR CLASSNAME[] = TEXT("cpaf::Panel");

WNDCLASSEX wnd_class = {
    sizeof(WNDCLASSEX),
    CS_DBLCLKS,
    (WNDPROC)cpaf::win32::gui::panel_wndproc,
    0,
    DLGWINDOWEXTRA,
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
    return ::DefWindowProc(hwnd, msg, w_param, l_param);
}

Panel::Panel()
: m_layout_manager(0)
{ }

void Panel::create(const cpaf::gui::initializer::PanelData &params)
{
    static bool registered = false;

    if( !registered )
        ::RegisterClassEx(&wnd_class);

    // panels must have layout managers
    m_layout_manager = params.get_layout_manager();
    if( !m_layout_manager )
        throw cpaf::Exception(cpaf::Exception::PANEL_NO_LAYOUT_MANAGER, __LINE__, __FILE__);

    // Create a panel
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, false, CLASSNAME, 0,
        WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_CONTROLPARENT);
}

int Panel::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch(msg)
    {
    case WM_SIZE:
        /*!
            \todo Decide wether the layout manager should update its children
                before or after the size event is sent
        */
        // update the layout manager
        m_layout_manager->do_layout(cpaf::Size(LOWORD(l_param), HIWORD(l_param)));

        break;
    };

    return cpaf::win32::gui::Widget::process_message(hwnd, msg, w_param, l_param);
}
