/*
win32 factory implementation
*/

#include <cpaf/private/factory.h>
#include <cpaf/win32/factory.h>
#include <cpaf/win32/gui/window.h>

cpaf::api::gui::Widget *cpaf::win32::gui::factory::create_window()
{
    return new cpaf::win32::gui::Window;
}

void cpaf::gui::factory::register_factories()
{
    // register window factory
    cpaf::gui::factory::register_widget_factory<cpaf::api::gui::Window>(cpaf::win32::gui::factory::create_window);
}
