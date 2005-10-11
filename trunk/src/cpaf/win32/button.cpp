/*!
    \file src/cpaf/win32/button.cpp
    \brief Implementation of cpaf::win32::gui::Button
    \date Created: 2005-04-05
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright (C) 2005 Robin McNeill
    http://www.snakesoft.net
    snakechomp (at) snakesoft [dot] net
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
