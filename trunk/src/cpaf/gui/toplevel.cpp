/*!
    \file src/cpaf/gui/toplevel.cpp
    \brief Implementation of cpaf::gui::TopLevel
    \date Created: 2005-04-05
*/

#include <cpaf/gui/toplevel.h>
#include <cpaf/api/gui/toplevel.h>
#include <cpaf/private/factory.h>
#include <cpaf/gui/app.h>

cpaf::gui::TopLevel::TopLevel(api_type *impl)
    : Widget(impl),
    m_impl(impl)
{
    // add ourselves to the TopLevel widget list
    cpaf::gui::App::add_top_level(this);
}

cpaf::gui::TopLevel::~TopLevel()
{
    // remove ourselves from the TopLevel widget list
    cpaf::gui::App::remove_top_level(this);
}

cpaf::gui::TopLevel::operator api_type *() const
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

std::string cpaf::gui::TopLevel::get_title() const
{
    return m_impl->get_title();
}

void cpaf::gui::TopLevel::set_client_size(const cpaf::Size &s)
{
    m_impl->set_client_size(s);
}

cpaf::Size cpaf::gui::TopLevel::get_client_size() const
{
    return m_impl->get_client_size();
}

cpaf::Point cpaf::gui::TopLevel::get_client_position() const
{
    return m_impl->get_client_position();
}
