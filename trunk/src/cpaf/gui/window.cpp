/*!
    \file src/cpaf/gui/window.cpp
    \brief Implementation of cpaf::gui::Window
    \date Created: 2005-04-05
*/

#include <cpaf/gui/window.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/private/factory.h>
#include <cpaf/exception.h>

cpaf::gui::Window::Window(cpaf::api::gui::Window *impl)
    : TopLevel(impl),
    m_impl(impl)
{ }

void cpaf::gui::Window::create(const Initializer::data_type &params)
{
    m_impl->create(params);
}

cpaf::gui::Window::operator cpaf::api::gui::Window *()
{
    return m_impl;
}
