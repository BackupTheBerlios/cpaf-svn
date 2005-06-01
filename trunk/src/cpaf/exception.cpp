/*!
    \file src/cpaf/exception.cpp
    \brief Implementation of cpaf::Exception
    \date Created: 2005-04-24
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

const char *cpaf::Exception::get_message()
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

        default:
            return "An unknown error was encountered";
        }
    }
    else
        return "An error occured which does not have an error message";
}
