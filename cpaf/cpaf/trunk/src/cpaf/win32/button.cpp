/*
cpaf::win32::gui::Button implementation
*/

#include <cpaf/win32/gui/button.h>
#include <cpaf/gui/widget.h>

cpaf::win32::gui::Button::Button(cpaf::api::gui::Widget *parent)
{
    HWND hparent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        ; //! \todo throw here, buttons must have parents

    m_hwnd = ::CreateWindowEx(0, "BUTTON", "Cpaf!!", WS_CHILD | BS_PUSHBUTTON,
        0, 0, 25, 100, hparent, NULL, ::GetModuleHandle(NULL),
        NULL);

    widget_map_add_hwnd(m_hwnd, this);
}

void cpaf::win32::gui::Button::set_label(const std::string &label)
{

}

std::string cpaf::win32::gui::Button::get_label()
{
    return "";
}
