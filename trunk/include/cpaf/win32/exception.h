/*!
    \file include/cpaf/win32/exception.h
    \brief cpaf::win32::Exception declaration
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

#ifndef CPAF_WIN32_EXCEPTION_H
#define CPAF_WIN32_EXCEPTION_H

#include <cpaf/exception.h>

#define CPAF_WIN32_EXCEPTION_IN_RANGE(c) ( (c) <= cpaf::win32::Exception::HIGHEST && (c) >= cpaf::win32::Exception::LOWEST )

namespace cpaf {
    namespace win32 {

class CPAF_EXCEPTION_API(CPAF_API) Exception : public cpaf::Exception
{
public:
    static const int LOWEST     = cpaf::Exception::HIGHEST + 1000;
    static const int HIGHEST    = LOWEST + 1000;

    enum error_codes {
        WIDGET_INIT = LOWEST, //!< failed internal initialization for win32
        HOOK, //!< error calling SetWindowsHookEx
        UNHOOK, //!< error calling UnhookWindowsHookEx
    };

private:
    int m_win32_error; //!< win32 error code

public:
    Exception(int error, int win32, int line, const char *file);

    const char *what();

    /*!
        \return The win32 error code
    */
    int get_win32_error();
};

    } // win32
} // cpaf

#endif
