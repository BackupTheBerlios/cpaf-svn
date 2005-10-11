/*!
    \file src/cpaf/gui/initializer/entrybox.cpp
    \brief cpaf::gui::EntryBox initializer implementation
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

#include <cpaf/gui/initializer/entrybox.h>

using namespace cpaf::gui::initializer;

EntryBoxData::EntryBoxData()
    : m_password_mode(false)
{ }

void EntryBoxData::set_password_mode(bool b)
{
    m_password_mode = b;
}

bool EntryBoxData::get_password_mode() const
{
    return m_password_mode;
}

cpaf::gui::EntryBoxInitializer::EntryBoxInitializer()
    : cpaf::gui::initializer::EntryBox<EntryBoxInitializer>(new data_type)
{ }

cpaf::gui::EntryBoxInitializer::data_type cpaf::gui::EntryBoxInitializer::get_data() const
{
    return *m_data;
}
