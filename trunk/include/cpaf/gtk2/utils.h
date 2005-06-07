/**
 * \file include/cpaf/gtk2/utils.h
 * \brief Gtk2 utils
 * \date Created: 2005-04-07
 */

#ifndef CPAF_GTK2_UTILS_H
#define CPAF_GTK2_UTILS_H

#include <cpaf/gtk2/gtk.h>

/*
#define CPAF_EXTENT_LEFT   0
#define CPAF_EXTENT_RIGHT  1
#define CPAF_EXTENT_TOP    2
#define CPAF_EXTENT_BOTTOM 3
*/

namespace cpaf {
    namespace gtk2 {
        namespace utils {
            enum extents_index {
                LEFT,
                RIGHT,
                TOP,
                BOTTOM,
            };

            /*!
                \brief The returned array must be freed with XFree.
                \return An array of type long where starting from the first
                element the extents are in the following order:
                left, right, top, bottom, or NULL if the passed
                GtkWidget argument does not have a realized X11 drawable or is
                not a toplevel window.
             */
            long * get_extents(GtkWidget *);
        } // utils
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_UTILS_H
