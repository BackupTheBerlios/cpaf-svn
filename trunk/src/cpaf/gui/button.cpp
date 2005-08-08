/*!
    \file src/cpaf/gui/button.cpp
    \brief Implementation of cpaf::gui::Button
    \date Created: 2005-04-05
*/

#include <cpaf/gui/button.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/private/factory.h>

cpaf::gui::Button::Button()
    : Widget(cpaf::gui::factory::create_widget_implementation<api_type>())
{
    m_impl = cpaf::gui::Widget::get_impl<api_type>();
}

cpaf::gui::Button::Button(cpaf::api::gui::Button *impl)
    : Widget(impl),
    m_impl(impl)
{ }

void cpaf::gui::Button::create(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

cpaf::gui::Button::api_type *cpaf::gui::Button::get_impl() const
{
    return m_impl;
}

void cpaf::gui::Button::set_label(const std::string &label)
{
    m_impl->set_label(label);
}

std::string cpaf::gui::Button::get_label() const
{
    return m_impl->get_label();
}
