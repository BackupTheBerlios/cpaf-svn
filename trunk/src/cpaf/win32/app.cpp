/*!
    \file src/cpaf/win32/app.cpp
    \brief Implementation of the parts of cpaf::gui::App which are implementation specific.
    \date Created: 2005-04-07
*/

#include <cpaf/win32/win.h>
#include <cpaf/gui/app.h>
#include <cpaf/win32/exception.h>

#include <commctrl.h>

using namespace cpaf::win32::gui;

void cpaf::gui::App::gui_init()
{
    // initialize common controls
    ::InitCommonControls();
}

int cpaf::gui::App::run()
{
    // the win32 message loop
    MSG msg;

    while( true )
    {
        // if no widgets exist, terminate the application
        if( !has_widgets() )
            ::PostQuitMessage(0);

        // use peekmessage to check for waiting messages
        if( !::PeekMessage(&msg, 0, 0, 0, PM_REMOVE) )
        {
            // no messages waiting, check the widget deletion stack
            if( widget_deletion_stack_waiting() )
            {
                // delete the widget and check for more messages
                widget_deletion_stack_pop();
                continue;
            }
            else
                // nothing to delete, wait for a message
                // we could use WaitMessage here
                //! \todo Do something if GetMessage returns -1
                if( ::GetMessage(&msg, 0, 0, 0) == -1 )
                    break;
        }

        // process the message
        if( msg.message == WM_QUIT )
            break;
        else
        {
            // allow tab traversal in panels
            // a widgets parent is either a panel, or a window (the root panel)
            // so we can always use GetParent here
            if( !::IsDialogMessage(::GetParent(msg.hwnd), &msg) )
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
            //else
                //DBG_MSG("IsDialogMessage processed");
        }
    }

    //! \todo return the exit code value instead of 0
    return 0;
}

void cpaf::gui::App::_quit()
{
    ::PostQuitMessage(0);
}
