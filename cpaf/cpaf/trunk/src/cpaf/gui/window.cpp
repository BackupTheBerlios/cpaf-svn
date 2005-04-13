/*
gui window wrapper
*/

#include <cpaf/gui/window.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/private/factory.h>

using namespace cpaf::api::gui;

cpaf::gui::Window::Window(cpaf::gui::Window *parent)
// for some reason, the next line wont compile unless I cast 0 myself
: TopLevel( cpaf::gui::factory::create_window( (parent) ? *parent : (cpaf::api::gui::Window*)0 ) ),
    m_impl( dynamic_cast<cpaf::api::gui::Window*>(Widget::m_impl) )
{ }

//cpaf::gui::Window::Window(const WindowPtr &p)
cpaf::gui::Window::Window(cpaf::api::gui::Window *p)
    : TopLevel(p),
    m_impl(p)
{ }

cpaf::gui::Window::operator cpaf::api::gui::Window *()
{
    return m_impl;
}
