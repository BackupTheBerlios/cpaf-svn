/**
 * \file src/cpaf/gtk2/window.cpp
 * \brief Implementation of gtk2 window
 * \date 2005-04-05
 */

#include <cpaf/gtk2/gui/window.h>
#include <cpaf/gtk2/gui/panel.h>
#include <cpaf/gtk2/utils.h>

#include <gtk/gtk.h>

using namespace cpaf::gtk2::gui;

Window::Window() { }

void Window::create(const cpaf::gui::initializer::WindowData &params)
{
    Widget::create(params, gtk_window_new(GTK_WINDOW_TOPLEVEL));

    set_client_size(params.get_client_size());

    boost::shared_ptr<cpaf::gui::Widget> parent = params.get_parent();
    if (parent)
        gtk_window_set_transient_for(GTK_WINDOW(m_widget),
                                     GTK_WINDOW(parent->get_handle()));

    if (params.get_content_panel())
    {
        Panel * root_panel = dynamic_cast<Panel*>(params.get_content_panel()->get_impl());
        gtk_container_add (GTK_CONTAINER (m_widget),
                           GTK_WIDGET (root_panel->get_handle()));
        params.get_content_panel()->show(true, false);
    }

    // Quit the application for now when the toplevel is closed
    //! \todo Find a different sensible thing to quit the application with
    g_signal_connect_swapped(m_widget, "delete-event",
                             G_CALLBACK (gtk_main_quit), NULL);

    /*!
        \note Show is always last - it might realize the widget (if params.m_show == true),
        and we don't want that to happen before all other data is set.
     */
    if (params.get_show())
        show(true, params.get_activate());
}

//! \todo Deal with DEFAULT_* values
void Window::set_size(const cpaf::Size &s)
{
    int w, h;

    if( gtk_window_get_decorated( GTK_WINDOW(m_widget ) ) )
    {
        long * extents;
        //! \todo What's the best estimation for these?
        w = 10; // estimated width of left+right extent
        h = 26; // estimated height of top+bottom extent

        if ( (extents = cpaf::gtk2::utils::get_extents(m_widget)) != NULL )
        {
            w = extents[cpaf::gtk2::utils::LEFT] + extents[cpaf::gtk2::utils::RIGHT];
            h = extents[cpaf::gtk2::utils::TOP] + extents[cpaf::gtk2::utils::BOTTOM];
            XFree(extents);
        }

        if ( (w = s.width - w) < 1)
            w = 1;
        if ( (h = s.height - h) < 1)
            h = 1;
    }
    else
    {
        w = s.width;
        h = s.height;
    }

    gtk_window_resize(GTK_WINDOW(m_widget), w, h);
}

//! \todo Deal with DEFAULT_* values
void Window::set_min_size(const cpaf::Size &s)
{
    GdkGeometry hints;
    hints.min_width = s.width;
    hints.min_height = s.height;
    gtk_window_set_geometry_hints(GTK_WINDOW(m_widget),
                                  NULL,
                                  &hints,
                                  GDK_HINT_MIN_SIZE);
}

//! \todo Deal with DEFAULT_* values
void Window::set_max_size(const cpaf::Size &s)
{
    GdkGeometry hints;
    hints.max_width = s.width;
    hints.max_height = s.height;
    gtk_window_set_geometry_hints(GTK_WINDOW(m_widget),
                                  NULL,
                                  &hints,
                                  GDK_HINT_MAX_SIZE);
}

//! \todo Deal with DEFAULT_* values
void Window::set_position(const cpaf::Point &p)
{
    gtk_window_move(GTK_WINDOW(m_widget), p.x, p.y);
}

cpaf::Size Window::get_size() const
{
    if(GTK_WIDGET_REALIZED(m_widget))
    {
        GdkRectangle rect;
        gdk_window_get_frame_extents(m_widget->window, &rect);
        return cpaf::Size(rect.width, rect.height);
    }
    else
    //! \todo realization: Maybe just realize above if not already done?
    {
        gint width, height;
        GtkRequisition req;
        gtk_window_get_default_size(GTK_WINDOW(m_widget), &width, &height);

        if (width == -1 || height == -1)
        {
            //! \todo multihead: GdkScreen must be associated with the widget (font sizes)
            gtk_widget_size_request(m_widget, &req);

            if (width == -1)
                width = req.width;
            if (height == -1)
                height = req.height;
        }

        //! \todo EWMH: Add expected wm frame sizes
        return cpaf::Size(width, height);
    }
}

struct _GtkWindowGeometryInfo
{
    GdkGeometry geometry; /* Geometry hints */
    // ...
    // We don't care what the remaining fields are.
};

cpaf::Size Window::get_min_size() const
{
    GtkWindowGeometryInfo *info = GTK_WINDOW(m_widget)->geometry_info;
    if (!info)
        return cpaf::Size(-1, -1);

    //! \todo Are info->geometry.min_*'s -1 if set_geometry_hints hasn't been called?
    // Unclear at first look at gtk+ src.
    return cpaf::Size(info->geometry.min_width, info->geometry.min_height);
}

cpaf::Size Window::get_max_size() const
{
    GtkWindowGeometryInfo *info = GTK_WINDOW(m_widget)->geometry_info;
    if (!info)
        return cpaf::Size(-1, -1);

    //! \todo Are info->geometry.max_*'s -1 if set_geometry_hints hasn't been called?
    // Unclear at first look at gtk+ src.
    return cpaf::Size(info->geometry.max_width, info->geometry.max_height);
}

cpaf::Point Window::get_position() const
{
    gint root_x, root_y;
    gtk_window_get_position(GTK_WINDOW(m_widget), &root_x, &root_y);
    return cpaf::Point(root_x, root_y);
}

void Window::show(bool show, bool activate)
{
    if (show)
    {
        //! \todo GTK2.6 specific: Sets _NET_WM_USER_TIME to 0 among other things if activate == true
        gtk_window_set_focus_on_map(GTK_WINDOW(m_widget), activate);
        gtk_widget_show(m_widget);
    }
    else
        gtk_widget_hide(m_widget);
}

void Window::set_title(const std::string &t)
{
    //! \todo std::string -> UTF8
    gtk_window_set_title(GTK_WINDOW(m_widget), t.c_str());
}

std::string Window::get_title()
{
    //! \todo UTF8 -> std::string
    return gtk_window_get_title(GTK_WINDOW(m_widget));
}

//! \todo Deal with DEFAULT_* values
void Window::set_client_size(const cpaf::Size &s)
{
    /*!
        \todo Add visible size of the menubar/statusbar, and similar non-drawable portions in the
        window. Alternatively if we treat the window as a container, we might be able to
        just set the size of the widget, that inside the container that is equal to the client
        area, with gdk_window_resize.
     */
    g_message("Resizing %s window to %f %f\n", GTK_WIDGET_MAPPED(m_widget) ? "shown" : "hidden", s.width, s.height);
    gtk_window_resize(GTK_WINDOW(m_widget), s.width, s.height);
}

cpaf::Size Window::get_client_size()
{
    gint width, height;
    //! \todo subtract menubar/toolbar/statusbar etc in a cross-platform manner
    // race condition? configure_event instead?
    gtk_window_get_size(GTK_WINDOW(m_widget), &width, &height);
    return cpaf::Size(width, height);
}

cpaf::Point Window::get_client_position()
{
    //! \todo What's the best estimation for these?
    int x = 5, y = 21;

    long * extents;
    if ( (extents = cpaf::gtk2::utils::get_extents(m_widget)) != NULL )
    {
        x = extents[cpaf::gtk2::utils::LEFT];
        y = extents[cpaf::gtk2::utils::TOP];
        XFree(extents);
    }

    //! \todo Add menubar/attached toolbar height.
    return cpaf::Point(x, y);
}

void Window::set_content_panel(cpaf::api::gui::Panel *p)
{
    //! \todo
    g_warning("Window::set_content_panel not yet implemented.");
}

boost::shared_ptr<cpaf::gui::Panel> Window::get_content_panel() const
{
    //! \todo
    g_warning("Window::get_content_panel not yet implemented");
    return boost::shared_ptr<cpaf::gui::Panel>();
}
