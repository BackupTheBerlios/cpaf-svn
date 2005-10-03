/*!
    \file src/cpaf/gtk2/panel.cpp
    \brief Implementation of cpaf::gtk2::gui::Panel
    \date Created: 
*/

#include <cpaf/gtk2/gui/panel.h>
#include <cpaf/exception.h>

#include <gtk/gtk.h>

using namespace cpaf::gtk2::gui;

extern "C" {
static void
cpaf_fixed_size_allocate(GtkWidget *gtkwidget,
                         GtkAllocation *alloc,
                         Panel * widget)
{
    //! \todo Revise the logic. Possibly writing our own gtk+ container for this
    if (alloc->width != widget->m_last_width || alloc->height != widget->m_last_height)
    {
        widget->m_layout_manager->do_layout(cpaf::Size(alloc->width, alloc->height));
        widget->m_last_width = alloc->width;
        widget->m_last_height = alloc->height;
    }
}
} // extern "C"

Panel::Panel()
:   m_layout_manager(NULL),
    m_last_width(0),
    m_last_height(0)
{ }

Panel::~Panel()
{
    // delete the layout manager
    delete m_layout_manager;
}

void
Panel::create (const cpaf::gui::initializer::PanelData &params)
{
    m_layout_manager = params.get_layout_manager();
    if (!m_layout_manager)
        throw cpaf::Exception (cpaf::Exception::PANEL_NO_LAYOUT_MANAGER, __LINE__, __FILE__);

    Widget::create (params, gtk_fixed_new());

    g_signal_connect_after (m_widget, "size-allocate",
                            G_CALLBACK (cpaf_fixed_size_allocate),
                            this);

    // panels are shown at the point when they are associated with a parent
}
