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
    m_impl = cpaf::gui::Widget::get_impl<api_type>();
}

cpaf::gui::EntryBox::EntryBox(cpaf::api::gui::EntryBox *impl)
    : TextWidget(impl),
    m_impl(impl)
{ }

void cpaf::gui::EntryBox::create(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

cpaf::gui::EntryBox::api_type *cpaf::gui::EntryBox::get_impl() const
{
    return m_impl;
}

void cpaf::gui::EntryBox::set_password_mode(bool mode)
{
    m_impl->set_password_mode(mode);
}

bool cpaf::gui::EntryBox::get_password_mode() const
{
    return m_impl->get_password_mode();
}
