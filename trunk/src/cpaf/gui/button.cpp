/*!
    \file src/cpaf/gui/button.cpp
    \brief Implementation of cpaf::gui::Button
    \date Created: 2005-04-05
*/

#include <cpaf/gui/button.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/private/factory.h>
#include <cpaf/exception.h>

cpaf::gui::Button::Button()
    : m_impl(NULL)
{ }

void cpaf::gui::Button::set_impl(cpaf::api::gui::Button *impl)
{
    m_impl = impl;
    cpaf::gui::Widget::set_impl(impl);
}

cpaf::gui::Button::operator cpaf::api::gui::Button *()
{
    return m_impl;
}

void cpaf::gui::Button::set_label(const std::string &label)
{
    m_impl->set_label(label);
}

std::string cpaf::gui::Button::get_label()
{
    return m_impl->get_label();
}

cpaf::gui::Button::Factory::Factory()
    : cpaf::gui::factory::Button<Factory>(new cpaf::gui::factory::ButtonData)
{ }

cpaf::gui::Button *cpaf::gui::Button::Factory::create(cpaf::gui::Button *wrapper) const
{
    //! \todo Do something to avoid duplicating this code in every factory::create function
    try
    {
        cpaf::gui::factory::button_functor_ptr creator = cpaf::gui::factory::create_button();
        wrapper->set_impl(creator->create());
        creator->initialize(*m_data);
        return wrapper;
    }
    catch(cpaf::Exception &e)
    {
        // delete the gui wrapper which will delete its implementation
        // because something went wrong
        delete wrapper;

        // rethrow so other exception handlers can know that something happened
        throw;
    }
}
