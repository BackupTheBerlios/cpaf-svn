/*!
    \file src/cpaf/gui/initializer/object.cpp
    \brief cpaf::gui::Object initializer implementation
    \date Created: 2005-07-27
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

#include <cpaf/gui/initializer/object.h>

using namespace cpaf::gui::initializer;

ObjectData::ObjectData()
    : m_default_size(true),
    m_default_pos(true)
{ }

ObjectData::~ObjectData() { }

void ObjectData::set_min_size(const cpaf::Size &s)
{
    m_min_size = s;
}

cpaf::Size ObjectData::get_min_size() const
{
    return m_min_size;
}

void ObjectData::set_max_size(const cpaf::Size &s)
{
    m_max_size = s;
}

cpaf::Size ObjectData::get_max_size() const
{
    return m_max_size;
}

void ObjectData::set_natural_size(const cpaf::Size &s)
{
    m_natural_size = s;
}

cpaf::Size ObjectData::get_natural_size() const
{
    return m_natural_size;
}
