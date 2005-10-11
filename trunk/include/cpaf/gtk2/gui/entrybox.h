/*!
    \file include/cpaf/gtk2/gui/entrybox.h
    \brief Gtk2 version of cpaf::api::gui::EntryBox
    \date Created: 2005-07-22
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
*/

#ifndef CPAF_GTK2_GUI_ENTRYBOX_H
#define CPAF_GTK2_GUI_ENTRYBOX_H

#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/api/gui/entrybox.h>
#include <cpaf/gui/entrybox.h>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class EntryBox : public virtual cpaf::gtk2::gui::Widget, public virtual cpaf::api::gui::EntryBox
{
public:
    void create(const cpaf::gui::initializer::EntryBoxData &params);

    virtual void                set_text            (const std::string&);
    virtual std::string         get_text            () const;
    virtual std::string         get_text            (const cpaf::TextRange&) const;
    virtual cpaf::text_range_t  get_length          () const;

    virtual cpaf::TextRange     get_selection_range () const;
    virtual void                set_selection_range (const cpaf::TextRange&);
    virtual bool                get_selection_bounds(cpaf::TextRange&) const;
    virtual void                set_selection_bounds(const cpaf::TextRange&);

    virtual cpaf::text_range_t  get_insertion_point () const;
    virtual void                set_insertion_point (cpaf::text_range_t);

    virtual void                delete_range        (const cpaf::TextRange&);
    virtual cpaf::text_range_t  insert_text         (const std::string&,
                                                     cpaf::text_range_t);
    virtual cpaf::text_range_t  insert_text         (const std::string&);

    virtual void                set_max_length      (cpaf::text_range_t);

    virtual void                set_read_only       (bool);
    virtual bool                is_read_only        () const;

    virtual void                set_password_mode   (bool);
    virtual bool                get_password_mode   ();
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_ENTRYBOX_H
