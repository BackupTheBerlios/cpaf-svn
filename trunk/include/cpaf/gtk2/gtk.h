/**
 * \file include/cpaf/gtk2/gtk.h
 * \brief Common header for gtk2 implementation
 * \date 2005-04-05
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
