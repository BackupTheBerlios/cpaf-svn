/*!
    \file src/cpaf/gui/panel.cpp
    \brief Implementation of cpaf::gui::Panel
    \date Created: 
*/

#include <cpaf/gui/panel.h>
#include <cpaf/api/gui/panel.h>
#include <cpaf/private/factory.h>

using namespace cpaf::gui;

Panel::Panel()
    : Widget(factory::create_widget_implementation<api_type>())
{
    m_impl = Widget::get_impl<api_type>();
}

Panel::Panel(api_type *impl)
    : Widget(impl),
    m_impl(impl)
{ }

void Panel::create(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

Panel::api_type *Panel::get_impl() const
{
    return m_impl;
}
