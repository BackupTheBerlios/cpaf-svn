/*!
    \file src/cpaf/gui/textbox.cpp
    \brief Implementation of cpaf::gui::TextBox
    \date Created: 2005-07-07
*/

#include <cpaf/gui/textbox.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/private/factory.h>

cpaf::gui::TextBox::TextBox()
    : TextWidget(cpaf::gui::factory::create_widget_implementation<api_type>())
{
    m_impl = get_impl<api_type>();
}

cpaf::gui::TextBox::TextBox(cpaf::api::gui::TextBox *impl)
    : TextWidget(impl),
    m_impl(impl)
{ }

void cpaf::gui::TextBox::create(Initializer::data_type params)
{
    params.m_wrapper = this;
    m_impl->create(params);
}

cpaf::gui::TextBox::operator cpaf::api::gui::TextBox *()
{
    return m_impl;
}
