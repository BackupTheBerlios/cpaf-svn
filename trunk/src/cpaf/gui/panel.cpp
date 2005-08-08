/*!
    \file src/cpaf/gui/panel.cpp
    \brief Implementation of cpaf::gui::Panel
    \date Created: 
*/

#include <cpaf/gui/panel.h>
#include <cpaf/api/gui/panel.h>
#include <cpaf/private/factory.h>

cpaf::gui::Panel::Panel()
    : Widget(cpaf::gui::factory::create_widget_implementation<api_type>())
{
    m_impl = get_impl<api_type>();
}

cpaf::gui::Panel::Panel(api_type *impl)
    : Widget(impl),
    m_impl(impl)
{ }

void cpaf::gui::Panel::create(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

cpaf::gui::Panel::operator api_type *() const
{
    return m_impl;
}
