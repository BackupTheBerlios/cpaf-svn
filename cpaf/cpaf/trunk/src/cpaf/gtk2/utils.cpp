/**
 * \file src/cpaf/gtk2/utils.cpp
 * \brief Gtk2 utils
 * \date 2005-04-07
 */

#include <cpaf/gtk2/utils.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xatom.h>

//! \note X11 specific
long * cpaf::gtk2::utils::get_extents(GtkWidget * widget)
{
    if (!GTK_WIDGET_REALIZED(widget) || !GTK_WIDGET_TOPLEVEL(widget))
        return NULL;

    //! \todo GTK2.2 specific
    if(!gdk_x11_screen_supports_net_wm_hint(
            gdk_drawable_get_screen(widget->window),
            gdk_atom_intern("_NET_FRAME_EXTENTS", false) ) )
        return NULL;

    guchar * data = NULL;
    Atom type;
    gint format;
    gulong nitems;
    gulong bytes_after;
    if (XGetWindowProperty (
            GDK_DISPLAY_XDISPLAY( gdk_drawable_get_display(widget->window) ),
            GDK_WINDOW_XWINDOW(widget->window),
            gdk_x11_get_xatom_by_name_for_display (
                    gdk_drawable_get_display(widget->window),
                    "_NET_FRAME_EXTENTS" ),
            0, // left, right, top, bottom, CARDINAL[4]/32
            G_MAXLONG, // size of long
            false, // do not delete property
            XA_CARDINAL, // 32 bit
            &type, &format, &nitems, &bytes_after, &data
       ) == Success)
    {
        if ((type == XA_CARDINAL) && (format == 32) && (nitems >= 4) && (data))
        {
            long *borders;
            borders = (long*)data;
            return borders;
        }
    }

    return NULL;
}
