/*
This file implements cpaf::gui::App::run() for win32
*/

#include <cpaf/win32/win.h>
#include <cpaf/gui/app.h>

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
