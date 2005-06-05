/*!
    \file src/cpaf/gui/window.cpp
    \brief Implementation of cpaf::gui::Window
    \date Created: 2005-04-05
*/

#include <cpaf/gui/window.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/private/factory.h>

cpaf::gui::Window::Window()
    : m_impl(NULL)
{ }

void cpaf::gui::Window::set_impl(cpaf::api::gui::Window *impl)
{
    m_impl = impl;
    cpaf::gui::TopLevel::set_impl(impl);
}

cpaf::gui::Window::operator cpaf::api::gui::Window *()
{
    return m_impl;
}

cpaf::gui::Window::Factory::Factory()
    : cpaf::gui::factory::Window<Factory>(new cpaf::gui::factory::WindowData)
{ }

cpaf::gui::Window *cpaf::gui::Window::Factory::create(cpaf::gui::Window *w) const
{
    try
    {
        cpaf::gui::factory::window_functor_ptr window = cpaf::gui::factory::create_window();
        w->set_impl(window->create());
        window->initialize(*m_data);
        return w;
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
