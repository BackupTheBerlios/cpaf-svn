/*!
    \file src/cpaf/win32/window.cpp
    \brief Implementation of cpaf::win32::gui::Window
    \date Created: 2005-04-05
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright (C) 2005 Robin McNeill
    http://www.snakesoft.net
    snakechomp (at) snakesoft [dot] net
*/

#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/exception.h>
#include <cpaf/win32/msgnames.h>

using namespace cpaf::win32::gui;

namespace {

const TCHAR CLASSNAME[] = TEXT("cpaf::Window");

WNDCLASSEX wnd_class = {
    sizeof(WNDCLASSEX),
    CS_DBLCLKS,
    (WNDPROC)cpaf::win32::gui::window_wndproc,
    0,
    DLGWINDOWEXTRA,
    GetModuleHandle(NULL),
    NULL,
    LoadCursor(NULL, IDC_ARROW),
    (HBRUSH)(COLOR_WINDOW+1),
    NULL,
    CLASSNAME
};

} // unnamed namespace

LRESULT CALLBACK cpaf::win32::gui::window_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    return ::DefWindowProc(hwnd, msg, w_param, l_param);
}

void Window::create(const cpaf::gui::initializer::WindowData &params)
{
    static bool registered = false;

    // register the window class
    //! \todo This may leak some memory because window classes registered by dll's are not unloaded
    //! by the NT kernel, but they are on flavors of win 95.
    if( !registered )
        ::RegisterClassEx(&wnd_class);

    // get non const initialization params
    cpaf::gui::initializer::WindowData init_params = params;

    int style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, style_ex = WS_EX_CONTROLPARENT;

    // handle client size
    cpaf::Size client_size = init_params.get_client_size();
    {
        RECT rect = {0};
        rect.right = client_size.width;
        rect.bottom = client_size.height;

        ::AdjustWindowRectEx(&rect, style, false, style_ex);

        if( client_size.width != 0 )
            client_size.width = rect.right - rect.left;
        else
            client_size.width = CW_USEDEFAULT;
        if( client_size.height != 0 )
            client_size.height = rect.bottom - rect.top;
        else
            client_size.height = CW_USEDEFAULT;
    }

    // handle window position
    cpaf::Point pos = init_params.get_position();
    if( init_params.default_position() )
        pos.x = pos.y = CW_USEDEFAULT;

    // set the content panel
    HWND w = 0;
    if( params.get_content_panel() )
    {
        m_root_panel = dynamic_cast<Panel*>(params.get_content_panel()->get_impl());
        w = (HWND)m_root_panel->get_handle();
    }
    else
        m_root_panel = 0;
    
    // create a window
    Widget::create(CreationInfo(this), init_params, false, CLASSNAME, params.get_title().c_str(),
        style, style_ex, pos.x, pos.y, client_size.width, client_size.height);

    if( params.get_content_panel() )
    {
        ::SetParent(w, m_hwnd);
        m_root_panel->show(true, false);
    }
}

int Window::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch(msg)
    {
    case WM_SIZE:
        if( m_root_panel )
            m_root_panel->set_size(cpaf::Size(LOWORD(l_param), HIWORD(l_param)));
        break;

    case WM_GETMINMAXINFO:
        {
            cpaf::Size min = m_root_panel->get_min_size();
            cpaf::Size max = m_root_panel->get_max_size();

            cpaf::Size abs_min = client_size_to_absolute(min);
            cpaf::Size abs_max = client_size_to_absolute(max);

            MINMAXINFO *info = (MINMAXINFO*)l_param;
            if( max.width != 0 )
                info->ptMaxTrackSize.x = abs_max.width;
            if( max.height != 0 )
                info->ptMaxTrackSize.y = abs_max.height;
            if( min.width != 0 )
                info->ptMinTrackSize.x = abs_min.width;
            if( min.height != 0 )
                info->ptMinTrackSize.y = abs_min.height;
            return 0;
        }
    }

    return Widget::process_message(hwnd, msg, w_param, l_param);
}

std::string Window::get_title()
{
    return get_window_text();
}

void Window::set_title(const std::string &t)
{
    set_window_text(t);
}

void Window::set_content_panel(cpaf::api::gui::Panel *p)
{
    //! \todo size the root panel
    m_root_panel = dynamic_cast<Panel*>(p);
    ::SetParent((HWND)m_root_panel->get_handle(), m_hwnd);

    // make sure the panel is shown
    m_root_panel->show(true, false);
}

boost::shared_ptr<cpaf::gui::Panel> Window::get_content_panel() const
{
    return m_root_panel->get_wrapper<cpaf::gui::Panel>();
}

void Window::set_min_content_size(const cpaf::Size &size)
{
    //! \todo Implement
}

void Window::set_max_content_size(const cpaf::Size &size)
{
    //! \todo Implement
}

cpaf::Size Window::get_min_content_size() const
{
    //! \todo Implement
    return cpaf::Size(0,0);
}

cpaf::Size Window::get_max_content_size() const
{
    //! \todo Implement
    return cpaf::Size(0,0);
}

void Window::set_client_size(const cpaf::Size &s)
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

cpaf::Size Window::client_size_to_absolute(const cpaf::Size &size)
{
    // find the difference between the current client size and window size
    // and use it to calculate a new window size based on the given client size

    cpaf::Size result = size;
    RECT window_rect, client_rect;
    ::GetWindowRect(m_hwnd, &window_rect);
    ::GetClientRect(m_hwnd, &client_rect);

    result.width += (window_rect.right - window_rect.left) - (client_rect.right);
    result.height += (window_rect.bottom - window_rect.top) - (client_rect.bottom);

    return result;
}
