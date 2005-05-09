/*
cpaf::win32::Exception class
*/

#ifndef CPAF_WIN32_EXCEPTION_H
#define CPAF_WIN32_EXCEPTION_H

#include <cpaf/exception.h>

#define CPAF_WIN32_EXCEPTION_IN_RANGE(c) ( (c) <= cpaf::win32::EXCEPTION_HIGHST && (c) >= cpaf::win32::EXCEPTION_LOWEST )

namespace cpaf {
    namespace win32 {

const int EXCEPTION_LOWEST(cpaf::EXCEPTION_HIGHEST + 1000);
const int EXCEPTION_HIGHST(EXCEPTION_LOWEST + 1000);

class CPAF_EXCEPTION_API(CPAF_API) Exception : public cpaf::Exception
{
public:
    enum error_codes {
        WIDGET_INIT = EXCEPTION_LOWEST, //!< failed internal initialization for win32
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
