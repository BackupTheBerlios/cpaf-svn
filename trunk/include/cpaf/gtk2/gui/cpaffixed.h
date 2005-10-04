/**
 * \file include/cpaf/gtk2/gui/cpaffixed.h
 * \brief Custom container derived from GtkFixed
 * \date Created: 2005-10-04
 */

/* THIS IS A C FILE, DO NOT USE C++ SYNTAX (comments in particular) */

#ifndef __CPAF_FIXED_H__
#define __CPAF_FIXED_H__

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

#endif /* __CPAF_FIXED_H__ */
