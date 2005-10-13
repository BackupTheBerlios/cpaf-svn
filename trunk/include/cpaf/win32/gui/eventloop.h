/*!
    \file include/cpaf/win32/gui/eventloop.h
    \brief Declares the EventLoop object
    \date Created: 2005-10-13
*/

#ifndef CPAF_WIN32_GUI_EVENTLOOP_H
#define CPAF_WIN32_GUI_EVENTLOOP_H

#include <cpaf/api/gui/EventLoop.h>

namespace cpaf {
    namespace win32 {
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
    } // win32
} // cpaf
#endif // CPAF_WIN32_GUI_EVENTLOOP_H
