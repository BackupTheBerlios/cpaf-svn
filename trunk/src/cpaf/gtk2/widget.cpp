/**
 * \file src/cpaf/gtk2/widget.cpp
 * \brief Implementation of gtk2 widget
 * \date 2005-04-05
 */

#include <cpaf/gtk2/gui/widget.h>

#include <gtk/gtk.h>

// for delete_implementation_wrapper
#include <cpaf/private/factory.h>

/*
    There is an inlined default constructor in the header file, you will need to do
    something with this one to work with the create() methods in other classes.
*/

cpaf::gtk2::gui::Widget::Widget(GtkWidget * widget)
    : m_widget(widget)
{
    // Set m_widget to NULL when gtk+ internally destroys the widget
    g_signal_connect_after(m_widget, "destroy",
                           G_CALLBACK (gtk_widget_destroyed), &m_widget);
}

cpaf::gtk2::gui::Widget::~Widget()
{
    if (m_widget)
        gtk_widget_destroy(m_widget);

    // delete our wrapper object safely
    cpaf::gui::factory::delete_implementation_wrapper(this);
}

void cpaf::gtk2::gui::Widget::set_size(const cpaf::Size& s)
{
    // Sets the size request
    /*
        "The size request of a widget is the smallest size a widget can
        accept while still functioning well and drawing itself correctly.
        However in some strange cases a widget may be allocated less than
        its requested size, and in many cases a widget may be allocated
        more space than it requested.

        If the size request in a given direction is -1 (unset), then the
        "natural" size request of the widget will be used instead." - gtk manual
    */
    // Do we want to enforce allocation instead?
    gtk_widget_set_size_request(m_widget, s.width, s.height);
    gtk_widget_queue_resize(m_widget);
}

cpaf::Size cpaf::gtk2::gui::Widget::get_size()
{
    // Is this correct? Maybe use gdk_window_get_frame_extents instead?
    return cpaf::Size(m_widget->allocation.width, m_widget->allocation.height);
}

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
