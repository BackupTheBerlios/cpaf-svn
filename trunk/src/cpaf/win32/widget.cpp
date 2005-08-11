/*!
    \file src/cpaf/win32/widget.cpp
    \brief Implementation of cpaf::win32::gui::Widget
    \date Created: 2005-04-05
*/

#include <cpaf/win32/gui/panel.h>
#include <cpaf/win32/gui/button.h>
#include <cpaf/win32/exception.h>
#include <cpaf/event/event.h>
#include <cpaf/gui/app.h>

#include <cpaf/win32/msgnames.h>

// for delete_implementation_wrapper
//#include <cpaf/private/factory.h>

#include <cpaf/gui/panel.h>
#include <cpaf/gui/window.h>

using namespace cpaf::win32::gui;

Widget::Widget()
    : m_delete(true),
    m_wrapper(NULL),
    m_hwnd(0),
    m_old_proc(0),
    m_max_size(-1,-1),
    m_min_size(-1,-1)
{ }

void Widget::create(const CreationInfo &info, const cpaf::gui::initializer::WidgetData &params,
        bool parent_required, LPCTSTR class_name, LPCTSTR window_name, int styles, int styles_ex)
{
    m_wrapper = params.get_wrapper();
    m_id = m_wrapper->get_id();

    HWND hparent = NULL;
    cpaf::gui::Panel *parent = params.get_parent();
    if( parent )
        hparent = (HWND)parent->get_handle();
    else if( parent_required )
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);
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

        m_hwnd = ::CreateWindowEx(styles_ex, class_name, window_name, styles,
            x, y, w, h, hparent, NULL, ::GetModuleHandle(NULL),
            &info);
    }

    if( !m_hwnd )
        throw cpaf::win32::Exception(cpaf::Exception::NATIVE_HANDLE, ::GetLastError(), __LINE__, __FILE__);

    // set the default font to what it should be
    ::SendMessage(m_hwnd, WM_SETFONT, (WPARAM)::GetStockObject(DEFAULT_GUI_FONT), 0);

    // show the window if necessary
    if( params.get_show() )
        show(true, params.get_activate());
}

void Widget::destroy()
{
    // destroy our native widget to start the deletion process
    ::DestroyWindow(m_hwnd);
}

Widget::~Widget()
{
    // remove our HWND from the widget map
    widget_map_remove_hwnd(m_hwnd);

    // delete our wrapper safely
    //cpaf::gui::factory::delete_implementation_wrapper(this);

    // delete our wrapper
    delete m_wrapper;
}

int Widget::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    //DBG_MSG_2("Widget::process_message: %s", cpaf::win32::MessageTypeNames[msg]);
    switch(msg)
    {
    case WM_CREATE:
        {
            // make sure we initialize all necessary members before sending WIDGET_CREATE
            // like m_hwnd
            m_hwnd = hwnd;

            // send the creation event
            cpaf::event::Event event(cpaf::event::WIDGET_CREATE, m_id);
            cpaf::event::get_manager().send_event(event);
            break;
        }

    case WM_DESTROY:
        {
            // send destroy event
            cpaf::event::Event event(cpaf::event::WIDGET_DESTROY, m_id);
            cpaf::event::get_manager().send_event(event);

            // queue ourselves for deletion
            widget_deletion_stack_push(this);

            break;
        }

    case WM_GETMINMAXINFO:
        {
            MINMAXINFO *info = (MINMAXINFO*)l_param;
            if( m_max_size.width != -1 )
                info->ptMaxTrackSize.x = m_max_size.width;
            if( m_max_size.height != -1 )
                info->ptMaxTrackSize.y = m_max_size.height;
            if( m_min_size.width != -1 )
                info->ptMinTrackSize.x = m_min_size.width;
            if( m_min_size.height != -1 )
                info->ptMinTrackSize.y = m_min_size.height;
            return 0;
        }

    case WM_COMMAND:
        {
            int command = HIWORD(w_param);

            switch(command)
            {
            case BN_CLICKED:
                {
                    Button *btn = get_widget_from_hwnd<Button>((HWND)l_param);
                    if( btn )
                    {
                        cpaf::event::Event click_event(cpaf::event::BUTTON_CLICK, btn->get_id());
                        cpaf::event::get_manager().send_event(click_event);
                    }
                    return 0;
                }
            }

        }

    }

    if( m_old_proc )
        return ::CallWindowProc(m_old_proc, hwnd, msg, w_param, l_param);
    else
        return ::DefWindowProc(hwnd, msg, w_param, l_param);
}

void Widget::set_size(const cpaf::Size &s)
{
    ::SetWindowPos(m_hwnd, NULL, 0, 0, s.width, s.height, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

cpaf::Size Widget::get_size() const
{
    RECT rect;
    ::GetWindowRect(m_hwnd, &rect);
    return cpaf::Size(rect.right - rect.left, rect.bottom - rect.top);
}

void Widget::set_min_size(const cpaf::Size &s)
{
    m_min_size = s;
}

void Widget::set_max_size(const cpaf::Size &s)
{
    m_max_size = s;
}

cpaf::Size Widget::get_min_size() const
{
    return m_min_size;
}

cpaf::Size Widget::get_max_size() const
{
    return m_max_size;
}

void Widget::set_position(const cpaf::Point &p)
{
    ::SetWindowPos(m_hwnd, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

cpaf::Point Widget::get_position() const
{
    RECT rect;
    ::GetWindowRect(m_hwnd, &rect);
    return cpaf::Point(rect.left, rect.top);
}

void Widget::show(bool show, bool focus)
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

bool Widget::is_shown() const
{
    // comparing against 0 removes the "forcing int to bool, performance warning" warnings of VC
    return ::IsWindowVisible(m_hwnd) != 0;
}

void Widget::enable(bool e)
{
    ::EnableWindow(m_hwnd, e);
}

bool Widget::is_enabled() const
{
    // comparing against 0 removes the "forcing int to bool, performance warning" warnings of VC
    return ::IsWindowEnabled(m_hwnd) != 0;
}

cpaf::gui::Panel *Widget::get_parent() const
{
    Widget *w = get_widget_from_hwnd(::GetParent(m_hwnd));
    if( w )
        return w->get_wrapper<cpaf::gui::Panel>();
    else
        return 0;
}

cpaf::gui::Window *Widget::get_parent_window() const
{
    Widget *w = get_widget_from_hwnd(::GetAncestor(m_hwnd, GA_ROOT));
    if( w )
        return w->get_wrapper<cpaf::gui::Window>();
    else
        DBG_MSG("Bad parent_window HWND");

    return 0;
}

/**********************************************

  Implementation specific functions

**********************************************/

void Widget::set_window_text(const std::string &str)
{
    //! \todo This won't work for unicode...
    ::SetWindowText(m_hwnd, str.c_str());
}

std::string Widget::get_window_text() const
{
    //! \todo Clean this function when we figure out what we are doing with strings
    int len = ::GetWindowTextLength(m_hwnd) + 1; //GetWindowTextLength doesn't include the terminating NULL char
    LPTSTR buff = new TCHAR[len];
    ::GetWindowText(m_hwnd, buff, len);
    std::string ret(buff);
    delete buff;
    return ret;
}
