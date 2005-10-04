/*!
    \file src/cpaf/gui/window.cpp
    \brief Implementation of cpaf::gui::Window
    \date Created: 2005-04-05
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
    m_impl = Widget::get_impl<api_type>();
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
    params.set_wrapper(this);
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

void Window::set_content_panel(Panel *p)
{
    m_impl->set_content_panel(p->get_impl());
}

Panel *Window::get_content_panel() const
{
    return m_impl->get_content_panel();
}
