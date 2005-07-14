/*!
    \file src/cpaf/gui/entrybox.cpp
    \brief Implementation of cpaf::gui::EntryBox
    \date Created: 2005-07-14
*/

#include <cpaf/gui/entrybox.h>
#include <cpaf/api/gui/entrybox.h>
#include <cpaf/private/factory.h>

cpaf::gui::EntryBox::EntryBox()
    : TextWidget(cpaf::gui::factory::create_widget_implementation<api_type>())
{
    m_impl = get_impl<api_type>();
}

cpaf::gui::EntryBox::EntryBox(cpaf::api::gui::EntryBox *impl)
    : TextWidget(impl),
    m_impl(impl)
{ }

void cpaf::gui::EntryBox::create(Initializer::data_type params)
{
    params.m_wrapper = this;
    m_impl->create(params);
}

cpaf::gui::EntryBox::operator cpaf::api::gui::EntryBox *()
{
    return m_impl;
}
