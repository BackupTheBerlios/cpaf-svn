/*!
    \file src/cpaf/gtk2/cpaffixed.cpp
    \brief Custom container derived from GtkFixed
    \date Created: 2005-10-04
 */

#include <cpaf/gtk2/gui/cpaffixed.h>

/* Prototypes */
static void cpaf_fixed_init             (CpafFixed      *fixed);
static void cpaf_fixed_class_init       (CpafFixedClass *klass);
static void cpaf_fixed_size_allocate    (GtkWidget      *widget,
                                         GtkAllocation  *allocation);

GType
cpaf_fixed_get_type (void)
{
    static GType fixed_type = 0;

    if (!fixed_type)
    {
        static const GTypeInfo fixed_info =
        {
            sizeof (CpafFixedClass),
            NULL, /* base_init */
            NULL, /* base_finalize */
            (GClassInitFunc) cpaf_fixed_class_init,
            NULL, /* class_finalize */
            NULL, /* class_data */
            sizeof (CpafFixed),
            0,    /* n_preallocs */
            (GInstanceInitFunc) cpaf_fixed_init,
        };

        fixed_type = g_type_register_static (GTK_TYPE_FIXED, "CpafFixed",
                                             &fixed_info, 0);
    }

    return fixed_type;
}

static void
cpaf_fixed_class_init (CpafFixedClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = (GtkWidgetClass*) klass;

    /* Provide our own size_allocate */
    widget_class->size_allocate = cpaf_fixed_size_allocate;
}

static void
cpaf_fixed_init (CpafFixed *fixed)
{
    /* Nothing to do yet */
}

GtkWidget *
cpaf_fixed_new (void)
{
    return g_object_new (CPAF_TYPE_FIXED, NULL);
}

static void
cpaf_fixed_size_allocate (GtkWidget     *widget,
                          GtkAllocation *allocation)
{
    GtkFixed *fixed;
    GtkFixedChild *child;
    GtkAllocation child_allocation;
    GtkRequisition child_requisition;
    GList *children;
    guint16 border_width;

    fixed = GTK_FIXED (widget);

    widget->allocation = *allocation;

    if (!GTK_WIDGET_NO_WINDOW (widget))
    {
        if (GTK_WIDGET_REALIZED (widget))
            gdk_window_move_resize (widget->window,
                                    allocation->x,
                                    allocation->y,
                                    allocation->width,
                                    allocation->height);
    }

    border_width = GTK_CONTAINER (fixed)->border_width;

    children = fixed->children;
    while (children)
    {
        child = children->data;
        children = children->next;

        if (GTK_WIDGET_VISIBLE (child->widget))
        {
            gtk_widget_get_child_requisition (child->widget, &child_requisition);
            child_allocation.x = child->x + border_width;
            child_allocation.y = child->y + border_width;
            child_allocation.height = child->widget->allocation.height;
            child_allocation.width = child->widget->allocation.width;

            /* Ensure that the allocation is not smaller than the requisition (CHECKME:) */
            if (child_allocation.height < child_requisition.height)
                child_allocation.height = child_requisition.height;

            if (child_allocation.width < child_requisition.width)
                child_allocation.width = child_requisition.width;

            if (GTK_WIDGET_NO_WINDOW (widget))
            {
                child_allocation.x += widget->allocation.x;
                child_allocation.y += widget->allocation.y;
            }

            gtk_widget_size_allocate (child->widget, &child_allocation);
        }
    }

}
