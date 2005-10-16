/*!
    \file src/cpaf/gui/object.cpp
    \brief Implementation of cpaf::gui::Object
    \date Created: 2004-04-05
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

#include <cpaf/gui/object.h>
#include <cpaf/api/gui/object.h>

using namespace cpaf::gui;

Object::Object(api_type *impl)
    : m_impl(impl)
{ }

Object::~Object()
{

}

Object::api_type *Object::get_impl() const
{
    return m_impl.get();
}
void Object::set_size(const cpaf::Size &s)
{
    m_impl->set_size(s);
}

void Object::set_min_size(const cpaf::Size &s)
{
    m_impl->set_min_size(s);
}

void Object::set_max_size(const cpaf::Size &s)
{
    m_impl->set_max_size(s);
}

void Object::set_position(const cpaf::Point &p)
{
    m_impl->set_position(p);
}

void Object::set_rect(const cpaf::Rect &r)
{
    m_impl->set_rect(r);
}

cpaf::Size Object::get_size() const
{
    return m_impl->get_size();
}

cpaf::Size Object::get_min_size() const
{
    return m_impl->get_min_size();
}

cpaf::Size Object::get_max_size() const
{
    return m_impl->get_max_size();
}

void Object::set_natural_size(const cpaf::Size &s)
{
    m_impl->set_natural_size(s);
}

cpaf::Size Object::get_natural_size() const
{
    return m_impl->get_natural_size();
}

cpaf::Point Object::get_position() const
{
    return m_impl->get_position();
}

cpaf::Rect Object::get_rect() const
{
    return m_impl->get_rect();
}
