/*
cpaf::win32::gui::Widget implementation
*/

#include <cpaf/win32/gui/widget.h>
#include <cpaf/win32/gui/window.h>
// for delete_implementation_wrapper
#include <cpaf/private/factory.h>

using namespace cpaf::win32::gui;

namespace cpaf {
    namespace win32 {
        namespace gui {

LRESULT CALLBACK widget_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    Widget *wnd = get_widget_from_hwnd/*<Widget>*/(hwnd);

    switch(msg)
    {
        case WM_NCCREATE:
        {
            break;
        }

        case WM_CREATE:
        {
            // lpCreateParams of CREATESTRUCT specifies the address of a CreationInfo struct.
            // This struct currently contains a pointer to the object creating this window.

            //! \todo Send create event
            LPCREATESTRUCT create = (LPCREATESTRUCT)l_param;
            CreationInfo *info = (CreationInfo*)create->lpCreateParams;
            widget_map_add_hwnd(hwnd, info->wnd);
            break;
        }

        case WM_DESTROY:
            //! \todo send destroy event

            // destroy the widget instance if we need to
            if( wnd && wnd->m_delete )
            {
                wnd->m_delete = false;
                delete wnd;
            }

            //! \todo Decide when to terminate an application
            PostQuitMessage(0);
            break;

        case WM_GETMINMAXINFO:
        {
            MINMAXINFO *info = (MINMAXINFO*)l_param;
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

    return DefWindowProc(hwnd, msg, w_param, l_param);
}

        } // gui
    } // win32
} // cpaf

cpaf::win32::gui::Widget::Widget()
    : m_delete(true),
    m_max_size(-1,-1),
    m_min_size(-1,-1)
{ }

cpaf::win32::gui::Widget::~Widget()
{
    // remove our HWND from the widget map
    cpaf::win32::gui::widget_map_remove_hwnd(m_hwnd);

    // destroy our native window if we need to
    if( m_delete )
    {
        m_delete = false;
        ::DestroyWindow(m_hwnd);
    }

    // delete our wrapper safely
    cpaf::gui::factory::delete_implementation_wrapper(this);
}

int cpaf::win32::gui::Widget::process_message(HWND hwnd, MSG msg, WPARAM w_param, LPARAM l_param)
{
    return 0;
}

void cpaf::win32::gui::Widget::set_size(const cpaf::Size &s)
{
    ::SetWindowPos(m_hwnd, NULL, 0, 0, s.width, s.height, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

cpaf::Size cpaf::win32::gui::Widget::get_size()
{
    RECT rect;
    ::GetWindowRect(m_hwnd, &rect);
    return cpaf::Size(rect.right - rect.left, rect.bottom - rect.top);
}

void cpaf::win32::gui::Widget::set_min_size(const cpaf::Size &s)
{
    m_min_size = s;
}

void cpaf::win32::gui::Widget::set_max_size(const cpaf::Size &s)
{
    m_max_size = s;
}

cpaf::Size cpaf::win32::gui::Widget::get_min_size()
{
    return m_min_size;
}

cpaf::Size cpaf::win32::gui::Widget::get_max_size()
{
    return m_max_size;
}

void cpaf::win32::gui::Widget::set_position(const cpaf::Point &p)
{
    ::SetWindowPos(m_hwnd, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

cpaf::Point cpaf::win32::gui::Widget::get_position()
{
    RECT rect;
    ::GetWindowRect(m_hwnd, &rect);
    return cpaf::Point(rect.left, rect.top);
}

void cpaf::win32::gui::Widget::show(bool show, bool focus)
{
    int cmd;
    if( show )
        if( focus )
            cmd = SW_SHOW;
        else
            cmd = SW_SHOWNA;
    else
        cmd = SW_HIDE;

    ::ShowWindow(m_hwnd, cmd);
}

bool cpaf::win32::gui::Widget::is_shown()
{
    // comparing against 0 removes the "forcing int to bool, performance warning" warnings of VC
    return ::IsWindowVisible(m_hwnd) != 0;
}

void cpaf::win32::gui::Widget::enable(bool e)
{
    ::EnableWindow(m_hwnd, e);
}

bool cpaf::win32::gui::Widget::is_enabled()
{
    // comparing against 0 removes the "forcing int to bool, performance warning" warnings of VC
    return ::IsWindowEnabled(m_hwnd) != 0;
}