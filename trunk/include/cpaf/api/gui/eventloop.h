/*!
    \file include/cpaf/api/gui/eventloop.h
    \brief Declares the EventLoop object API
    \date Created: 2005-10-13
*/

#ifndef CPAF_API_GUI_EVENTLOOP_H
#define CPAF_API_GUI_EVENTLOOP_H

namespace cpaf {
    namespace api {
        namespace gui {

class EventLoop
{
public:
    virtual void run() = 0;
    virtual void run_once() = 0;
    virtual void run_until() = 0;
    virtual void stop() = 0;
    virtual bool is_running() const = 0;

    // I'm lazy, so this will be the factory function implemented by a port
    // to return their derivative of this interface
    static EventLoop *create();
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_EVENTLOOP_H
