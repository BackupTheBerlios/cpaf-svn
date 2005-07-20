/*!
    \file src/cpaf/win32/app.cpp
    \brief Implementation of the parts of cpaf::gui::App which are implementation specific,
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

    while( true )
    {
        // if no widgets exist, terminate the application
        if( cpaf::win32::gui::widget_map_empty() )
            ::PostQuitMessage(0);

        // use peekmessage to check for waiting messages
        if( !::PeekMessage(&msg, 0, 0, 0, PM_REMOVE) )
        {
            // no messages waiting, check the widget deletion stack
            if( cpaf::win32::gui::widget_deletion_stack_waiting() )
            {
                // delete the widget and check for more messages
                cpaf::win32::gui::widget_deletion_stack_pop();
                continue;
            }
            else
                // wait for a message
                //! \todo Throw if GetMessage returns -1
                if( ::GetMessage(&msg, 0, 0, 0) == -1 )
                    break;
        }

        // process the message
        if( msg.message == WM_QUIT )
            break;
        else
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }

    //! \todo return the exit code value instead of 0
    return 0;
}
