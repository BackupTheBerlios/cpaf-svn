/**
 * \file src/cpaf/gtk2/window.cpp
 * \brief Implementation of gtk2 window
 * \date 2005-04-05
 */

#include <cpaf/gtk2/gui/window.h>

#include <gtk/gtk.h>

cpaf::gtk2::gui::Window::Window()
{
    m_widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
}

void cpaf::gtk2::gui::Window::set_size(cpaf::Size s)
{
    gtk_window_resize(GTK_WINDOW(m_widget), s.x, s.y);
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
    //! \todo realization: Maybe should just make sure it's realized?
    {
        gint width, height;
        GtkRequisition req;
        gtk_window_get_default_size(GTK_WINDOW(m_widget), &width, &height);

        if (width == -1 || height == -1)
        {
            //! \todo multihead: GdkScreen must be associated with the widget (font sizes)
            gtk_widget_size_request(m_widget, req);

            if (width == -1)
                width = req.width;
            if (height == -1)
                height = req.height;
        }

        //! \todo EWMH: Add expected wm frame sizes?
        return cpaf::Size(width, height);
    }
}

void cpaf::win32::gui::Window::show(bool show, bool activate)
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

std::string cpaf::gtk2::gui::Window::get_title()
{
    //! \todo UTF8 -> std::string
    return gtk_window_get_title(GTK_WINDOW(m_widget));
}
