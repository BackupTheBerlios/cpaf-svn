/*!
    \file src/cpaf/gtk2/panel.cpp
    \brief Implementation of cpaf::gtk2::gui::Panel
    \date Created: 2005-08-08
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

#include <cpaf/gtk2/gui/panel.h>
#include <cpaf/exception.h>

#include <gtk/gtk.h>
#include <cpaf/gtk2/gui/cpaffixed.h>

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
:   m_last_width(0),
    m_last_height(0)
{ }

Panel::~Panel()
{

}

void
Panel::create (const cpaf::gui::initializer::PanelData &params)
{
    m_layout_manager = params.get_layout_manager();
    if (!m_layout_manager)
        throw cpaf::Exception (cpaf::Exception::PANEL_NO_LAYOUT_MANAGER, __LINE__, __FILE__);

    Widget::create (params, cpaf_fixed_new());

    g_signal_connect_after (m_widget, "size-allocate",
                            G_CALLBACK (cpaf_fixed_size_allocate),
                            this);

    // panels are shown at the point when they are associated with a parent
}
