/*
Factory functions
*/

#include <cpaf/gui/api-prototypes.h>
#include <cpaf/dllimpexp.h>
#include <map>

namespace cpaf {
    namespace gui {
        namespace factory {

// widget factory function pointer
typedef cpaf::api::gui::Widget *(*WidgetFactoryPtr)();

// widget factory registry map typedef
typedef std::map<int, cpaf::gui::factory::WidgetFactoryPtr> WidgetFactoryMap;

// these two functions wrap retrieving and inserting into the widget factory map
WidgetFactoryPtr get_factory(int key);
void add_factory(int key, WidgetFactoryPtr fact);

//extern WidgetFactoryMap widget_factory_map;

template <typename T> T *create_widget()
{
    return static_cast<T*>(get_factory(T::factory_key)());
    //return static_cast<T*>(widget_factory_map[T::factory_key]());
}

template <typename T> void register_widget_factory(WidgetFactoryPtr ptr)
{
    add_factory(T::factory_key, ptr);
    //widget_factory_map[T::factory_key] = ptr;
}

// declared by an implementation
// will be called so that implementations can use register_widget_factory
// to register their widget factory function pointers
// this is CPAF_EXP for now because i need to call it manually in my demo
void CPAF_EXP register_factories();

        }
    }
}
