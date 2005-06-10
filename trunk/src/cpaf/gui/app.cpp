/*!
    \file src/cpaf/gui/app.cpp
    \brief Implementation of cpaf::gui::App
    \date Created: 2005-04-07
*/

#include <cpaf/gui/app.h>
#include <cpaf/private/factory.h>

cpaf::gui::App::App()
{
    // implementation specific gui initialization
    gui_init();
}

cpaf::event::Manager &cpaf::gui::App::get_event_manager()
{
    return m_event_manager;
}
