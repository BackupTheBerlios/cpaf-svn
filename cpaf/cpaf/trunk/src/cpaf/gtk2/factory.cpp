/**
 * \file src/cpaf/gtk2/factory.cpp
 * \brief Implementation of gtk2 factory
 * \date 2005-04-05
 */

#include <cpaf/private/factory.h>
#include <cpaf/gtk2/factory.h>
#include <cpaf/gtk2/gui/window.h>
#include <cpaf/gtk2/gui/button.h>

cpaf::api::gui::Widget *cpaf::gtk2::gui::factory::create_window(int id, cpaf::api::gui::Widget *parent)
{
    return new cpaf::gtk2::gui::Window( dynamic_cast<cpaf::api::gui::Window*>(parent) );
}

cpaf::api::gui::Widget *cpaf::gtk2::gui::factory::create_button(int id, cpaf::api::gui::Widget *parent)
{
    return new cpaf::gtk2::gui::Button( parent );
}

void cpaf::gui::factory::register_factories()
{
    // register widget factories
    cpaf::gui::factory::register_widget_factory<cpaf::api::gui::Window>(cpaf::gtk2::gui::factory::create_window);
    cpaf::gui::factory::register_widget_factory<cpaf::api::gui::Button>(cpaf::gtk2::gui::factory::create_button);

}
