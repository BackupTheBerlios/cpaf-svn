/*!
    \file src/cpaf/gui/widget.cpp
    \brief Implementation of cpaf::gui::Widget
    \date Created: 2005-04-05
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

#include <cpaf/gui/widget.h>
#include <cpaf/api/gui/widget.h>

// for delete_widget_implementation
#include <cpaf/private/factory.h>

using cpaf::object_id;
using namespace cpaf::gui;

Widget::Widget(api_type *impl)
    : Object(impl),
    m_id(factory::get_unique_object_id()),
    m_impl(impl)
{
    // add the wrapper / implementation pair to the map
    //factory::add_implementation_wrapper(m_impl, this);
}

Widget::~Widget()
{
    // delete the implementation safely
    //factory::delete_widget_implementation(m_impl);
}

void Widget::destroy()
{
    m_impl->destroy();
}

Widget::api_type *Widget::get_impl() const
{
    return m_impl;
}

void *Widget::get_handle() const
{
    return m_impl->get_handle();
}

void Widget::enable(bool e)
{
    m_impl->enable(e);
}

void Widget::disable()
{
    m_impl->enable(false);
}

void Widget::show(bool show, bool activate)
{
    m_impl->show(show, activate);
}

void Widget::hide()
{
    m_impl->show(false, false);
}

bool Widget::is_enabled() const
{
    return m_impl->is_enabled();
}

bool Widget::is_shown() const
{
    return m_impl->is_shown();
}

object_id Widget::get_id() const
{
    return m_id;
}

boost::shared_ptr<Panel> Widget::get_parent() const
{
    return m_impl->get_parent();
}

boost::shared_ptr<Window> Widget::get_parent_window() const
{
    return m_impl->get_parent_window();
}

/*
    Widget Id Map implementation
*/
typedef std::map<cpaf::object_id, boost::shared_ptr<Widget> > WidgetMap;

namespace {
    WidgetMap widget_map;
}

void cpaf::gui::associate_widget_id(cpaf::object_id id, boost::shared_ptr<Widget> ptr)
{
    widget_map.insert(std::make_pair(id, ptr));
}

void cpaf::gui::disassociate_widget_id(cpaf::object_id id)
{
    widget_map.erase(id);
}

boost::shared_ptr<Widget> cpaf::gui::get_widget_from_id(cpaf::object_id id)
{
    WidgetMap::iterator it= widget_map.find(id);

    //! \todo Decide what to do if the id isn't in the map
    if( it != widget_map.end() )
        return it->second;
}
