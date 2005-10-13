/*!
    \file include/cpaf/cocoa/gui/eventloop.h
    \brief Declares the EventLoop object
    \date Created: 2005-10-13
*/

#ifndef CPAF_COCOA_GUI_EVENTLOOP_H
#define CPAF_COCOA_GUI_EVENTLOOP_H

#include <cpaf/api/gui/EventLoop.h>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class EventLoop : public cpaf::api::gui::EventLoop
{
public:
    EventLoop();

    void run();
    void run_once();
    void run_until();
    void stop();
    bool is_running() const;

private:
    bool m_running, m_stop;
};

        } // gui
    } // cocoa
} // cpaf
#endif // CPAF_COCOA_GUI_EVENTLOOP_H
