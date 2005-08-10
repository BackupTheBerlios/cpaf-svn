/**
 * \file src/cpaf/gtk2/entrybox.cpp
 * \brief Implementation of cpaf::gtk2::gui::EntryBox
 * \date Created: 2005-07-22
*/

#include <cpaf/gtk2/gui/entrybox.h>
#include <cpaf/exception.h>
#include <gtk/gtk.h>

void
cpaf::gtk2::gui::EntryBox::create (const cpaf::gui::initializer::EntryBoxData &params)
{
    //! \todo Use factory params
    cpaf::gtk2::gui::Widget::create (params, gtk_entry_new ());

    GtkWidget * hparent;
    //! \todo IMPLEMENT
    cpaf::gui::Widget *parent = NULL; //params.get_parent();
    if (parent)
    {
        hparent = GTK_WIDGET (parent->get_handle());
        //! \todo Figure out a better way to use the GtkFixed inside toplevels
        gtk_fixed_put (GTK_FIXED (gtk_bin_get_child (GTK_BIN (hparent))),
                       m_widget,
                       params.get_pos().x,
                       params.get_pos().y);
    }
    else
        throw cpaf::Exception (cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

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
cpaf::gtk2::gui::EntryBox::set_text (const std::string &s)
{
    //! \todo std::string -> UTF8
    gtk_entry_set_text (GTK_ENTRY (m_widget), s.c_str());
}

std::string
cpaf::gtk2::gui::EntryBox::get_text () const
{
    //! \todo UTF8 -> std::string
    return gtk_entry_get_text (GTK_ENTRY (m_widget));
}

std::string
cpaf::gtk2::gui::EntryBox::get_text (const cpaf::TextRange &range) const
{
    //! \todo IMPLEMENT
    return "";
}

cpaf::text_range_t
cpaf::gtk2::gui::EntryBox::get_length () const
{
    //! \todo IMPLEMENT
    return 0;
}

cpaf::TextRange
cpaf::gtk2::gui::EntryBox::get_selection_range () const
{
    //! \todo IMPLEMENT
    return cpaf::TextRange();
}

void
cpaf::gtk2::gui::EntryBox::set_selection_range (const cpaf::TextRange &range)
{
    //! \todo IMPLEMENT
}

bool
cpaf::gtk2::gui::EntryBox::get_selection_bounds (cpaf::TextRange &range) const
{
    //! \todo IMPLEMENT
    return true;
}

void
cpaf::gtk2::gui::EntryBox::set_selection_bounds (const cpaf::TextRange &range)
{
    //! \todo IMPLEMENT
}

cpaf::text_range_t
cpaf::gtk2::gui::EntryBox::get_insertion_point () const
{
    return gtk_editable_get_position (GTK_EDITABLE (m_widget));
}

void
cpaf::gtk2::gui::EntryBox::set_insertion_point (cpaf::text_range_t pos)
{
    //! \todo Negativity consideration?
    if (pos == cpaf::TextRange::END)
        pos = -1;

    gtk_editable_set_position (GTK_EDITABLE (m_widget), pos);
}

void
cpaf::gtk2::gui::EntryBox::delete_range (const cpaf::TextRange &range)
{
    cpaf::TextRange r(range);
    r.normalize();
    gtk_editable_delete_text (GTK_EDITABLE (m_widget),
                              r.first,
                              (r.second == cpaf::TextRange::END) ? -1 : r.second);
}

cpaf::text_range_t
cpaf::gtk2::gui::EntryBox::insert_text (const std::string &str,
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
cpaf::gtk2::gui::EntryBox::insert_text (const std::string &str)
{
    //! \todo IMPLEMENT
}

void
cpaf::gtk2::gui::EntryBox::set_max_length (cpaf::text_range_t len)
{
    //! \todo -1 is supposed to be converted to 0 - unless we change the docs
    gtk_entry_set_max_length (GTK_ENTRY (m_widget), len);
}

void
cpaf::gtk2::gui::EntryBox::set_read_only (bool b)
{
    gtk_editable_set_editable (GTK_EDITABLE (m_widget), !b);
}

bool
cpaf::gtk2::gui::EntryBox::is_read_only () const
{
    return !gtk_editable_get_editable (GTK_EDITABLE (m_widget));
}

void
cpaf::gtk2::gui::EntryBox::set_password_mode (bool mode)
{
    gtk_entry_set_visibility (GTK_ENTRY (m_widget), !mode);
}

bool
cpaf::gtk2::gui::EntryBox::get_password_mode ()
{
    return !gtk_entry_get_visibility (GTK_ENTRY (m_widget));
}
