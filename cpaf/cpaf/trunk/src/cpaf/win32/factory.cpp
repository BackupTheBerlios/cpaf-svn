/*
win32 factory implementation
*/

#include <cpaf/private/factory.h>
#include <cpaf/win32/factory.h>
#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/gui/button.h>

#include <cpaf/gui/window.h>


#include <cpaf/exception.h>

cpaf::api::gui::Widget *cpaf::win32::gui::factory::create_window(int id, cpaf::api::gui::Widget *parent)
{
    return new cpaf::win32::gui::Window( id, dynamic_cast<cpaf::api::gui::Window*>(parent) );
}

cpaf::api::gui::Widget *cpaf::win32::gui::factory::create_button(int id, cpaf::api::gui::Widget *parent)
{
    return new cpaf::win32::gui::Button( id, parent );
}

void cpaf::gui::factory::register_factories()
{
    // register widget factories
    cpaf::gui::factory::register_widget_factory<cpaf::api::gui::Window>(cpaf::win32::gui::factory::create_window);
    cpaf::gui::factory::register_widget_factory<cpaf::api::gui::Button>(cpaf::win32::gui::factory::create_button);
}
