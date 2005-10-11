/*!
    \file src/cpaf/gui/panel.cpp
    \brief Implementation of cpaf::gui::Panel
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

#include <cpaf/gui/panel.h>
#include <cpaf/api/gui/panel.h>
#include <cpaf/private/factory.h>

using namespace cpaf::gui;

Panel::Panel()
    : Widget(factory::create_widget_implementation<api_type>())
{
    m_impl = Widget::get_impl<api_type>();
}

Panel::Panel(api_type *impl)
    : Widget(impl),
    m_impl(impl)
{ }

boost::shared_ptr<Panel> Panel::create(const Initializer &initializer)
{
    Panel *wrapper = new Panel;
    return wrapper->initialize(initializer);
}

boost::shared_ptr<Panel> Panel::initialize(const Initializer &initializer)
{
    // create a shared pointer for this wapper
    boost::shared_ptr<Panel> ptr(this);

    // create the native widget
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(ptr);
    m_impl->create(params);

    // store the widget id / shared_ptr pair to retain the wrapper
    associate_widget_id(get_id(), ptr);

    // lastly, return the wrapper
    return ptr;
}

Panel::api_type *Panel::get_impl() const
{
    return m_impl;
}
