/*
implementation of win32 window
*/

#include <cpaf/win32/gui/window.h>

#define CLASSNAME cS("cpaf::Window")

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
    return cpaf::win32::gui::widget_wndproc(0, hwnd, msg, w_param, l_param);
}

        } // gui
    } // win32
} // cpaf


cpaf::win32::gui::Window::Window(cpaf::api::gui::Window *parent)
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

    m_hwnd = ::CreateWindowEx(0, CLASSNAME, cS("Cpaf!!"), WS_OVERLAPPEDWINDOW ,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hparent, NULL, ::GetModuleHandle(NULL),
        &info);
}

//! \todo re-do this code considering that win32 is always unicode and move it to a common function
cpaf::String cpaf::win32::gui::Window::get_title()
{
    int len = ::GetWindowTextLength(m_hwnd) + 1; //GetWindowTextLength doesn't include the terminating NULL char
    LPTSTR buff = new TCHAR[len];
    ::GetWindowText(m_hwnd, buff, len);
    cpaf::String ret(buff);
    delete buff;
    return ret;
}

void cpaf::win32::gui::Window::set_title(const cpaf::String &t)
{
    ::SetWindowText(m_hwnd, t.c_str());
}
