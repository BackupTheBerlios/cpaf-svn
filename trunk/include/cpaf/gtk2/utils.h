/*!
    \file include/cpaf/gtk2/utils.h
    \brief Gtk2 utils
    \date Created: 2005-04-07
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright (C) 2005 Mart Raudsepp
    leio (at) dustbite [dot] net
*/

#ifndef CPAF_GTK2_UTILS_H
#define CPAF_GTK2_UTILS_H

#include <cpaf/gtk2/gtk.h>

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
