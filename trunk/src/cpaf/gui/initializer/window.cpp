/*!
    \file src/cpaf/gui/initializer/window.cpp
    \brief cpaf::gui::Window initializer implementation
    \date Created: 2005-07-27
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

#include <cpaf/gui/initializer/window.h>

using namespace cpaf::gui::initializer;

WindowData::WindowData()
    : m_default_position(false)
{
    // windows should be activated when shown by default
    WidgetData::m_activate = true;
}

void WindowData::set_title(const std::string &str)
{
    m_title = str;
}

std::string WindowData::get_title() const
{
    return m_title;
}

void WindowData::set_client_size(const cpaf::Size &s)
{
    m_client_size = s;
}

cpaf::Size WindowData::get_client_size() const
{
    return m_client_size;
}

void WindowData::set_position(const cpaf::Point &p)
{
    m_default_position = false;
    m_position = p;
}

cpaf::Point WindowData::get_position() const
{
    return m_position;
}

bool WindowData::default_position() const
{
    return m_default_position;
}

void WindowData::set_content_panel(boost::shared_ptr<cpaf::gui::Panel> p)
{
    m_content_panel = p;
}

boost::shared_ptr<cpaf::gui::Panel> WindowData::get_content_panel() const
{
    return m_content_panel;
}

cpaf::gui::WindowInitializer::WindowInitializer()
    : cpaf::gui::initializer::Window<WindowInitializer>(new data_type)
{ }

cpaf::gui::WindowInitializer::data_type cpaf::gui::WindowInitializer::get_data() const
{
    return *m_data;
}
