/*
gui window wrapper
*/

#include <cpaf/gui/window.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/private/factory.h>

cpaf::gui::Window::Window()
    : m_impl(NULL)
{ }

void cpaf::gui::Window::set_impl(cpaf::api::gui::Object *impl)
{
    m_impl = dynamic_cast<cpaf::api::gui::Window*>(impl);
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
    cpaf::gui::factory::create_window(w, *m_data);
    return w;
}
