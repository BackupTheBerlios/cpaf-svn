/**
 * \file src/cpaf/gtk2/window.cpp
 * \brief Implementation of gtk2 window
 * \date 2005-04-05
 */

#include <cpaf/gtk2/gui/window.h>
#include <cpaf/gtk2/utils.h>

#include <gtk/gtk.h>

cpaf::gtk2::gui::Window::Window()
{
    m_widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Quit the application for now when the toplevel is closed
    g_signal_connect_swapped(G_OBJECT(m_widget), "delete-event", gtk_main_quit, NULL);
}

cpaf::gtk2::gui::Window::~Window()
{
    gtk_widget_destroy(m_widget);
}

void cpaf::gtk2::gui::Window::set_size(const cpaf::Size &s)
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
            w = extents[CPAF_EXTENT_LEFT] + extents[CPAF_EXTENT_RIGHT];
            h = extents[CPAF_EXTENT_TOP] + extents[CPAF_EXTENT_BOTTOM];
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

void cpaf::gtk2::gui::Window::set_min_size(const cpaf::Size &s)
{
    GdkGeometry hints;
    hints.min_width = s.width;
    hints.min_height = s.height;
    gtk_window_set_geometry_hints(GTK_WINDOW(m_widget),
                                  NULL,
                                  &hints,
                                  GDK_HINT_MIN_SIZE);
}

void cpaf::gtk2::gui::Window::set_max_size(const cpaf::Size &s)
{
    GdkGeometry hints;
    hints.max_width = s.width;
    hints.max_height = s.height;
    gtk_window_set_geometry_hints(GTK_WINDOW(m_widget),
                                  NULL,
                                  &hints,
                                  GDK_HINT_MAX_SIZE);
}

void cpaf::gtk2::gui::Window::set_position(const cpaf::Point &p)
{
    gtk_window_move(GTK_WINDOW(m_widget), p.x, p.y);
}

cpaf::Size cpaf::gtk2::gui::Window::get_size()
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

cpaf::Size cpaf::gtk2::gui::Window::get_min_size()
{
    GtkWindowGeometryInfo *info = GTK_WINDOW(m_widget)->geometry_info;
    if (!info)
        return cpaf::Size(-1, -1);

    //! \todo Are info->geometry.min_*'s -1 if set_geometry_hints hasn't been called?
    // Unclear at first look at gtk+ src.
    return cpaf::Size(info->geometry.min_width, info->geometry.min_height);
}

cpaf::Size cpaf::gtk2::gui::Window::get_max_size()
{
    GtkWindowGeometryInfo *info = GTK_WINDOW(m_widget)->geometry_info;
    if (!info)
        return cpaf::Size(-1, -1);

    //! \todo Are info->geometry.max_*'s -1 if set_geometry_hints hasn't been called?
    // Unclear at first look at gtk+ src.
    return cpaf::Size(info->geometry.max_width, info->geometry.max_height);
}

cpaf::Point cpaf::gtk2::gui::Window::get_position()
{
    gint root_x, root_y;
    gtk_window_get_position(GTK_WINDOW(m_widget), &root_x, &root_y);
    return cpaf::Point(root_x, root_y);
}

void cpaf::gtk2::gui::Window::show(bool show, bool activate)
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

void cpaf::gtk2::gui::Window::set_title(const std::string &t)
{
    //! \todo std::string -> UTF8
    gtk_window_set_title(GTK_WINDOW(m_widget), t.c_str());
}

std::string cpaf::gtk2::gui::Window::get_title()
{
    //! \todo UTF8 -> std::string
    return gtk_window_get_title(GTK_WINDOW(m_widget));
}

void cpaf::gtk2::gui::Window::set_client_size(const cpaf::Size &s)
{
    /*!
        \todo Add visible size of the menubar/statusbar, and similar non-drawable portions in the
        window. Alternatively if we treat the window as a container, we might be able to
        just set the size of the widget, that inside the container that is equal to the client
        area, with gdk_window_resize.
     */
    gtk_window_resize(GTK_WINDOW(m_widget), s.width, s.height);
}

cpaf::Size cpaf::gtk2::gui::Window::get_client_size()
{
    gint width, height;
    //! \todo subtract menubar/toolbar/statusbar etc in a cross-platform manner
    // race condition? configure_event instead?
    gtk_window_get_size(GTK_WINDOW(m_widget), &width, &height);
    return cpaf::Size(width, height);
}

cpaf::Point cpaf::gtk2::gui::Window::get_client_position()
{
    //! \todo What's the best estimation for these?
    int x = 5, y = 21;

    long * extents;
    if ( (extents = cpaf::gtk2::utils::get_extents(m_widget)) != NULL )
    {
        x = extents[CPAF_EXTENT_LEFT];
        y = extents[CPAF_EXTENT_TOP];
        XFree(extents);
    }

    //! \todo Add menubar/attached toolbar height.
    return cpaf::Point(x, y);
}
