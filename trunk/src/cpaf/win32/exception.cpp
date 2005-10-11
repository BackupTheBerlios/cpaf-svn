/*!
    \file src/cpaf/win32/exception.cpp
    \brief Implementation of cpaf::win32::Exception
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

    Copyright (C) 2005 Robin McNeill
    http://www.snakesoft.net
    snakechomp (at) snakesoft [dot] net
*/

#include <cpaf/win32/exception.h>

cpaf::win32::Exception::Exception(int error, int win32, int line, const char *file)
    : cpaf::Exception(error, line, file),
    m_win32_error(win32)
{ }

const char *cpaf::win32::Exception::what()
{
    if( CPAF_WIN32_EXCEPTION_IN_RANGE(m_code) )
    {
        switch(m_code)
        {
        case WIDGET_INIT:
            return "The widget implementation class failed to initialize internally";
        case HOOK:
            return "There was an error hooking WM_CREATE";
        case UNHOOK:
            return "There was an error unhooking the WM_CREATE hook";
        default:
            return "Unknown error encountered";
        };
    }
    else
        return cpaf::Exception::what();
}

int cpaf::win32::Exception::get_win32_error()
{
    return m_win32_error;
}
