/*!
    \file src/cpaf/win32/panel.cpp
    \brief Implementation of cpaf::win32::gui::Panel
    \date Created: 
*/

#include <cpaf/win32/gui/panel.h>
#include <cpaf/win32/exception.h>

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

Panel::~Panel()
{
    // delete the layout manager
    delete m_layout_manager;
}

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

#if 0
    m_wrapper = params.get_wrapper();
    m_id = m_wrapper->get_id();

    HWND hparent = NULL;
    cpaf::gui::Panel *parent = params.get_parent();
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        hparent = ::GetDesktopWindow();

    int x = params.get_pos().x, y = params.get_pos().y;
    int w = params.get_size().width, h = params.get_size().height;

    if( params.use_default_pos() )
        x = CW_USEDEFAULT;
    if( params.use_default_size() )
        w = CW_USEDEFAULT;

    {
        CreationHook hook; // hook WM_CREATE for initialization stuff
        CreationInfo info(this);
#define IDD_PANEL_TEMPLATE  0x1001
        m_hwnd = ::CreateDialog(::GetModuleHandle(TEXT("cpaf-gui-win32d.dll")), MAKEINTRESOURCE(IDD_PANEL_TEMPLATE), hparent, (DLGPROC)cpaf::win32::gui::panel_wndproc);
    }

    if( !m_hwnd )
        throw cpaf::win32::Exception(cpaf::Exception::NATIVE_HANDLE, ::GetLastError(), __LINE__, __FILE__);

    // set the default font to what it should be
    ::SendMessage(m_hwnd, WM_SETFONT, (WPARAM)::GetStockObject(DEFAULT_GUI_FONT), 0);

    // show the window if necessary
    if( params.get_show() )
        show(true, params.get_activate());
#endif
}

int Panel::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch(msg)
    {
    case WM_SIZE:
        /*!
            \todo Decide whether the layout manager should update its children
                before or after the size event is sent
        */
        // update the layout manager
        m_layout_manager->do_layout(cpaf::Size(LOWORD(l_param), HIWORD(l_param)));

        break;
    };

    return cpaf::win32::gui::Widget::process_message(hwnd, msg, w_param, l_param);
}

cpaf::gui::LayoutManager &Panel::get_layout_manager()
{
    return *m_layout_manager;
}
