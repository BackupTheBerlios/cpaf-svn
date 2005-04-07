/*
Sizer interface definition
*/

#ifndef CPAF_API_GUI_SIZER_H
#define CPAF_API_GUI_SIZER_H

#include <cpaf/api/gui/sizeable.h>

namespace cpaf {
    namespace api {
        namespace gui {

class Sizer : public Sizeable
{
public:

    virtual void layout() = 0;
    virtual void add(cpaf::api::gui::Sizeable *s) = 0;
    virtual void remove(cpaf::api::gui::Sizeable *s) = 0;

};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_SIZER_H
