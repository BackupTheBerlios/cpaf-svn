/*
cpaf::win32::gui::Button implementation
*/

#include <cpaf/win32/gui/button.h>
#include <cpaf/gui/widget.h>

using namespace cpaf::win32::gui;

static WNDPROC old_proc = 0;

// Window procedure for our buttons
static LRESULT CALLBACK button_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    return cpaf::win32::gui::widget_wndproc(old_proc, hwnd, msg, w_param, l_param);
}

cpaf::win32::gui::Button::Button(cpaf::api::gui::Widget *parent)
{
    static bool wnd_proc_replaced = false;

    if( !wnd_proc_replaced )
    {
        wnd_proc_replaced = true;

        // create a temp button to use to replace the system class's window procedure
        // with the widget window procedure
        HWND btn = CreateWindowEx(0, "BUTTON", "", 0, 0, 0, 0, 0,
            ::GetDesktopWindow(), NULL, ::GetModuleHandle(NULL), NULL);

        if( !btn )
            ;//! \todo Um...this is bad, so most likely need to throw here
        else
        {
            // replace the old window procedure with our own instead of hooking WM_CREATE
            old_proc = (WNDPROC)::SetClassLong(btn, GCL_WNDPROC, (LONG)button_wndproc);
            m_old_proc = old_proc;
            DestroyWindow(btn);
        }
    }

    HWND hparent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        ; //! \todo throw here, buttons must have parents

    CreationInfo info(this);

    m_hwnd = ::CreateWindowEx(0, "BUTTON", "Cpaf!!", WS_CHILD | BS_PUSHBUTTON,
        0, 0, 100, 25, hparent, NULL, ::GetModuleHandle(NULL),
        &info);
}

void cpaf::win32::gui::Button::set_label(const std::string &label)
{

}

std::string cpaf::win32::gui::Button::get_label()
{
    return "";
}
