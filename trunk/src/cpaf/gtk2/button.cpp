/**
 * \file src/cpaf/gtk2/button.cpp
 * \brief Implementation of cpaf::gtk2::gui::Button
 * \date Created: 2005-04-14
 */

#include <cpaf/gtk2/gui/button.h>
#include <cpaf/gtk2/gui/panel.h>
#include <cpaf/exception.h>
#include <gtk/gtk.h>

using namespace cpaf::gtk2::gui;

Button::Button()
    : m_label(NULL)
{ }

void
Button::create (const cpaf::gui::initializer::ButtonData &params)
{
    //! \todo Use factory params
    Widget::create(params, gtk_button_new ());

    //! \todo IMPLEMENT
    cpaf::gui::Panel *parent = params.get_parent();
    if( parent )
    {
        GtkFixed * hparent = GTK_FIXED (parent->get_handle());
        gtk_fixed_put (hparent,
                       m_widget,
                       params.get_pos().x,
                       params.get_pos().y);
    }
    else
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    //! \todo Check in set_label instead, for delayed creation on set_label("") too?
    if (!params.get_label().empty())
        set_label (params.get_label());

    /*!
        \note Show is always last - it might realize the widget (if params.m_show == true),
        and we don't want that to happen before all other data is set.
     */
    if (params.get_show())
        show(true, params.get_activate());
}

void Button::set_label(const std::string &label)
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

std::string Button::get_label()
{
    if(!m_label)
        return "";

    //! \todo UTF8 -> std::string
    return gtk_label_get_text(GTK_LABEL(m_label));
}
