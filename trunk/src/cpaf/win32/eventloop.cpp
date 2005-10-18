/*!
    \file src/cpaf/win32/eventloop.cpp
    \brief Implements the EventLoop object for win32
    \date Created: 2005-10-13
*/

#include <cpaf/win32/gui/EventLoop.h>
#include <cpaf/win32/win.h>

// implement factory
cpaf::api::gui::EventLoop *cpaf::api::gui::EventLoop::create()
{
    return new cpaf::win32::gui::EventLoop;
}

using cpaf::win32::gui::EventLoop;

EventLoop::EventLoop()
: m_running(false),
m_stop(false)
{

}

void EventLoop::run()
{
    m_running = true;

    // the win32 message loop
    MSG msg;

    while( !m_stop )
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
        }
    }

    m_stop = false;

    //! \todo return the exit code value somehow
    return;
}

void EventLoop::run_once()
{

}

void EventLoop::run_until()
{

}

void EventLoop::stop()
{
    m_stop = true;
}

bool EventLoop::is_running() const
{
    return m_running;
}
