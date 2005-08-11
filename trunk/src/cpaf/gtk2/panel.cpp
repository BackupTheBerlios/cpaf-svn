/*!
    \file src/cpaf/gtk2/panel.cpp
    \brief Implementation of cpaf::gtk2::gui::Panel
    \date Created: 
*/

#include <cpaf/gtk2/gui/panel.h>

#include <gtk/gtk.h>

using namespace cpaf::gtk2::gui;

void Panel::create(const cpaf::gui::initializer::PanelData &params)
{
    Widget::create (params, gtk_fixed_new());

    // panels are shown at the point when they are associated with a parent
}
