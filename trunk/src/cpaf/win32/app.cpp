/*!
    \file src/cpaf/win32/app.cpp
    \brief Implementation file for the parts of cpaf::gui::App which are implemenation specific,
    those being gui_init() and run().
    \date Created: 2005-04-07
*/

#include <cpaf/win32/win.h>
#include <cpaf/gui/app.h>
#include <cpaf/exception.h>

void cpaf::gui::App::gui_init()
{
    // dont need to do anything for win32 yet...
}

int cpaf::gui::App::run()
{
    // the win32 message loop
    MSG msg;

    // getmessage could return -1....who cares
    while( GetMessage( &msg, NULL, 0, 0 ) )
    {
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }

    //! \todo return the exit code value instead of 0
    return 0;
}
