/*!
    \file src\cpaf\layoutmanager.cpp
    \brief Layout Manager implementation
    \date Created: 2005-08-24
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

#include <cpaf/gui/layoutmanager.h>
#include <cpaf/gui/widget.h>

using namespace cpaf::gui;

LayoutManager::~LayoutManager() { }

void LayoutManager::set_widget_pos(boost::shared_ptr<Widget> widget, const cpaf::Point &pos)
{
    widget->set_position(pos);
}

void LayoutManager::set_widget_size(boost::shared_ptr<Widget> widget, const cpaf::Size &size)
{
    widget->set_size(size);
}

void LayoutManager::set_widget_rect(boost::shared_ptr<Widget> widget, const cpaf::Rect &rect)
{
    widget->set_rect(rect);
}
