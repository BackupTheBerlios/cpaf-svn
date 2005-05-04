/*
cpaf::win32::gui::Button implementation
*/

#include <cpaf/win32/gui/button.h>
#include <cpaf/gui/widget.h>
#include <cpaf/win32/exception.h>

static WNDPROC old_proc = 0;

cpaf::win32::gui::Button::Button(int id, cpaf::api::gui::Widget *parent)
    : Widget(id)
{
    DBG_MSG("win32::button ctor");
    static bool wnd_proc_replaced = false;

    // this needs to go before the wnd_proc_replaced bit or I get an access violation from VC
    // for what ever stupid reason if the parent is null
    HWND hparent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        throw cpaf::Exception(cpaf::Exception::error_codes::WIDGET_NO_PARENT, __LINE__, __FILE__);

    CreationInfo info(this);

    {
        cpaf::win32::gui::CreationHook hook; // hook WM_CREATE for initialization stuff

        m_hwnd = ::CreateWindowEx(0, TEXT("BUTTON"), TEXT("Cpaf!!"), WS_CHILD | BS_PUSHBUTTON,
            0, 0, 100, 25, hparent, (HMENU)id, ::GetModuleHandle(NULL),
            &info);
    }

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
