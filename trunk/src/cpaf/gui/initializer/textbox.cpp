/*!
    \file src/cpaf/gui/initializer/textbox.cpp
    \brief cpaf::gui::TextBox initializer implementation
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

#include <cpaf/gui/initializer/textbox.h>

using namespace cpaf::gui::initializer;

cpaf::gui::TextBoxInitializer::TextBoxInitializer()
    : cpaf::gui::initializer::TextBox<TextBoxInitializer>(new data_type)
{ }

cpaf::gui::TextBoxInitializer::data_type cpaf::gui::TextBoxInitializer::get_data() const
{
    return *m_data;
}
