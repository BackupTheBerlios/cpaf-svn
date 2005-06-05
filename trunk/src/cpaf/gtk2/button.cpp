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
{
}

void cpaf::gtk2::gui::Button::create(const cpaf::gui::factory::ButtonData &params)
{
    //! \todo It would be more convenient to initialize this member within the Widget base
    m_wrapper = params.m_wrapper;

    //! \todo Use factory params
    cpaf::gtk2::gui::Widget::create(gtk_button_new());

    GtkWidget * hparent;
    cpaf::gui::Widget *parent = params.m_parent;
    if( parent )
    {
        hparent = GTK_WIDGET(parent->get_handle());
        //! \todo Figure out a better way to use the GtkFixed inside toplevels
        gtk_container_add(GTK_CONTAINER(gtk_bin_get_child(GTK_BIN(hparent))), m_widget);
    }
    else
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    if (params.m_label)
        set_label(m_label);
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
