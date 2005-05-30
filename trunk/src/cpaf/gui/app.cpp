/*
Implementation for cpaf::gui::App
*/

#include <cpaf/gui/app.h>
#include <cpaf/private/factory.h>

cpaf::gui::App::App()
{
    // implementation specific gui initialization
    gui_init();
}

inline cpaf::event::Manager &cpaf::gui::App::get_events_manager()
{
    return m_events_manager;
}
