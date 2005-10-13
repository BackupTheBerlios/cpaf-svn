/*!
    \file include/cpaf/gtk2/gui/eventloop.h
    \brief Declares the EventLoop object
    \date Created: 2005-10-13
*/

#ifndef CPAF_GTK2_GUI_EVENTLOOP_H
#define CPAF_GTK2_GUI_EVENTLOOP_H

#include <cpaf/api/gui/EventLoop.h>

namespace cpaf {
    namespace gtk2 {
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
    } // gtk2
} // cpaf
#endif // CPAF_GTK2_GUI_EVENTLOOP_H
