/**
 * \file src/cpaf/gtk2/entrybox.cpp
 * \brief Implementation of cpaf::gtk2::gui::EntryBox
 * \date Created: 2005-07-22
*/

#include <cpaf/gtk2/gui/entrybox.h>
#include <cpaf/exception.h>
#include <gtk/gtk.h>

void cpaf::gtk2::gui::EntryBox::create(const cpaf::gui::initializer::EntryBoxData &params)
{
    //! \todo Use factory params
    cpaf::gtk2::gui::Widget::create(params, gtk_entry_new());

    GtkWidget * hparent;
    cpaf::gui::Widget *parent = params.get_parent();
    if( parent )
    {
        hparent = GTK_WIDGET(parent->get_handle());
        //! \todo Figure out a better way to use the GtkFixed inside toplevels
        gtk_fixed_put(GTK_FIXED(gtk_bin_get_child(GTK_BIN(hparent))), m_widget, params.get_pos().x, params.get_pos().y);
    }
    else
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    if (!params.get_text().empty())
        set_text(params.get_text());

    /*!
        \note Show is always last - it might realize the widget (if params.m_show == true),
        and we don't want that to happen before all other data is set.
     */
    if (params.get_show())
        show(true, params.get_activate());
}

void cpaf::gtk2::gui::EntryBox::set_text(const std::string &s)
{
    //! \todo std::string -> UTF8
    gtk_entry_set_text(GTK_ENTRY(m_widget), s.c_str());
}

std::string cpaf::gtk2::gui::EntryBox::get_text() const
{
    //! \todo UTF8 -> std::string
    return gtk_entry_get_text(GTK_ENTRY(m_widget));
}

