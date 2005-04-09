/**
 * \file src/cpaf/gtk2/widget.cpp
 * \brief Implementation of gtk2 widget
 * \date 2005-04-05
 */

#include <cpaf/gtk2/gui/widget.h>

#include <gtk/gtk.h>

cpaf::gtk2::gui::Widget::Widget()
{ }

// empty virtual dtor
cpaf::gtk2::gui::Widget::~Widget() { }

void cpaf::gtk2::gui::Widget::enable(bool e)
{
    gtk_widget_set_sensitive(m_widget, e);
}

void cpaf::gtk2::gui::Widget::show(bool show, bool activate)
{
    if (show)
    {
        gtk_widget_show(m_widget);
        if (activate && GTK_WIDGET_CAN_FOCUS(m_widget))
            gtk_widget_grab_focus(m_widget);
    }
    else
        gtk_widget_hide(m_widget);
}

bool cpaf::gtk2::gui::Widget::is_enabled()
{
    return GTK_WIDGET_IS_SENSITIVE(m_widget);
}

bool cpaf::gtk2::gui::Widget::is_shown()
{
    return GTK_WIDGET_VISIBLE(m_widget);
}
