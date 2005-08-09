/*!
    \file src/cpaf/gui/entrybox.cpp
    \brief Implementation of cpaf::gui::EntryBox
    \date Created: 2005-07-14
*/

#include <cpaf/gui/entrybox.h>
#include <cpaf/api/gui/entrybox.h>
#include <cpaf/private/factory.h>

using namespace cpaf::gui;

EntryBox::EntryBox()
    : TextWidget(factory::create_widget_implementation<api_type>())
{
    m_impl = Widget::get_impl<api_type>();
}

EntryBox::EntryBox(cpaf::api::gui::EntryBox *impl)
    : TextWidget(impl),
    m_impl(impl)
{ }

void EntryBox::create(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

EntryBox::api_type *EntryBox::get_impl() const
{
    return m_impl;
}

void EntryBox::set_password_mode(bool mode)
{
    m_impl->set_password_mode(mode);
}

bool EntryBox::get_password_mode() const
{
    return m_impl->get_password_mode();
}
