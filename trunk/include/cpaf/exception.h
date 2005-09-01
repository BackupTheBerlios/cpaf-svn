/*!
    \file include/cpaf/exception.h
    \brief cpaf::Exception declaration.
    \date Created: 2005-04-24
*/

#ifndef CPAF_EXCEPTION_H
#define CPAF_EXCEPTION_H

#include <cpaf/dllimpexp.h>

#define CPAF_EXCEPTION_IN_RANGE(c) ( (c) <= cpaf::Exception::HIGHEST && (c) >= cpaf::Exception::LOWEST )

namespace cpaf {

/*!
    Base class for all exceptions thrown by cpaf
*/
class CPAF_EXCEPTION_API(CPAF_API) Exception
{
public:
    static const int LOWEST     = 1;
    static const int HIGHEST    = LOWEST + 2000;

    // only add to the bottom of this enum...
    enum error_codes {
        WIDGET_NO_PARENT = LOWEST, //!< An attempt was made to create a widget with no parent, but the widget requires one
        NATIVE_HANDLE, //!< An error was encountered creating the native widget
        GUI_INIT_FAILED, //!< An error was encountered initializing the GUI
        PANEL_NO_LAYOUT_MANAGER, //!< A panel was created without a layout manager
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
        \todo Once we figure out unicode, this function should be localized
    */
    virtual const char *what();

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
