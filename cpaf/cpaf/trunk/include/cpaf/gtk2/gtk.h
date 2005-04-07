/**
 * \file include/cpaf/gtk2/gtk.h
 * \brief Common header for gtk2 implementation
 * \date 2005-04-05
 */

#ifndef _CPAF_GTK2_GTK_H_
#define _CPAF_GTK2_GTK_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GtkWidget GtkWidget;

//! \note X11 specific
extern int XFree( void* );

#ifdef __cplusplus
}
#endif

#endif // _CPAF_GTK2_GTK_H_
