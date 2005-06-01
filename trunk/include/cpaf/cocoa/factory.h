/**
 * \file include/cpaf/cocoa/factory.h
 * \brief Cocoa factories
 * \date Created: 2005-04-29
 */

#ifndef CPAF_COCOA_FACTORY_H
#define CPAF_COCOA_FACTORY_H

#include <cpaf/gui/api-prototypes.h>

namespace cpaf {
    namespace cocoa {
        namespace gui {
            namespace factory {

cpaf::api::gui::Widget *create_window(int id, cpaf::api::gui::Widget *parent);
cpaf::api::gui::Widget *create_button(int id, cpaf::api::gui::Widget *parent);

            } // factory
        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_FACTORY_H
