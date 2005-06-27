/*!
    \file include/cpaf/private/factory.h
    \brief Private widget factory declarations
    \date Created: 2005-04-05
*/

#ifndef CPAF_PRIVATE_FACTORY_H
#define CPAF_PRIVATE_FACTORY_H

#include <cpaf/dllimpexp.h>

//#include <cpaf/gui/api-prototypes.h>
//#include <cpaf/gui/widget.h>
//#include <cpaf/gui/button.h>
//#include <cpaf/gui/window.h>
//#include <map>

namespace cpaf {
    namespace gui {
        namespace factory {

/*!
    \brief Implementation widget factory function prototype

    This template is left undefined in this header. Implementations are responsible for
    implementing template specializations for all constructable types.
*/
template<typename Api> Api *create_widget_implementation();

/*
    \return An object identifier unique throughout the application
*/
int get_unique_object_id();

/*!
    \brief Helper macro for implementing widget factory functions.

    \param type Name of the api widget class that will be constructed. "Button"
    \param port Port implementing this factory. "win32"
*/
#define IMPLEMENT_WIDGET_FACTORY(type, port) \
namespace cpaf { \
    namespace gui { \
        namespace factory { \
            template<> cpaf::api::gui::type *create_widget_implementation<cpaf::api::gui::type>() \
            { return new cpaf::port::gui::type; } \
        } \
    } \
}

//These functions are currently unused, see "technotes/widget destruction.txt"
/*
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
*/
        } // factory
    } // gui
} // cpaf

#endif // CPAF_PRIVATE_FACTORY_H
