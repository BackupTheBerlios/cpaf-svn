/*!
    \file include/cpaf/win32/exception.h
    \brief cpaf::win32::Exception declaration
    \date Created: 2005-04-24
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

    const char *get_message();

    /*!
        \return The win32 error code
    */
    int get_win32_error();
};

    } // win32
} // cpaf

#endif
