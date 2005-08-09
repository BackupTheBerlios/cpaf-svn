/*!
    \file src/cpaf/gui/button.cpp
    \brief Implementation of cpaf::gui::Button
    \date Created: 2005-04-05
*/

#include <cpaf/gui/button.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/private/factory.h>

using namespace cpaf::gui;

Button::Button()
    : Widget(factory::create_widget_implementation<api_type>())
{
    m_impl = Widget::get_impl<api_type>();
}

Button::Button(cpaf::api::gui::Button *impl)
    : Widget(impl),
    m_impl(impl)
{ }

void Button::create(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

Button::api_type *Button::get_impl() const
{
    return m_impl;
}

void Button::set_label(const std::string &label)
{
    m_impl->set_label(label);
}

std::string Button::get_label() const
{
    return m_impl->get_label();
}
