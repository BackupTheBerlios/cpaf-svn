/*
implementation of win32 window
*/

#include <cpaf/win32/gui/window.h>

using namespace cpaf::win32::gui;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#define CLASSNAME "cpaf::Window"

static WNDCLASSEX wnd_class = {
    sizeof(WNDCLASSEX),
    CS_DBLCLKS,
    (WNDPROC)WindowProc,
    0,
    0,
    GetModuleHandle(NULL),
    NULL,
    LoadCursor(NULL, IDC_ARROW),
    (HBRUSH)COLOR_BACKGROUND,
    NULL,
    CLASSNAME
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window *wnd = get_widget_from_hwnd<Window>(hwnd);

    switch(uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

cpaf::win32::gui::Window::Window()
{
    static bool registered = false;

    // register the window class
    if( !registered )
        ::RegisterClassEx(&wnd_class);

    m_hwnd = ::CreateWindowEx(0, CLASSNAME, "Cpaf!!", WS_OVERLAPPED,
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

std::string cpaf::win32::gui::Window::get_title()
{
    int len = ::GetWindowTextLength(m_hwnd) + 1; //GetWindowTextLength doesn't include the terminating NULL char
    LPTSTR buff = new TCHAR[len];
    ::GetWindowText(m_hwnd, buff, len);
    std::string ret(buff);
    delete buff;
    return ret;
}
