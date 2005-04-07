/*
win32 factories
*/

#ifndef _CPAF_WIN32_FACTORY_H_
#define _CPAF_WIN32_FACTORY_H_

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

#endif // _CPAF_WIN32_FACTORY_H_
