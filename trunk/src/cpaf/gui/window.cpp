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

cpaf::gui::Window::Window()
    : TopLevel(cpaf::gui::factory::create_widget_implementation<api_type>())
{
    m_impl = cpaf::gui::Widget::get_impl<api_type>();
}

cpaf::gui::Window::Window(api_type *impl)
    : TopLevel(impl),
    m_impl(impl)
{ }

void cpaf::gui::Window::create(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

cpaf::gui::Window::api_type *cpaf::gui::Window::get_impl() const
{
    return m_impl;
}

void cpaf::gui::Window::set_content_panel(cpaf::gui::Panel *p)
{
    m_impl->set_content_panel(p->get_impl());
}

cpaf::gui::Panel *cpaf::gui::Window::get_content_panel() const
{
    return m_impl->get_content_panel();
}
