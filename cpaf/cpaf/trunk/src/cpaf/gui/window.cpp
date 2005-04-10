/*
gui window wrapper
*/

#include <cpaf/gui/window.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/private/factory.h>

using namespace cpaf::api::gui;

cpaf::gui::Window::Window()
    : TopLevel( cpaf::gui::factory::create_widget<cpaf::api::gui::Window>() ),
    m_impl( dynamic_cast<cpaf::api::gui::Window*>(Widget::m_impl) )
{ }

//cpaf::gui::Window::Window(const WindowPtr &p)
cpaf::gui::Window::Window(cpaf::api::gui::Window *p)
    : TopLevel(p),
    m_impl(p)
{ }
