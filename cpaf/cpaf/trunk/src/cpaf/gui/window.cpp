/*
gui window wrapper
*/

#include <cpaf/gui/window.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/private/factory.h>

cpaf::gui::Window::Window(cpaf::api::gui::Window *p)
    : TopLevel(p),
    m_impl(p)
{ }

cpaf::gui::Window::operator cpaf::api::gui::Window *()
{
    return m_impl;
}

cpaf::gui::Window::Factory::Factory()
    : cpaf::gui::factory::Window<Factory>(new cpaf::gui::factory::WindowData)
{ }

cpaf::gui::Window *cpaf::gui::Window::Factory::create() const
{
    return new cpaf::gui::Window(cpaf::gui::factory::create_window(*m_data));
}
