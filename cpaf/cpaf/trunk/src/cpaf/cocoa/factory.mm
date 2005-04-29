/**
 * \file src/cpaf/cocoa/factory.mm
 * \brief Implementation of Cocoa factory
 * \date 2005-04-29
 */

#include <cpaf/private/factory.h>
#include <cpaf/cocoa/factory.h>
#include <cpaf/cocoa/gui/window.h>
#include <cpaf/cocoa/gui/button.h>

cpaf::api::gui::Widget *cpaf::cocoa::gui::factory::create_window(int id, cpaf::api::gui::Widget *parent)
{
    return new cpaf::cocoa::gui::Window( dynamic_cast<cpaf::api::gui::Window*>(parent) );
}

cpaf::api::gui::Widget *cpaf::cocoa::gui::factory::create_button(int id, cpaf::api::gui::Widget *parent)
{
    return new cpaf::cocoa::gui::Button( parent );
}

void cpaf::gui::factory::register_factories()
{
    // register widget factories
    cpaf::gui::factory::register_widget_factory<cpaf::api::gui::Window>(cpaf::cocoa::gui::factory::create_window);
    cpaf::gui::factory::register_widget_factory<cpaf::api::gui::Button>(cpaf::cocoa::gui::factory::create_button);
}
