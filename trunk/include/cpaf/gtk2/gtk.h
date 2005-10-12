/*!
    \file include/cpaf/gtk2/gtk.h
    \brief Common header for gtk2 implementation
    \date Created: 2005-04-05
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

#ifndef CPAF_GTK2_GTK_H
#define CPAF_GTK2_GTK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GtkWidget GtkWidget;

//! \note X11 specific
extern int XFree( void* );

#ifdef __cplusplus
}
#endif

#endif // CPAF_GTK2_GTK_H
