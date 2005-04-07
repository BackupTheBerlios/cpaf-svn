/*
Implementation for cpaf::gui::App
*/

#include <cpaf/gui/app.h>
#include <cpaf/private/factory.h>

cpaf::gui::App::App()
{
    // we are a gui app, and as such we need to registry the factory function pointers
    cpaf::gui::factory::register_factories();
}
