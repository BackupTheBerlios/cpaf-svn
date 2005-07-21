/*!    \file src/cpaf/gui/passwordbox.cpp    \brief Implementation of cpaf::gui::PasswordBox    \date Created: */#include <cpaf/gui/passwordbox.h>#include <cpaf/api/gui/passwordbox.h>#include <cpaf/private/factory.h>cpaf::gui::PasswordBox::PasswordBox()    : TextWidget(cpaf::gui::factory::create_widget_implementation<api_type>()){    m_impl = get_impl<api_type>();}cpaf::gui::PasswordBox::PasswordBox(api_type *impl)    : TextWidget(impl),    m_impl(impl){ }void cpaf::gui::PasswordBox::create(Initializer::data_type params){    params.m_wrapper = this;    m_impl->create(params);}cpaf::gui::PasswordBox::operator api_type *(){    return m_impl;}