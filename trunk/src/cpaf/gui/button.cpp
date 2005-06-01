/*!
    \file src/cpaf/gui/button.cpp
    \brief Implementation of cpaf::gui::Button
    \date Created: 2005-04-05
*/

#include <cpaf/gui/button.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/private/factory.h>

cpaf::gui::Button::Button()
    : m_impl(NULL)
{ }

void cpaf::gui::Button::set_impl(cpaf::api::gui::Button *impl)
{
    m_impl = impl;
    cpaf::gui::Widget::set_impl(impl);
}

cpaf::gui::Button::operator cpaf::api::gui::Button *()
{
    return m_impl;
}

void cpaf::gui::Button::set_label(const std::string &label)
{
    m_impl->set_label(label);
}

std::string cpaf::gui::Button::get_label()
{
    return m_impl->get_label();
}

cpaf::gui::Button::Factory::Factory()
    : cpaf::gui::factory::Button<Factory>(new cpaf::gui::factory::ButtonData)
{ }

cpaf::gui::Button *cpaf::gui::Button::Factory::create(cpaf::gui::Button *w) const
{
    cpaf::gui::factory::button_functor_ptr button = cpaf::gui::factory::create_button();
    w->set_impl(button->create());
    button->initialize(*m_data);
    return w;
}
