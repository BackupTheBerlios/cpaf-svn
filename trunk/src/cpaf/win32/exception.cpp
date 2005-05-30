/*
win32::Exception implementation
*/

#include <cpaf/win32/exception.h>

cpaf::win32::Exception::Exception(int error, int win32, int line, const char *file)
    : cpaf::Exception(error, line, file),
    m_win32_error(win32)
{ }

const char *cpaf::win32::Exception::get_message()
{
    if( CPAF_WIN32_EXCEPTION_IN_RANGE(m_code) )
    {
        switch(m_code)
        {
        case WIDGET_INIT:
            return "The widget implementation class failed to initialize internally";
        default:
            return "Unknown error encountered";
        };
    }
    else
        return cpaf::Exception::get_message();
}

int cpaf::win32::Exception::get_win32_error()
{
    return m_win32_error;
}