/*
Widget interface definition
*/

#include <cpaf/api/gui/sizeable.h>

namespace cpaf {
    namespace api {
        namespace gui {

/*!
    \brief The Widget interface represents a generic widget that appears on screen. All
    widgets are based off of this interface.
*/
class Widget : public Sizeable
{
public:

    virtual int get_handle() = 0; // int return value for now...
    virtual void enable(bool e) = 0;
    virtual void show(bool show, bool activate) = 0;
    virtual bool is_enabled() = 0;
    virtual bool is_shown() = 0;

    // commented until they are needed
    /*
    virtual void get_children() = 0;
    virtual void set_sizer(cpaf::api::Sizer s) = 0;
    virtual cpaf::api::Sizer set_sizer() = 0;
    */

};

        } // gui
    } // api
} // cpaf
