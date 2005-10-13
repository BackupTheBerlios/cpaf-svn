/*!
    \file include/cpaf/win32/entrybox.h
    \brief win32 version of cpaf::api::gui::EntryBox
    \date Created: 2005-07-13
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

#ifndef CPAF_WIN32_GUI_ENTRYBOX_H
#define CPAF_WIN32_GUI_ENTRYBOX_H

#include <cpaf/win32/gui/textwidget.h>
#include <cpaf/api/gui/entrybox.h>
#include <cpaf/gui/entrybox.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class EntryBox : public virtual cpaf::win32::gui::TextWidget, public virtual cpaf::api::gui::EntryBox
{
public:
    void create(const cpaf::gui::initializer::EntryBoxData &params);

    int process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

	void set_password_mode(bool mode);
    bool get_password_mode();

    std::string get_text(const cpaf::TextRange &range) const;
};

        } // gui
    } // win32
} // cpaf

#endif
