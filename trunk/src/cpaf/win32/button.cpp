/*!
    \file src/cpaf/win32/button.cpp
    \brief Implementation of cpaf::win32::gui::Button
    \date Created: 2005-04-05
*/

#include <cpaf/win32/gui/button.h>

using namespace cpaf::win32::gui;

void Button::create(const cpaf::gui::initializer::ButtonData &params)
{
    // create a button
    Widget::create(CreationInfo(this), params, true, TEXT("BUTTON"), params.get_label().c_str(),
        WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP);
}

int Button::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    /*switch(msg)
    {
    case WM_GETDLGCODE:
        return DLGC_BUTTON | DLGC_UNDEFPUSHBUTTON;
    }*/

    return Widget::process_message(hwnd, msg, w_param, l_param);
}

void Button::set_label(const std::string &label)
{
    set_window_text(label);
}

std::string Button::get_label()
{
    return get_window_text();
}
