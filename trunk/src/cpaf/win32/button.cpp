/*!
    \file src/cpaf/win32/button.cpp
    \brief Implementation of cpaf::win32::gui::Button
    \date Created: 2005-04-05
*/

#include <cpaf/win32/gui/button.h>

void cpaf::win32::gui::Button::create(const cpaf::gui::initializer::ButtonData &params)
{
    // create a button
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, true, TEXT("BUTTON"), params.get_label().c_str(),
        WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP);
}

int cpaf::win32::gui::Button::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    /*switch(msg)
    {
    case WM_GETDLGCODE:
        return DLGC_BUTTON | DLGC_UNDEFPUSHBUTTON;
    }*/

    return cpaf::win32::gui::Widget::process_message(hwnd, msg, w_param, l_param);
}

void cpaf::win32::gui::Button::set_label(const std::string &label)
{
    set_window_text(label);
}

std::string cpaf::win32::gui::Button::get_label()
{
    return get_window_text();
}
