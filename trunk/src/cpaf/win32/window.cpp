/*!
    \file src/cpaf/win32/window.cpp
    \brief Implementation file for cpaf::win32::gui::Window
    \date Created: 2005-04-05
*/

#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/exception.h>

namespace {

const TCHAR CLASSNAME[] = TEXT("cpaf::Window");

WNDCLASSEX wnd_class = {
    sizeof(WNDCLASSEX),
    CS_DBLCLKS,
    (WNDPROC)cpaf::win32::gui::window_wndproc,
    0,
    0,
    GetModuleHandle(NULL),
    NULL,
    LoadCursor(NULL, IDC_ARROW),
    (HBRUSH)COLOR_BACKGROUND,
    NULL,
    CLASSNAME
};

} // unnamed namespace

namespace cpaf {
    namespace win32 {
        namespace gui {

LRESULT CALLBACK window_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    return cpaf::win32::gui::widget_wndproc(hwnd, msg, w_param, l_param);
}

        } // gui
    } // win32
} // cpaf

void cpaf::win32::gui::Window::create(const cpaf::gui::factory::WindowData &params)
{
    //! \todo remove duplicated code from window and button create methods

    //! \todo handle client_size from the factory
    static bool registered = false;

    // register the window class
    //! \todo This may leak some memory because window classes registered by dll's are not unloaded
    //! by the NT kernel, but they are on flavors of win 95.
    if( !registered )
        ::RegisterClassEx(&wnd_class);

    HWND hparent;
    cpaf::gui::Widget *parent = params.m_parent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        hparent = ::GetDesktopWindow();

    // initialize creation info
    CreationInfo info(this);
    int x = params.m_pos.x, y = params.m_pos.y;
    int w = params.m_size.width, h = params.m_size.height;

    if( params.m_default_position )
        x = CW_USEDEFAULT;
    if( params.m_default_size )
        w = CW_USEDEFAULT;

    m_hwnd = ::CreateWindowEx(0, CLASSNAME, params.m_title.c_str(), WS_OVERLAPPEDWINDOW,
        x, y, w, h, hparent, NULL, ::GetModuleHandle(NULL),
        &info);

    if( !m_hwnd )
        throw cpaf::win32::Exception(cpaf::Exception::NATIVE_HANDLE, ::GetLastError(), __LINE__, __FILE__);

    // show the window if necessary
    if( params.m_show )
        show(true, params.m_activate);
}

std::string cpaf::win32::gui::Window::get_title()
{
    return get_window_text();
}

void cpaf::win32::gui::Window::set_title(const std::string &t)
{
    set_window_text(t);
}

void cpaf::win32::gui::Window::set_client_size(const cpaf::Size &s)
{
    // the desired client size
    RECT client_rect = {0};
    client_rect.right = s.width;
    client_rect.bottom = s.height;

    // used for calculations
    RECT rect = {0};
    rect.right = s.width;
    rect.bottom = s.height;

    // use AdjustWindowRect to go from client to absolute size
    /*!
        \todo Take into account what styles we might actually have.
        \todo Also consider if there is a menu or not.
        \todo Account for failure (ret 0).
    */
    ::AdjustWindowRect(&rect, WS_CAPTION | WS_THICKFRAME, false);

    // normalize the calculated rect
    rect.right = rect.right - rect.left;
    rect.left = 0;
    rect.bottom = rect.bottom - rect.top;
    rect.top = 0;

    // set the window size
    ::SetWindowPos(m_hwnd, NULL, 0, 0, rect.right, rect.bottom,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

    // because AdjustWindowRect will not account for menu height, lets see how big the client size
    // actually ended up and adjust further if necessary
    //! \todo prevent sending multiple size changed messages

    RECT new_rect;
    ::GetClientRect(m_hwnd, &new_rect);

    //! \todo This code has yet to be tested
    if( new_rect.bottom != client_rect.bottom || new_rect.right != client_rect.right )
    {
        // size ourselves again using the difference to get an exact size
        rect.bottom = rect.bottom + (new_rect.bottom - client_rect.bottom);
        rect.right = rect.right + (new_rect.right - client_rect.right);

        ::AdjustWindowRect(&rect, WS_CAPTION | WS_THICKFRAME, false);

        // normalize the calculated rect
        rect.right = rect.right - rect.left;
        rect.left = 0;
        rect.bottom = rect.bottom - rect.top;
        rect.top = 0;

        // set the window size
        ::SetWindowPos(m_hwnd, NULL, 0, 0, rect.right, rect.bottom,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

        // test to see if it is ok now
        ::GetClientRect(m_hwnd, &new_rect);
    }
}
