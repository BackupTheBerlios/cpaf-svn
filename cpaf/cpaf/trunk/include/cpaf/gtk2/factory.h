/**
 * \file include/cpaf/gtk2/factory.h
 * \brief gtk2 factories
 * \date 2005-04-05
 */

#ifndef _CPAF_GTK2_FACTORY_H_
#define _CPAF_GTK2_FACTORY_H_

#include <cpaf/gui/api-prototypes.h>

namespace cpaf {
   namespace gtk2 {
        namespace gui {
            namespace factory {

cpaf::api::gui::Widget *create_window();

            } // factory
        } // gui
   } // gtk2
} // cpaf

#endif // _CPAF_GTK2_FACTORY_H_
