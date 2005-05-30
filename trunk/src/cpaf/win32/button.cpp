/*
cpaf::win32::gui::Button implementation
*/

#include <cpaf/win32/gui/button.h>
#include <cpaf/gui/widget.h>
#include <cpaf/win32/exception.h>
#include <cpaf/gui/button.h>

cpaf::win32::gui::Button::Button(const cpaf::gui::factory::ButtonData &params)
    : Widget(params)
{
    // this needs to go before the wnd_proc_replaced bit or I get an access violation from VC
    // for what ever stupid reason if the parent is null
    HWND hparent;
    cpaf::gui::Widget *parent = params.m_parent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    CreationInfo info(this);
    int x = params.m_pos.x, y = params.m_pos.y;
    int w = params.m_size.width, h = params.m_size.height;

    {
        CreationHook hook; // hook WM_CREATE for initialization stuff

        m_hwnd = ::CreateWindowEx(0, TEXT("BUTTON"), params.m_label.c_str(), WS_CHILD | BS_PUSHBUTTON,
            x, y, w, h, hparent, NULL, ::GetModuleHandle(NULL),
            &info);
    }

    if( !m_hwnd )
        throw cpaf::win32::Exception(cpaf::Exception::NATIVE_HANDLE, ::GetLastError(), __LINE__, __FILE__);

    // show the window if necessary
    if( params.m_show )
        show(true, params.m_activate);
}

void cpaf::win32::gui::Button::set_label(const std::string &label)
{
    set_window_text(label);
}

std::string cpaf::win32::gui::Button::get_label()
{
    return get_window_text();
}
