/*!
    \file src/cpaf/gui/textwidget.cpp
    \brief Implementation of cpaf::gui::TextWidget
    \date Created: 2005-07-14
*/

#include <cpaf/gui/textwidget.h>
#include <cpaf/api/gui/textwidget.h>
#include <cpaf/private/factory.h>

cpaf::gui::TextWidget::TextWidget()
    : Widget(cpaf::gui::factory::create_widget_implementation<api_type>())
{
    m_impl = get_impl<api_type>();
}

cpaf::gui::TextWidget::TextWidget(cpaf::api::gui::TextWidget *impl)
    : Widget(impl),
    m_impl(impl)
{ }

cpaf::gui::TextWidget::operator cpaf::api::gui::TextWidget *()
{
    return m_impl;
}

void cpaf::gui::TextWidget::set_text(const std::string &s)
{
    m_impl->set_text(s);
}

std::string cpaf::gui::TextWidget::get_text()
{
    return m_impl->get_text();
}
