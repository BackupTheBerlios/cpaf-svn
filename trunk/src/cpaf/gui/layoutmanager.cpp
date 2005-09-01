/*!
    \file src\cpaf\layoutmanager.cpp
    \brief Layout Manager implementation
    \date Created: 2005-08-24
*/

#include <cpaf/gui/layoutmanager.h>
#include <cpaf/gui/widget.h>

using namespace cpaf::gui;

LayoutManager::~LayoutManager() { }

void LayoutManager::set_widget_pos(Widget *widget, const cpaf::Point &pos)
{
    widget->set_position(pos);
}

void LayoutManager::set_widget_size(Widget *widget, const cpaf::Size &size)
{
    widget->set_size(size);
}
