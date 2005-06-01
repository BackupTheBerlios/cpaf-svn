/*!
    \file include/cpaf/api/gui/sizer.h
    \brief Sizer interface declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_API_GUI_SIZER_H
#define CPAF_API_GUI_SIZER_H

#include <cpaf/api/gui/object.h>

namespace cpaf {
    namespace api {
        namespace gui {

class Sizer : public Object
{
public:

    virtual void layout() = 0;
    virtual void add(cpaf::api::gui::Object *s) = 0;
    virtual void remove(cpaf::api::gui::Object *s) = 0;

};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_SIZER_H
