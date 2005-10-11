/*!
    \file include/cpaf/gtk2/gui/cpaffixed.h
    \brief Custom container derived from GtkFixed
    \date Created: 2005-10-04
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
*/

/* THIS IS A C FILE, DO NOT USE C++ SYNTAX (comments in particular) */

#ifndef CPAF_GTK2_FIXED_H
#define CPAF_GTK2_FIXED_H

#include <gtk/gtkfixed.h>

G_BEGIN_DECLS

/* CpafFixed is a derivation of GtkFixed, modified for our needs
 */

#define CPAF_TYPE_FIXED             (cpaf_fixed_get_type ())
#define CPAF_FIXED(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), CPAF_TYPE_FIXED, CpafFixed))
#define CPAF_FIXED_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), CPAF_TYPE_FIXED, CpafFixedClass))
#define CPAF_IS_FIXED(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CPAF_TYPE_FIXED))
#define CPAF_IS_FIXED_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), CPAF_TYPE_FIXED))
#define CPAF_FIXED_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), CPAF_TYPE_FIXED, CpafFixedClass))

typedef struct _CpafFixed       CpafFixed;
typedef struct _CpafFixedClass  CpafFixedClass;

struct _CpafFixed {
    GtkFixed fixed;
};

struct _CpafFixedClass {
    GtkFixedClass parent_class;
};

GType                 cpaf_fixed_get_type       (void) G_GNUC_CONST;
GtkWidget            *cpaf_fixed_new            (void);

G_END_DECLS

#endif /* CPAF_GTK2_FIXED_H */
