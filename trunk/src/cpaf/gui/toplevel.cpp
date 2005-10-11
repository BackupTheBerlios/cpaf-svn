/*!
    \file src/cpaf/gui/toplevel.cpp
    \brief Implementation of cpaf::gui::TopLevel
    \date Created: 2005-04-05
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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

void TopLevel::set_rect(const cpaf::Rect &r)
{
    m_impl->set_rect(r);
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
