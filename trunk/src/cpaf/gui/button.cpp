/*
Wrapper for api::gui::button
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
    w->set_impl(cpaf::gui::factory::create_button(*m_data));
    return w;
}
