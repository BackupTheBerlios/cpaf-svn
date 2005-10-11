/*!
    \file src/cpaf/exception.cpp
    \brief Implementation of cpaf::Exception
    \date Created: 2005-04-24
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

#include <cpaf/exception.h>

cpaf::Exception::Exception(int code, int line, const char *file)
    : m_code(code),
    m_line(line),
    m_file(file)
{ }

cpaf::Exception::~Exception() { }

const char *cpaf::Exception::get_file()
{
    return m_file;
}

int cpaf::Exception::get_line()
{
    return m_line;
}

int cpaf::Exception::get_code()
{
    return m_code;
}

const char *cpaf::Exception::what()
{
    if( CPAF_EXCEPTION_IN_RANGE(m_code) )
    {
        switch(m_code)
        {
        case WIDGET_NO_PARENT:
            return "An attempt was made to create a widget with no parent";
        case NATIVE_HANDLE:
            return "An error was encountered creating the native widget";
        case GUI_INIT_FAILED:
            return "An error was encountered initializing the GUI";
        case PANEL_NO_LAYOUT_MANAGER:
            return "A panel was created without a layout manager";

        default:
            return "An unknown error was encountered";
        }
    }
    else
        return "An error occured which does not have an error message";
}
