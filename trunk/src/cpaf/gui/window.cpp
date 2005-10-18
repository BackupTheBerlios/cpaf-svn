/*!
    \file src/cpaf/gui/window.cpp
    \brief Implementation of cpaf::gui::Window
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

#include <cpaf/gui/window.h>
#include <cpaf/gui/panel.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/private/factory.h>
#include <cpaf/exception.h>

using namespace cpaf::gui;

Window::Window()
    : TopLevel(factory::create_widget_implementation<api_type>())
{
    m_impl = Object::get_impl<api_type>();
}

Window::Window(api_type *impl)
    : TopLevel(impl),
    m_impl(impl)
{ }

boost::shared_ptr<Window> Window::create(const Initializer &initializer)
{
    Window *wrapper = new Window;
    return wrapper->initialize(initializer);
}

boost::shared_ptr<Window> Window::initialize(const Initializer &initializer)
{
    // create a shared pointer for this wapper
    boost::shared_ptr<Window> ptr(this);

    // create the native widget
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(ptr);
    m_impl->create(params);

    // store the widget id / shared_ptr pair to retain the wrapper
    associate_widget_id(get_id(), ptr);

    // lastly, return the wrapper
    return ptr;
}

Window::api_type *Window::get_impl() const
{
    return m_impl;
}

void Window::set_min_content_size(const cpaf::Size &size)
{
    m_impl->set_min_content_size(size);
}

void Window::set_max_content_size(const cpaf::Size &size)
{
    m_impl->set_max_content_size(size);
}

cpaf::Size Window::get_min_content_size() const
{
    return m_impl->get_min_content_size();
}

cpaf::Size Window::get_max_content_size() const
{
    return m_impl->get_max_content_size();
}

void Window::set_content_panel(boost::shared_ptr<cpaf::gui::Panel> p)
{
    m_impl->set_content_panel(p->get_impl());
}

boost::shared_ptr<cpaf::gui::Panel> Window::get_content_panel() const
{
    return m_impl->get_content_panel();
}
