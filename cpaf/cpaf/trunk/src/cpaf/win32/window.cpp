/*
implementation of win32 window
*/

#include <cpaf/win32/gui/window.h>

using namespace cpaf::win32::gui;

#define CLASSNAME "cpaf::Window"

static WNDCLASSEX wnd_class = {
    sizeof(WNDCLASSEX),
    CS_DBLCLKS,
    (WNDPROC)widget_wndproc, // subclass to use window_wndproc later
    0,
    0,
    GetModuleHandle(NULL),
    NULL,
    LoadCursor(NULL, IDC_ARROW),
    (HBRUSH)COLOR_BACKGROUND,
    NULL,
    CLASSNAME
};

/*
namespace cpaf {
    namespace win32 {
        namespace gui {

LRESULT CALLBACK window_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window *wnd = get_widget_from_hwnd<Window>(hwnd);

    switch(uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_GETMINMAXINFO:
        {
            MINMAXINFO *info = (MINMAXINFO*)lParam;
            if( wnd )
            {
                if( wnd->m_max_size.width != -1 )
                    info->ptMaxTrackSize.x = wnd->m_max_size.width;
                if( wnd->m_max_size.height != -1 )
                    info->ptMaxTrackSize.y = wnd->m_max_size.height;
                if( wnd->m_min_size.width != -1 )
                    info->ptMinTrackSize.x = wnd->m_min_size.width;
                if( wnd->m_min_size.height != -1 )
                    info->ptMinTrackSize.y = wnd->m_min_size.height;
                return 0;
            }
            else
                break;
        }

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

        } // gui
    } // win32
} // cpaf

*/

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
    CreationInfo info = { this };

    m_hwnd = ::CreateWindowEx(0, CLASSNAME, "Cpaf!!", WS_OVERLAPPEDWINDOW ,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hparent, NULL, ::GetModuleHandle(NULL),
        &info);
}

std::string cpaf::win32::gui::Window::get_title()
{
    int len = ::GetWindowTextLength(m_hwnd) + 1; //GetWindowTextLength doesn't include the terminating NULL char
    LPTSTR buff = new TCHAR[len];
    ::GetWindowText(m_hwnd, buff, len);
    std::string ret(buff);
    delete buff;
    return ret;
}

void cpaf::win32::gui::Window::set_title(const std::string &t)
{
    //! \todo This won't work for unicode...
    ::SetWindowText(m_hwnd, t.c_str());
}
