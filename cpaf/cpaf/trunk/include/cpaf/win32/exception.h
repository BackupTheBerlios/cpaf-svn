/*
cpaf::win32::Exception class
*/

#ifndef CPAF_WIN32_EXCEPTION_H
#define CPAF_WIN32_EXCEPTION_H

#include <cpaf/exception.h>

#define CPAF_WIN32_EXCEPTION_LOWEST CPAF_EXCEPTION_HIGHEST + 1000
#define CPAF_WIN32_EXCEPTION_HIGHST CPAF_WIN32_EXCEPTION_LOWEST + 1000
#define CPAF_WIN32_EXCEPTION_IN_RANGE(c) ( (c) <= CPAF_WIN32_EXCEPTION_HIGHST && (c) >= CPAF_WIN32_EXCEPTION_LOWEST )

namespace cpaf {
    namespace win32 {

class CPAF_EXCEPTION_API(CPAF_API) Exception : public cpaf::Exception
{
public:
    enum error_codes {
        WIDGET_INIT = CPAF_WIN32_EXCEPTION_LOWEST, //!< failed internal initialization for win32
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
