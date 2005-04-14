/*
cpaf::win32::gui::Button implementation
*/

#include <cpaf/win32/gui/button.h>
#include <cpaf/gui/widget.h>

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
            WNDPROC old_proc = (WNDPROC)::SetClassLong(btn, GCL_WNDPROC, (LONG)cpaf::win32::gui::widget_wndproc);
            DestroyWindow(btn);
        }
    }

    HWND hparent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        ; //! \todo throw here, buttons must have parents

    CreationInfo info = { this };

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
