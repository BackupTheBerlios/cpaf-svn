/*
Factory function implementations
*/

#include <cpaf/private/factory.h>

// include this because a full declaration of api::gui::Widget is required
// to call the proper destructors by delete_widget_implementation
#include <cpaf/api/gui/widget.h>

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

static cpaf::gui::factory::WidgetImplementationWrapperMap widget_impl_map;

// adds a wrappper implementation pair to the map
void cpaf::gui::factory::add_implementation_wrapper(cpaf::api::gui::Widget *impl, cpaf::gui::Widget* wrapper)
{
    widget_impl_map[impl] = wrapper;
}

void cpaf::gui::factory::remove_implementation_wrapper(cpaf::api::gui::Widget *impl)
{
    WidgetImplementationWrapperMap::iterator i = widget_impl_map.find(impl);

    if( i != widget_impl_map.end() )
        widget_impl_map.erase(i);
    //! \todo I should throw here
}

// called by gui::Foo destructors to delete their implementations only if the impl pointer is
// in the map
void cpaf::gui::factory::delete_widget_implementation(cpaf::api::gui::Widget *impl)
{
    WidgetImplementationWrapperMap::iterator i = widget_impl_map.find(impl);

    // if we found it...
    if( i != widget_impl_map.end() )
    {
        // remove it
        widget_impl_map.erase(i);
        
        // and delete the implementation
        delete impl;
    }
}

// called by implementation destructors to delete their gui wrappers only if the implementation
// pointer is in the map
void cpaf::gui::factory::delete_implementation_wrapper(cpaf::api::gui::Widget *impl)
{
    WidgetImplementationWrapperMap::iterator i = widget_impl_map.find(impl);

    // if we found it...
    if( i != widget_impl_map.end() )
    {
        // store the thing to delete later
        cpaf::gui::Widget *wrapper = i->second;

        // remove it
        widget_impl_map.erase(i);
        
        // and delete the wrapper
        delete wrapper;
    }
}
