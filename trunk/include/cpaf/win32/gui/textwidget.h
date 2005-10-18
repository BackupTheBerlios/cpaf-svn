/*!
    \file include/cpaf/win32/gui/textwidget.h
    \brief win32 version of cpaf::api::gui::TextWidget
    \date Created: 2005-07-17
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

#ifndef CPAF_WIN32_GUI_TEXTWIDGET_H
#define CPAF_WIN32_GUI_TEXTWIDGET_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/textwidget.h>
#include <cpaf/gui/textwidget.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class TextWidget : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::TextWidget
{
public:
    int process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

    virtual void set_text(const std::string &s);
    virtual std::string get_text() const;
    virtual cpaf::text_range_t get_length() const;

    virtual cpaf::TextRange get_selection_range() const;
    virtual void set_selection_range(const cpaf::TextRange &range);
    virtual bool get_selection_bounds(cpaf::TextRange &range) const;
    virtual void set_selection_bounds(const cpaf::TextRange &range);

    virtual cpaf::text_range_t get_insertion_point() const;
    virtual void set_insertion_point(cpaf::text_range_t pos);

    virtual void delete_range(const cpaf::TextRange &range);
    virtual cpaf::text_range_t insert_text(const std::string &str, cpaf::text_range_t pos);
    virtual cpaf::text_range_t insert_text(const std::string &str);

    virtual void set_max_length(cpaf::text_range_t len);

    virtual void set_read_only(bool b);
    virtual bool is_read_only() const;
};

        } // gui
    } // win32
} // cpaf

#endif
