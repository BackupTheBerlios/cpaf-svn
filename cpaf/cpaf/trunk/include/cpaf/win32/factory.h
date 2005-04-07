/*
win32 factories
*/

#ifndef CPAF_WIN32_FACTORY_H
#define CPAF_WIN32_FACTORY_H

#include <cpaf/gui/api-prototypes.h>

namespace cpaf {
   namespace win32 {
        namespace gui {
            namespace factory {

cpaf::api::gui::Widget *create_window();

            } // factory
        } // gui
   } // win32
} // cpaf

#endif // CPAF_WIN32_FACTORY_H
