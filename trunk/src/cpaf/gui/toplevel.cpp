/*
Wrapper for api::gui::TopLevel
*/

#include <cpaf/gui/toplevel.h>
#include <cpaf/api/gui/toplevel.h>
#include <cpaf/private/factory.h>

using namespace cpaf::api::gui;

cpaf::gui::TopLevel::TopLevel()
    : m_impl(NULL)
{ }

void cpaf::gui::TopLevel::set_impl(cpaf::api::gui::TopLevel *impl)
{
    m_impl = impl;
    cpaf::gui::Widget::set_impl(impl);

    // because TopLevel widget derivatives are allowed to be on the stack,
    // their implementation objects must not be allowed to delete them,
    // so remove ourselves from the wrapper -> implementation map
    //cpaf::gui::factory::remove_implementation_wrapper(m_impl);
}

cpaf::gui::TopLevel::~TopLevel()
{
    // delete out implementation unconditionally
    //delete m_impl;
}

cpaf::gui::TopLevel::operator cpaf::api::gui::TopLevel *()
{
    return m_impl;
}

void cpaf::gui::TopLevel::show(bool show, bool focus)
{
    m_impl->show(show, focus);
}

void cpaf::gui::TopLevel::set_title(const std::string &t)
{
    m_impl->set_title(t);
}

std::string cpaf::gui::TopLevel::get_title()
{
    return m_impl->get_title();
}

void cpaf::gui::TopLevel::set_client_size(const cpaf::Size &s)
{
    m_impl->set_client_size(s);
}

cpaf::Size cpaf::gui::TopLevel::get_client_size()
{
    return m_impl->get_client_size();
}

cpaf::Point cpaf::gui::TopLevel::get_client_position()
{
    return m_impl->get_client_position();
}
