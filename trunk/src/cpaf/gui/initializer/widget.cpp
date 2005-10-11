/*!
    \file src/cpaf/gui/initializer/widget.cpp
    \brief cpaf::gui::Widget initializer implementation
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

#include <cpaf/gui/initializer/widget.h>

using namespace cpaf::gui::initializer;

WidgetData::WidgetData()
    : m_show(false),
    m_activate(false),
    m_enable(true)
{ }

void WidgetData::set_wrapper(boost::shared_ptr<cpaf::gui::Widget> w)
{
    m_wrapper = w;
}

boost::shared_ptr<cpaf::gui::Widget> WidgetData::get_wrapper() const
{
    return m_wrapper;
}

void WidgetData::set_parent(boost::shared_ptr<cpaf::gui::Panel> p)
{
    m_parent = p;
}

boost::shared_ptr<cpaf::gui::Panel> WidgetData::get_parent() const
{
    return m_parent;
}

void WidgetData::set_show(bool b)
{
    m_show = b;
}

bool WidgetData::get_show() const
{
    return m_show;
}

void WidgetData::set_activate(bool b)
{
    m_activate = b;
}

bool WidgetData::get_activate() const
{
    return m_activate;
}

void WidgetData::set_enable(bool b)
{
    m_enable = b;
}

bool WidgetData::get_enable() const
{
    return m_enable;
}
