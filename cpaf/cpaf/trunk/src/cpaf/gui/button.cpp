/*
Wrapper for api::gui::button
*/

#include <cpaf/gui/button.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/private/factory.h>

cpaf::gui::Button::Button(cpaf::gui::Widget *parent)
//! \todo this crashes if parent is null
: Widget( cpaf::gui::factory::create_button(*parent) ),
    m_impl( dynamic_cast<cpaf::api::gui::Button*>(Widget::m_impl) )
{ }

cpaf::gui::Button::Button(cpaf::api::gui::Button *p)
    : Widget(p),
    m_impl(p)
{ }

cpaf::gui::Button::operator cpaf::api::gui::Button *()
{
    return m_impl;
}

void cpaf::gui::Button::set_label(const cpaf::String &label)
{
    m_impl->set_label(label);
}

cpaf::String cpaf::gui::Button::get_label()
{
    return m_impl->get_label();
}
