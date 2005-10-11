/*!
    \file src/cpaf/gtk2/entrybox.cpp
    \brief Implementation of cpaf::gtk2::gui::EntryBox
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

#include <cpaf/gtk2/gui/entrybox.h>
#include <cpaf/gtk2/gui/panel.h>
#include <cpaf/exception.h>
#include <cpaf/event/event.h>

#include <gtk/gtk.h>

using namespace cpaf::gtk2::gui;

extern "C" {
static void
cpaf_editable_changed(GtkEditable * gtkeditable,
                      EntryBox * widget)
{
    widget->send_event(cpaf::event::TEXT_CHANGED);
}
} // extern "C"

void
EntryBox::create (const cpaf::gui::initializer::EntryBoxData &params)
{
    //! \todo Use factory params
    Widget::create (params, gtk_entry_new ());

    //! \todo IMPLEMENT
    boost::shared_ptr<cpaf::gui::Panel> parent = params.get_parent();
    if (parent)
    {
        GtkFixed * hparent = GTK_FIXED (parent->get_handle());
        gtk_fixed_put (hparent,
                       m_widget,
                       params.get_pos().x,
                       params.get_pos().y);
    }
    else
        throw cpaf::Exception (cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    g_signal_connect (m_widget, "changed",
                      G_CALLBACK (cpaf_editable_changed),
                      this);

    if (!params.get_text().empty())
        set_text (params.get_text());

    /*!
        \note Show is always last - it might realize the widget (if params.m_show == true),
        and we don't want that to happen before all other data is set.
     */
    if (params.get_show())
        show (true, params.get_activate());
}

void
EntryBox::set_text (const std::string &s)
{
    //! \todo std::string -> UTF8
    gtk_entry_set_text (GTK_ENTRY (m_widget), s.c_str());
}

std::string
EntryBox::get_text () const
{
    //! \todo UTF8 -> std::string
    return gtk_entry_get_text (GTK_ENTRY (m_widget));
}

std::string
EntryBox::get_text (const cpaf::TextRange &range) const
{
    //! \todo IMPLEMENT
    return "";
}

cpaf::text_range_t
EntryBox::get_length () const
{
    //! \todo IMPLEMENT
    return 0;
}

cpaf::TextRange
EntryBox::get_selection_range () const
{
    //! \todo IMPLEMENT
    return cpaf::TextRange();
}

void
EntryBox::set_selection_range (const cpaf::TextRange &range)
{
    //! \todo IMPLEMENT
}

bool
EntryBox::get_selection_bounds (cpaf::TextRange &range) const
{
    //! \todo IMPLEMENT
    return true;
}

void
EntryBox::set_selection_bounds (const cpaf::TextRange &range)
{
    //! \todo IMPLEMENT
}

cpaf::text_range_t
EntryBox::get_insertion_point () const
{
    return gtk_editable_get_position (GTK_EDITABLE (m_widget));
}

void
EntryBox::set_insertion_point (cpaf::text_range_t pos)
{
    //! \todo Negativity consideration?
    if (pos == cpaf::TextRange::END)
        pos = -1;

    gtk_editable_set_position (GTK_EDITABLE (m_widget), pos);
}

void
EntryBox::delete_range (const cpaf::TextRange &range)
{
    cpaf::TextRange r(range);
    r.normalize();
    gtk_editable_delete_text (GTK_EDITABLE (m_widget),
                              r.first,
                              (r.second == cpaf::TextRange::END) ? -1 : r.second);
}

cpaf::text_range_t
EntryBox::insert_text (const std::string &str,
                       cpaf::text_range_t p)
{
    text_range_t pos = p;
    //! \todo std::string -> UTF8
    gtk_editable_insert_text (GTK_EDITABLE (m_widget),
                              str.c_str(),
                              str.length(),
                              &pos);
    return pos;
}

cpaf::text_range_t
EntryBox::insert_text (const std::string &str)
{
    //! \todo IMPLEMENT
    return 0;
}

void
EntryBox::set_max_length (cpaf::text_range_t len)
{
    //! \todo -1 is supposed to be converted to 0 - unless we change the docs
    gtk_entry_set_max_length (GTK_ENTRY (m_widget), len);
}

void
EntryBox::set_read_only (bool b)
{
    gtk_editable_set_editable (GTK_EDITABLE (m_widget), !b);
}

bool
EntryBox::is_read_only () const
{
    return !gtk_editable_get_editable (GTK_EDITABLE (m_widget));
}

void
EntryBox::set_password_mode (bool mode)
{
    gtk_entry_set_visibility (GTK_ENTRY (m_widget), !mode);
}

bool
EntryBox::get_password_mode ()
{
    return !gtk_entry_get_visibility (GTK_ENTRY (m_widget));
}
