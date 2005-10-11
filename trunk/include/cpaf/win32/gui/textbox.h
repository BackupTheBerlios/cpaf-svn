/*!
    \file include/cpaf/win32/textbox.h
    \brief win32 version of cpaf::api::gui::TextBox
    \date Created: 2005-07-07
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

#ifndef CPAF_WIN32_GUI_TEXTBOX_H
#define CPAF_WIN32_GUI_TEXTBOX_H

#include <cpaf/win32/gui/textwidget.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/gui/textbox.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class TextBox : public virtual cpaf::win32::gui::TextWidget, public virtual cpaf::api::gui::TextBox
{
public:
    void create(const cpaf::gui::initializer::TextBoxData &params);

    std::string get_text(const cpaf::TextRange &range) const;
};

        } // gui
    } // win32
} // cpaf

#endif
