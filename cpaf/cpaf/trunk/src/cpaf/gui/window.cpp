/*
gui window wrapper
*/

#include <cpaf/gui/window.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/private/factory.h>

using namespace cpaf::api::gui;

cpaf::gui::Window::Window()
    : TopLevel( WindowPtr(cpaf::gui::factory::create_widget<cpaf::api::gui::Window>()) ),
    m_impl( static_cast<cpaf::api::gui::Window*>(Widget::m_impl.get()) )
{ }

cpaf::gui::Window::Window(const WindowPtr &p)
    : TopLevel(p),
    m_impl(p.get())
{ }
