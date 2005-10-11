/*!
    \file src/cpaf/gui/initializer/panel.cpp
    \brief cpaf::gui::Panel initializer implementation
    \date Created: 
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

#include <cpaf/gui/initializer/panel.h>

using namespace cpaf::gui::initializer;

PanelData::PanelData() { }

void PanelData::set_layout_manager(boost::shared_ptr<cpaf::gui::LayoutManager> manager)
{
    m_layout_manager = manager;
}

boost::shared_ptr<cpaf::gui::LayoutManager> PanelData::get_layout_manager() const
{
    return m_layout_manager;
}

cpaf::gui::PanelInitializer::PanelInitializer()
    : cpaf::gui::initializer::Panel<PanelInitializer>(new data_type)
{ }

cpaf::gui::PanelInitializer::data_type cpaf::gui::PanelInitializer::get_data() const
{
    return *m_data;
}
