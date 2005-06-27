/**
 * \file src/cpaf/gtk2/button.cpp
 * \brief Implementation of gtk2 button
 * \date 2005-04-14
 */

#include <cpaf/gtk2/gui/button.h>
#include <cpaf/exception.h>
#include <gtk/gtk.h>

cpaf::gtk2::gui::Button::Button()
    : m_label(NULL)
{ }

void cpaf::gtk2::gui::Button::create(const cpaf::gui::initializer::ButtonData &params)
{
    //! \todo Use factory params
    cpaf::gtk2::gui::Widget::create(params, gtk_button_new());

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

    //! \todo Check in set_label instead, for delayed creation on set_label("") too?
    if (!params.m_label.empty())
        set_label(params.m_label);

    /*!
        \note Show is always last - it might realize the widget (if params.m_show == true),
        and we don't want that to happen before all other data is set.
     */
    if (params.m_show)
        show(params.m_show, params.m_activate);
}

void cpaf::gtk2::gui::Button::set_label(const std::string &label)
{
    //! \todo std::string -> UTF8
    if (!m_label)
    {
        m_label = gtk_label_new(label.c_str());
        gtk_widget_show(m_label);
        gtk_container_add(GTK_CONTAINER(m_widget), m_label);
    }
    else
        gtk_label_set_text(GTK_LABEL(m_label), label.c_str());
}

std::string cpaf::gtk2::gui::Button::get_label()
{
    if(!m_label)
        return "";

    //! \todo UTF8 -> std::string
    return gtk_label_get_text(GTK_LABEL(m_label));
}
