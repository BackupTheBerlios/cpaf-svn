/*
implementation of win32 window
*/

#include <cpaf/win32/gui/window.h>

using namespace cpaf::win32::gui;

#define CLASSNAME "cpaf::Window"

static WNDCLASSEX wnd_class = {
    sizeof(WNDCLASSEX),
    CS_DBLCLKS,
    (WNDPROC)window_proc,
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

LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

cpaf::win32::gui::Window::Window()
    : m_max_size(-1,-1),
    m_min_size(-1,-1)
{
    static bool registered = false;

    // register the window class
    if( !registered )
        ::RegisterClassEx(&wnd_class);

    m_hwnd = ::CreateWindowEx(0, CLASSNAME, "Cpaf!!", WS_OVERLAPPEDWINDOW ,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, ::GetDesktopWindow(), NULL, ::GetModuleHandle(NULL),
        NULL);

    widget_map_add_hwnd(m_hwnd, this);
}

void cpaf::win32::gui::Window::set_size(cpaf::Size s)
{
    ::SetWindowPos(m_hwnd, NULL, 0, 0, s.width, s.height, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

cpaf::Size cpaf::win32::gui::Window::get_size()
{
    RECT rect;
    ::GetWindowRect(m_hwnd, &rect);
    return cpaf::Size(rect.right - rect.left, rect.bottom - rect.top);
}

void cpaf::win32::gui::Window::set_min_size(cpaf::Size s)
{
    m_min_size = s;
}

void cpaf::win32::gui::Window::set_max_size(cpaf::Size s)
{
    m_max_size = s;
}

cpaf::Size cpaf::win32::gui::Window::get_min_size()
{
    return m_min_size;
}

cpaf::Size cpaf::win32::gui::Window::get_max_size()
{
    return m_max_size;
}

void cpaf::win32::gui::Window::set_position(cpaf::Point p)
{
    ::SetWindowPos(m_hwnd, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

cpaf::Point cpaf::win32::gui::Window::get_position()
{
    RECT rect;
    ::GetWindowRect(m_hwnd, &rect);
    return cpaf::Point(rect.left, rect.top);
}

void cpaf::win32::gui::Window::show(bool show, bool activate)
{
    int cmd;
    if( show )
        if( activate )
            cmd = SW_SHOW;
        else
            cmd = SW_SHOWNA;
    else
        cmd = SW_HIDE;

    ::ShowWindow(m_hwnd, cmd);
}

bool cpaf::win32::gui::Window::is_shown()
{
    // comparing against 0 removes the "forcing int to bool, performance warning" warnings of VC
    return ::IsWindowVisible(m_hwnd) != 0;
}

void cpaf::win32::gui::Window::enable(bool e)
{
    ::EnableWindow(m_hwnd, e);
}

bool cpaf::win32::gui::Window::is_enabled()
{
    // comparing against 0 removes the "forcing int to bool, performance warning" warnings of VC
    return ::IsWindowEnabled(m_hwnd) != 0;
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
