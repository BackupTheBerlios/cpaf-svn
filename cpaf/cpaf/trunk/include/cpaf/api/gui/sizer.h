/*
Sizer interface definition
*/

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
