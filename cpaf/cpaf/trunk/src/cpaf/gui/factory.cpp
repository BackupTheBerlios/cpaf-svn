/*
Factory function implementations
*/

#include <cpaf/private/factory.h>

/*
#ifdef CPAF_WIN32
#include <cpaf/win32/factory.h>
#endif
#ifdef CPAF_GTK
#include <cpaf/gtk/factory.h>
#endif

// a WindowPtr will be conveniently constructed for us by return;
cpaf::api::gui::WindowPtr cpaf::gui::factory::create_window()
{
#ifdef CPAF_WIN32 // win32 build
    return cpaf::win32::gui::factory::create_window();
#endif
#ifdef CPAF_GTK
    return cpaf::gtk::gui::factory::create_window();
#endif
}
*/

// the widget factory function pointer registry
//cpaf::gui::factory::WidgetFactoryMap cpaf::gui::factory::widget_factory_map;
static cpaf::gui::factory::WidgetFactoryMap widget_factory_map;

cpaf::gui::factory::WidgetFactoryPtr cpaf::gui::factory::get_factory(int key)
{
    return widget_factory_map[key];
}

void cpaf::gui::factory::add_factory(int key, WidgetFactoryPtr fact)
{
    widget_factory_map[key] = fact;
}
