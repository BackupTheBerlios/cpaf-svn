/*!
    \file include/cpaf/win32/gui/button.h
    \brief win32 version of cpaf::api::gui::Button
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

#ifndef CPAF_WIN32_GUI_BUTTON_H
#define CPAF_WIN32_GUI_BUTTON_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/button.h>

// for the initializer factory
#include <cpaf/gui/button.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Button : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::Button
{
public:
    Button() { }

    void create(const cpaf::gui::initializer::ButtonData &params);

    int process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

    virtual void set_label(const std::string &label);
    virtual std::string get_label();
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_BUTTON_H
