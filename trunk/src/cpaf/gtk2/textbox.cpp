/**
 * \file src/cpaf/gtk2/textbox.cpp
 * \brief Implementation of cpaf::gtk2::gui::TextBox
 * \date Created: 2005-07-08
*/

#include <cpaf/gtk2/gui/textbox.h>
#include <cpaf/exception.h>
#include <gtk/gtk.h>

void cpaf::gtk2::gui::TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
    //! \todo Use factory params
    cpaf::gtk2::gui::Widget::create(params, gtk_entry_new());

    GtkWidget * hparent;
    cpaf::gui::Widget *parent = params.m_parent;
    if( parent )
    {
        hparent = GTK_WIDGET(parent->get_handle());
        //! \todo Figure out a better way to use the GtkFixed inside toplevels
        gtk_fixed_put(GTK_FIXED(gtk_bin_get_child(GTK_BIN(hparent))), m_widget, params.m_pos.x, params.m_pos.y);
    }
    else
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    if (!params.m_text.empty())
        set_text(params.m_text);

    /*!
        \note Show is always last - it might realize the widget (if params.m_show == true),
        and we don't want that to happen before all other data is set.
     */
    if (params.m_show)
        show(params.m_show, params.m_activate);
}

void cpaf::gtk2::gui::TextBox::set_text(const std::string &s)
{
    //! \todo std::string -> UTF8
    gtk_entry_set_text(GTK_ENTRY(m_widget), s.c_str());
}

std::string cpaf::gtk2::gui::TextBox::get_text()
{
    //! \todo UTF8 -> std::string
    return gtk_entry_get_text(GTK_ENTRY(m_widget));
}
