/*
cpaf::Exception definition. The base class for any exception thrown by cpaf
*/

#ifndef CPAF_EXCEPTION_H
#define CPAF_EXCEPTION_H

#include <cpaf/dllimpexp.h>

#define CPAF_EXCEPTION_LOWEST   1
#define CPAF_EXCEPTION_HIGHEST  CPAF_EXCEPTION_LOWEST + 2000
#define CPAF_EXCEPTION_IN_RANGE(c) ( (c) <= CPAF_EXCEPTION_LOWEST && (c) >= CPAF_EXCEPTION_LOWEST )

namespace cpaf {
    
/*!
    Base class for all exceptions thrown by cpaf
*/
class CPAF_EXCEPTION_API(CPAF_API) Exception
{
public:

    // only add to the bottom of this enum...
    enum error_codes {
        WIDGET_NO_PARENT = CPAF_EXCEPTION_LOWEST, //!< An attempt was made to create a widget with no parent, but the widget requires one
        NATIVE_HANDLE, //!< An error was encountered creating the native widget
    };

protected:
    int m_code; //!< A value used to indicate an error code.
    int m_line; //!< line that generated the exception
    const char *m_file; //!< the name of the file that generated the exception

public:
    Exception(int code, int line, const char *file);
    virtual ~Exception();

    /*!
        \return An english ansi description of the error
        //! \todo Once we figure out unicode, this function should be localized
    */
    virtual const char *get_message();

    /*!
        \return An ansi description of the file throwing the exception
    */
    const char *get_file();

    /*!
        \return The line of code throwing the exception
    */
    int get_line();

    /*!
        \return The error code
    */
    int get_code();
};

} // cpaf

#endif
