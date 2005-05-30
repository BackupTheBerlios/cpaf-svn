/*
implementation of win32 window
*/

#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/exception.h>

#define CLASSNAME TEXT("cpaf::Window")

namespace {

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

//! \todo remove duplicated code from window and button ctor
cpaf::win32::gui::Window::Window(const cpaf::gui::factory::WindowData &params)
: Widget(params)
{
    static bool registered = false;

    // register the window class
    //! \todo This may leak some memory because window classes registered by dll's are not unloaded
    // by the NT kernel, but they are on flavors of win 95.
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

    if( x == cpaf::DEFAULT_VALUE )
        x = CW_USEDEFAULT;
    if( w == cpaf::DEFAULT_VALUE )
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
