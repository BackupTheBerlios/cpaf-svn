/*!
    \file src/cpaf/win32/exception.cpp
    \brief Implementation of cpaf::win32::Exception
    \date Created: 2005-04-24
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
