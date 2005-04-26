/*
Factory functions
*/

#ifndef CPAF_PRIVATE_FACTORY_H
#define CPAF_PRIVATE_FACTORY_H

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>
#include <cpaf/dllimpexp.h>
#include <map>

namespace cpaf {
    namespace gui {
        namespace factory {

// widget factory function pointer
typedef cpaf::api::gui::Widget *(*WidgetFactoryPtr)(int id, cpaf::api::gui::Widget *parent);

// widget factory registry map typedef
typedef std::map<int, cpaf::gui::factory::WidgetFactoryPtr> WidgetFactoryMap;

// these two functions wrap retrieving and inserting into the widget factory map
WidgetFactoryPtr get_factory(int key);
void add_factory(int key, WidgetFactoryPtr fact);


/*!
    \internal
    \return A unique widget identifier. Called by create_foo functions and passed to the
        implementation create_foo functions to be passed to implementation class ctors
 */
int get_widget_id();

template <typename T> T *create_widget(cpaf::api::gui::Widget *parent)
{
    WidgetFactoryPtr ptr = get_factory(T::factory_key);
    return dynamic_cast<T*>(ptr(get_widget_id(), parent));
}

template <typename T> void register_widget_factory(WidgetFactoryPtr ptr)
{
    add_factory(T::factory_key, ptr);
}

// declared by an implementation
// will be called so that implementations can use register_widget_factory
// to register their widget factory function pointers
void register_factories();

/*
CPAF OBJECT DESCTRUCTION OVERVIEW

  gui::Foo wrappers are no longer solely responsible for deleting their implementations.

  It is now possible for an implementation to delete its wrapper, or for a wrapper to delete its implementation.
  During one deletion chain, both events will occur.

  When a gui wrapper is created, the gui wrapper registers itself as wrapping a given implementation with
  add_implementation_wrapper. When its gui::Widget base is destructed, delete_widget_implementation is called
  to delete the implementation object only if it has not been deleted already (meaning its still in the map).
  delete_widget_implementation will remove the wrapper implementation pair from the map and then delete the
  implementation. This invokes the implementations destructor, which will call delete_implementation_wrapper.
  Because the wrapper implementation pair is no longer in the list, the function does nothing.

  The use of these two functions allows deletion of either end (wrapper, or implementation) to delete BOTH
  the wrapping object and the implementation object.

  BECAUSE OF THIS CHANGE ALL OBJECTS MUST BE CREATED WITH THE NEW OPERATOR.
*/

// map from implementations to their wrappers
typedef std::map<cpaf::api::gui::Widget *, cpaf::gui::Widget *> WidgetImplementationWrapperMap;

// adds a wrappper implementation pair to the map
void add_implementation_wrapper(cpaf::api::gui::Widget *impl, cpaf::gui::Widget* wrapper);

// removes a wrapper implementation pair from the map but does not delete the implementation or wrapper objects
// this is called by top level wrapper ctors to allow creation of them on the stack
void remove_implementation_wrapper(cpaf::api::gui::Widget *impl);

// called by gui::Foo destructors to delete their implementations only if the impl pointer is
// in the map. If the impl pointer is in the map, it will be removed, and then deleted.
void delete_widget_implementation(cpaf::api::gui::Widget *impl);

// called by implementation destructors to delete their gui wrappers only if the implementation
// pointer is in the map. If the impl pointer is in the map, it will be removed, and its wrapper deleted.
void delete_implementation_wrapper(cpaf::api::gui::Widget *impl);

        } // factory
    } // gui
} // cpaf

#endif // CPAF_PRIVATE_FACTORY_H
