/**
 * \file src/cpaf/gtk2/widget.cpp
 * \brief Implementation of gtk2 widget
 * \date 2005-04-05
 */

#include <cpaf/gtk2/gui/widget.h>

#include <gtk/gtk.h>

// for delete_implementation_wrapper
#include <cpaf/private/factory.h>

using namespace cpaf::gtk2::gui;

Widget::Widget()
    : m_wrapper(NULL),
      m_widget(NULL)
{ }

void Widget::create(const cpaf::gui::initializer::WidgetData &params, GtkWidget * widget)
{
    m_wrapper = params.get_wrapper();
    m_widget = widget;

    // Set m_widget to NULL when gtk+ internally destroys the widget
    g_signal_connect_after(m_widget, "destroy",
                           G_CALLBACK (gtk_widget_destroyed), &m_widget);

    if (!params.use_default_size())
        set_size(params.get_size());

    //! \todo Uncomment after all set_{min,max}_size methods are aware of the DEFAULT_* values
    //set_min_size(params.m_min_size);
    //set_max_size(params.m_max_size);

    if (!params.use_default_pos())
        set_position(params.get_pos());

    enable(params.get_enable());

    /*!
        \todo Make sure nothing above realizes the control, and change order appropriately
        if something does. E.g show() is in all derived class create()'s instead of here.
     */
}

void Widget::destroy()
{
    //! \todo Add whatever is needed here.
}

Widget::~Widget()
{
    if (m_widget)
        gtk_widget_destroy(m_widget);

    // delete our wrapper object safely
    //cpaf::gui::factory::delete_implementation_wrapper(this);

    // delete our wrapper
    delete m_wrapper;
}

void Widget::set_size(const cpaf::Size& s)
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

    //! \todo Deal with DEFAULT_* values
    gtk_widget_set_size_request(m_widget, s.width, s.height);
    gtk_widget_queue_resize(m_widget);
}

cpaf::Size Widget::get_size() const
{
    // Is this correct? Maybe use gdk_window_get_frame_extents instead?
    return cpaf::Size(m_widget->allocation.width, m_widget->allocation.height);
}

void Widget::enable(bool e)
{
    gtk_widget_set_sensitive(m_widget, e);
}

void Widget::show(bool show, bool activate)
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

bool Widget::is_enabled() const
{
    return GTK_WIDGET_IS_SENSITIVE(m_widget);
}

bool Widget::is_shown() const
{
    return GTK_WIDGET_VISIBLE(m_widget);
}

cpaf::gui::Panel * Widget::get_parent() const
{
    //! \todo IMPLEMENT
    return (cpaf::gui::Panel*)NULL;
}

cpaf::gui::Window * Widget::get_parent_window() const
{
    //! \todo IMPLEMENT
    return (cpaf::gui::Window*)NULL;
}
