/*
Implementation for cpaf::gui::App
*/

#include <cpaf/gui/app.h>
#include <cpaf/private/factory.h>

cpaf::gui::App::App()
{
    // implementation specific gui initialization
    gui_init();

    // we are a gui app, and as such we need to register the factory function pointers
    cpaf::gui::factory::register_factories();
}
