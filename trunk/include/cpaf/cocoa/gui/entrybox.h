/*!
    \file include/cpaf/cocoa/entrybox.h
    \brief Cocoa version of cpaf::api::gui::EntryBox
    \date Created: 2005-07-14
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

    Copyright (C) 2005 Thomas Steinacher
    http://www.eggdrop.ch/
    tom (at) eggdrop [dot] ch
*/

#ifndef CPAF_COCOA_GUI_ENTRYBOX_H
#define CPAF_COCOA_GUI_ENTRYBOX_H

#include <cpaf/cocoa/gui/textwidget.h>
#include <cpaf/api/gui/entrybox.h>
#include <cpaf/gui/entrybox.h>

#include <string>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class EntryBox : public virtual cpaf::cocoa::gui::TextWidget, public virtual cpaf::api::gui::EntryBox
{
public:
    EntryBox() { }

    void create(const cpaf::gui::initializer::EntryBoxData &params);
    void set_password_mode(bool mode);
    bool get_password_mode();

    void set_text(const std::string &s);
    std::string get_text() const;
    std::string get_text(const cpaf::TextRange &range) const;
    cpaf::text_range_t get_length() const;

    cpaf::TextRange get_selection_range() const;
    void set_selection_range(const cpaf::TextRange &range);
    bool get_selection_bounds(cpaf::TextRange &range) const;
    void set_selection_bounds(const cpaf::TextRange &range);

    cpaf::text_range_t get_insertion_point() const;
    void set_insertion_point(cpaf::text_range_t pos);

    void delete_range(const cpaf::TextRange &range);
    cpaf::text_range_t insert_text(const std::string &str, cpaf::text_range_t pos);
    cpaf::text_range_t insert_text(const std::string &str);

    void set_max_length(cpaf::text_range_t len);

    void set_read_only(bool b);
    bool is_read_only() const;

};

        } // gui
    } // cocoa
} // cpaf

#endif
