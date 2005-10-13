/*!
    \file include/cpaf/gui/eventloop.h
    \brief Declares the EventLoop object
    \date Created: 2005-10-13
*/

#ifndef CPAF_GUI_EVENTLOOP_H
#define CPAF_GUI_EVENTLOOP_H

#include <cpaf/dllimpexp.h>
#include <boost/scoped_ptr.hpp>

namespace cpaf {
    namespace api { namespace gui { class EventLoop; } }
    namespace gui {

/*!
    This class represents the event loop for the application. Its implementation
    is dependant on the system, but its purpose is to control the events system
    from one central location. This object allows you to start and stop the event
    loop, giving you fine control over how your application processes events from
    both the system and cpaf's own event system if you need it.
*/
class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    /*!
        Runs the event loop until it is stopped.
    */
    void run();

    /*!
        Stops the running loop.
    */
    void stop();

    /*!
        Runs a single iteration of the event loop and returns.
    */
    void run_once();

    /*!
        Runs the event loop until no events remain to be processed and then returns
    */
    void run_until();

    /*!
        \return Whether or not the event loop is running.
    */
    bool is_running() const;

private:
    boost::scoped_ptr<cpaf::api::gui::EventLoop> m_impl;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_EVENTLOOP_H
