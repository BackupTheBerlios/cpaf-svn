/**
 * \file src/cpaf/gtk2/factory.cpp
 * \brief Implementation of gtk2 factory
 * \author Mart Raudsepp
 * \date 2005-04-05
 */

#include <cpaf/private/factory.h>
#include <cpaf/gtk2/factory.h>
#include <cpaf/gtk2/gui/window.h>

cpaf::api::gui::Widget *cpaf::gtk2::gui::factory::create_window()
{
    return new cpaf::gtk2::gui::Window;
}

void cpaf::gui::factory::register_factories()
{
    // register window factory
    cpaf::gui::factory::register_widget_factory<cpaf::api::gui::Window>(cpaf::gtk2::gui::factory::create_window);
}
