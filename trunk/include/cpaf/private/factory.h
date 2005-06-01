/*!
    \file include/cpaf/private/factory.h
    \brief Widget factory declarations
    \date Created: 2005-04-05
*/

#ifndef CPAF_PRIVATE_FACTORY_H
#define CPAF_PRIVATE_FACTORY_H

#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>
#include <cpaf/dllimpexp.h>

#include <cpaf/gui/button.h>
#include <cpaf/gui/window.h>

#include <map>
#include <memory>

namespace cpaf {
    namespace gui {
        class Widget;
        namespace factory {

template<typename Api, typename Data> class widget_functor
{
public:
    typedef Api api_type;
    typedef Data data_type;

    virtual api_type *create() = 0;
    virtual void initialize(const data_type &params) = 0;

    virtual ~widget_functor() { }
};

/*!
    \brief Helper macro for declaring widget factory functions.

    \param name Name of the api widget class that will be constructed. "Button"
    \param lname Name of the api widget class being constructed in lower case. "button"
*/
#define DECLARE_WIDGET_FACTORY(type, name)                                                          \
    typedef widget_functor<cpaf::api::gui::type, cpaf::gui::factory::type##Data> name##_functor;    \
    typedef std::auto_ptr<name##_functor> name##_functor_ptr;                                       \
    name##_functor_ptr create_##name();                                                             \

#define IMPLEMENT_WIDGET_FACTORY(type, name, port)                      \
namespace {                                                             \
class name##_functor_impl : public cpaf::gui::factory::name##_functor   \
{                                                                       \
private:                                                                \
    typedef cpaf::port::gui::type impl_type;                            \
    impl_type *m_i;                                                     \
public:                                                                 \
    api_type *create()                                                  \
    {                                                                   \
        m_i = new impl_type;                                            \
        return m_i;                                                     \
    }                                                                   \
    void initialize(const data_type &params)                            \
    {                                                                   \
        m_i->create(params);                                            \
    }                                                                   \
};                                                                      \
}                                                                       \
cpaf::gui::factory::name##_functor_ptr cpaf::gui::factory::create_##name() \
{ return name##_functor_ptr(new name##_functor_impl); }                 \


/*
    Widget factory function prototypes

    These factories are defined by an implementation and are called directly
    by initializer factory objects.
*/
DECLARE_WIDGET_FACTORY(Button, button)
DECLARE_WIDGET_FACTORY(Window, window)



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
