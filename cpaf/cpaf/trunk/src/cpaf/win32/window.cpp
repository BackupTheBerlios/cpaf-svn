/*
implementation of win32 window
*/

#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/exception.h>

#define CLASSNAME "cpaf::Window"

static WNDCLASSEX wnd_class = {
    sizeof(WNDCLASSEX),
    CS_DBLCLKS,
    (WNDPROC)cpaf::win32::gui::window_wndproc, // subclass to use window_wndproc later
    0,
    0,
    GetModuleHandle(NULL),
    NULL,
    LoadCursor(NULL, IDC_ARROW),
    (HBRUSH)COLOR_BACKGROUND,
    NULL,
    CLASSNAME
};

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


cpaf::win32::gui::Window::Window(int id, cpaf::api::gui::Window *parent)
: Widget(id)
{
    static bool registered = false;

    // register the window class
    //! \todo This may leak some memory because window classes registered by dll's are not unloaded
    // by the NT kernel, but they are on flavors of win 95.
    if( !registered )
        ::RegisterClassEx(&wnd_class);

    HWND hparent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        hparent = ::GetDesktopWindow();

    // initialize creation info
    CreationInfo info(this);

    m_hwnd = ::CreateWindowEx(0, CLASSNAME, "Cpaf!!", WS_OVERLAPPEDWINDOW ,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hparent, NULL, ::GetModuleHandle(NULL),
        &info);

    if( !m_hwnd )
        throw cpaf::win32::Exception(cpaf::Exception::error_codes::NATIVE_HANDLE, ::GetLastError(), __LINE__, __FILE__);
}

std::string cpaf::win32::gui::Window::get_title()
{
    return get_window_text();
}

void cpaf::win32::gui::Window::set_title(const std::string &t)
{
    set_window_text(t);
}
