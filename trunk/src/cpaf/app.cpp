/*!
    \file src/cpaf/app.cpp
    \brief Implementation of cpaf::App
    \date Created: 2005-04-07
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

#include <cpaf/app.h>

const cpaf::App::cmd_line &cpaf::App::get_cmd_line()
{
    return m_cmd;
}

void cpaf::App::set_cmd_line(const cmd_line &cmd)
{
    m_cmd = cmd;
}
