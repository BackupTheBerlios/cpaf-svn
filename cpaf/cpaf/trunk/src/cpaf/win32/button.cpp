/*
cpaf::win32::gui::Button implementation
*/

#include <cpaf/win32/gui/button.h>
#include <cpaf/gui/widget.h>
#include <cpaf/win32/exception.h>

static WNDPROC old_proc = 0;

// Window procedure for our buttons
static LRESULT CALLBACK button_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    return cpaf::win32::gui::widget_wndproc(old_proc, hwnd, msg, w_param, l_param);
}

cpaf::win32::gui::Button::Button(int id, cpaf::api::gui::Widget *parent)
    : Widget(id)
{
    static bool wnd_proc_replaced = false;

    // this needs to go before the wnd_proc_replaced bit or I get an access violation from VC
    // for what ever stupid reason if the parent is null
    HWND hparent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        throw cpaf::Exception(cpaf::Exception::error_codes::WIDGET_NO_PARENT, __LINE__, __FILE__);

    if( !wnd_proc_replaced )
    {
        wnd_proc_replaced = true;

        // create a temp button to use to replace the system class's window procedure
        // with the widget window procedure
        HWND btn = CreateWindowEx(0, "BUTTON", "", 0, 0, 0, 0, 0,
            ::GetDesktopWindow(), NULL, ::GetModuleHandle(NULL), NULL);

        if( !btn )
            throw cpaf::win32::Exception(cpaf::win32::Exception::error_codes::WIDGET_INIT, ::GetLastError(), __LINE__, __FILE__);
        else
        {
            // replace the old window procedure with our own instead of hooking WM_CREATE
            old_proc = (WNDPROC)::SetClassLong(btn, GCL_WNDPROC, (LONG)button_wndproc);
            m_old_proc = old_proc;
            DestroyWindow(btn);
        }
    }

    CreationInfo info(this);

    m_hwnd = ::CreateWindowEx(0, "BUTTON", "Cpaf!!", WS_CHILD | BS_PUSHBUTTON,
        0, 0, 100, 25, hparent, (HMENU)id, ::GetModuleHandle(NULL),
        &info);

    if( !m_hwnd )
        throw cpaf::win32::Exception(cpaf::Exception::error_codes::NATIVE_HANDLE, ::GetLastError(), __LINE__, __FILE__);
}

void cpaf::win32::gui::Button::set_label(const std::string &label)
{
    set_window_text(label);
}

std::string cpaf::win32::gui::Button::get_label()
{
    return get_window_text();
}
