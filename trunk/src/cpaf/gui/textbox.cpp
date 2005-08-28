/*!
    \file src/cpaf/gui/textbox.cpp
    \brief Implementation of cpaf::gui::TextBox
    \date Created: 2005-07-07
*/

#include <cpaf/gui/textbox.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/private/factory.h>

using namespace cpaf::gui;

TextBox::TextBox()
    : TextWidget(factory::create_widget_implementation<api_type>())
{
    m_impl = Widget::get_impl<api_type>();
}

TextBox::TextBox(api_type *impl)
    : TextWidget(impl),
    m_impl(impl)
{ }

TextBox *TextBox::create(const Initializer &initializer)
{
    TextBox *wrapper = new TextBox;
    wrapper->initialize(initializer);
    return wrapper;
}

void TextBox::initialize(const Initializer &initializer)
{
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(this);
    m_impl->create(params);
}

TextBox::api_type *TextBox::get_impl() const
{
    return m_impl;
}
