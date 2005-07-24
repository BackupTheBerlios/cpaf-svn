/*!
    \file src/cpaf/win32/widget.cpp
    \brief Implementation of cpaf::win32::gui::Widget
    \date Created: 2005-04-05
*/

#include <cpaf/win32/gui/button.h>
#include <cpaf/win32/exception.h>
#include <cpaf/event/event.h>
#include <cpaf/gui/app.h>

#include <cpaf/win32/msgnames.h>

// for delete_implementation_wrapper
//#include <cpaf/private/factory.h>

cpaf::win32::gui::Widget::Widget()
    : m_delete(true),
    m_wrapper(NULL),
    m_hwnd(0),
    m_old_proc(0),
    m_max_size(-1,-1),
    m_min_size(-1,-1)
{ }

void cpaf::win32::gui::Widget::create(const CreationInfo &info, const cpaf::gui::initializer::WidgetData &params,
        bool parent_required, LPCTSTR class_name, LPCTSTR window_name, int styles, int styles_ex)
{
    m_wrapper = params.m_wrapper;
    m_id = m_wrapper->get_id();

    HWND hparent = NULL;
    cpaf::gui::Widget *parent = params.m_parent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else if( parent_required )
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    int x = params.m_pos.x, y = params.m_pos.y;
    int w = params.m_size.width, h = params.m_size.height;

    if( params.m_default_position )
        x = CW_USEDEFAULT;
    if( params.m_default_size )
        w = CW_USEDEFAULT;

    {
        CreationHook hook; // hook WM_CREATE for initialization stuff
        CreationInfo info(this);

        // I don't set m_hwnd here because process_message() sets it for me
        ::CreateWindowEx(styles_ex, class_name, window_name, styles,
            x, y, w, h, hparent, NULL, ::GetModuleHandle(NULL),
            &info);
    }

    if( !m_hwnd )
        throw cpaf::win32::Exception(cpaf::Exception::NATIVE_HANDLE, ::GetLastError(), __LINE__, __FILE__);

    // show the window if necessary
    if( params.m_show )
        show(true, params.m_activate);
}

void cpaf::win32::gui::Widget::destroy()
{
    // destroy our native widget to start the deletion process
    ::DestroyWindow(m_hwnd);
}

cpaf::win32::gui::Widget::~Widget()
{
    // remove our HWND from the widget map
    cpaf::win32::gui::widget_map_remove_hwnd(m_hwnd);

    // delete our wrapper safely
    //cpaf::gui::factory::delete_implementation_wrapper(this);

    // delete our wrapper
    delete m_wrapper;
}

int cpaf::win32::gui::Widget::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    //DBG_MSG_2("cpaf::win32::gui::Widget::process_message: %s", cpaf::win32::MessageTypeNames[msg]);
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

            // process native event first, because m_old_proc will be invalid once
            // 'delete this' is executed
            int ret;
            if( m_old_proc )
                ret = ::CallWindowProc(m_old_proc, hwnd, msg, w_param, l_param);
            else
                ret = ::DefWindowProc(hwnd, msg, w_param, l_param);

            // delete ourself (and our wrapper)
            /*!
                \todo I cannot delete myself here because I have not recieved WM_DESTROY events
                for child windows yet. I will not be able to recieve child WM_DESTROY events
                until the next message loop iteration so I must que the deletion of this object
            */

            // queue ourselves for deletion
            cpaf::win32::gui::widget_deletion_stack_push(this);

            
            return ret;
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
                    cpaf::event::Event click_event(cpaf::event::BUTTON_CLICK, btn->get_id());
                    cpaf::event::get_manager().send_event(click_event);
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

/**********************************************

  Implementation specific functions

**********************************************/

void cpaf::win32::gui::Widget::set_window_text(const std::string &str)
{
    //! \todo This won't work for unicode...
    ::SetWindowText(m_hwnd, str.c_str());
}

std::string cpaf::win32::gui::Widget::get_window_text() const
{
    //! \todo Clean this function when we figure out what we are doing with strings
    int len = ::GetWindowTextLength(m_hwnd) + 1; //GetWindowTextLength doesn't include the terminating NULL char
    LPTSTR buff = new TCHAR[len];
    ::GetWindowText(m_hwnd, buff, len);
    std::string ret(buff);
    delete buff;
    return ret;
}
