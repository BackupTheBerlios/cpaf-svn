/*!
    \file src/cpaf/gui/textbox.cpp
    \brief Implementation of cpaf::gui::TextBox
    \date Created: 2005-07-07
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <cpaf/gui/textbox.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/private/factory.h>

using namespace cpaf::gui;

TextBox::TextBox()
    : TextWidget(factory::create_widget_implementation<api_type>())
{
    m_impl = Object::get_impl<api_type>();
}

TextBox::TextBox(api_type *impl)
    : TextWidget(impl),
    m_impl(impl)
{ }

boost::shared_ptr<TextBox> TextBox::create(const Initializer &initializer)
{
    TextBox *wrapper = new TextBox;
    return wrapper->initialize(initializer);
}

boost::shared_ptr<TextBox> TextBox::initialize(const Initializer &initializer)
{
    // create a shared pointer for this wapper
    boost::shared_ptr<TextBox> ptr(this);

    // create the native widget
    Initializer::data_type params = initializer.get_data();
    params.set_wrapper(ptr);
    m_impl->create(params);

    // store the widget id / shared_ptr pair to retain the wrapper
    associate_widget_id(get_id(), ptr);

    // lastly, return the wrapper
    return ptr;
}

TextBox::api_type *TextBox::get_impl() const
{
    return m_impl;
}
