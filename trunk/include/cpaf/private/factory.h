/*!
    \file include/cpaf/private/factory.h
    \brief Private widget factory declarations
    \date Created: 2005-04-05
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CPAF_PRIVATE_FACTORY_H
#define CPAF_PRIVATE_FACTORY_H

#include <cpaf/dllimpexp.h>

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

        } // factory
    } // gui
} // cpaf

#endif // CPAF_PRIVATE_FACTORY_H
