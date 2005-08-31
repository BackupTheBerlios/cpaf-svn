/*!
    \file src/cpaf/gui/toplevel.cpp
    \brief Implementation of cpaf::gui::TopLevel
    \date Created: 2005-04-05
*/

#include <cpaf/gui/toplevel.h>
#include <cpaf/api/gui/toplevel.h>
#include <cpaf/private/factory.h>
#include <cpaf/gui/app.h>

using namespace cpaf::gui;

TopLevel::TopLevel(api_type *impl)
    : Widget(impl),
    m_impl(impl)
{
    // add ourselves to the TopLevel widget list
    App::add_top_level(this);
}

TopLevel::~TopLevel()
{
    // remove ourselves from the TopLevel widget list
    App::remove_top_level(this);
}

TopLevel::api_type *TopLevel::get_impl() const
{
    return m_impl;
}

void TopLevel::set_size(const cpaf::Size &s)
{
    m_impl->set_size(s);
}

void TopLevel::set_position(const cpaf::Point &p)
{
    m_impl->set_position(p);
}

void TopLevel::show(bool show, bool focus)
{
    m_impl->show(show, focus);
}

void TopLevel::set_title(const std::string &t)
{
    m_impl->set_title(t);
}

std::string TopLevel::get_title() const
{
    return m_impl->get_title();
}

void TopLevel::set_client_size(const cpaf::Size &s)
{
    m_impl->set_client_size(s);
}

cpaf::Size TopLevel::get_client_size() const
{
    return m_impl->get_client_size();
}

cpaf::Point TopLevel::get_client_position() const
{
    return m_impl->get_client_position();
}
