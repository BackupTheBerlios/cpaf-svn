/*
TopLevel interface definition
*/

#include <cpaf/api/gui/widget.h>

// prototype instead of including the header
//namespace std { class string; }
// doesn't work, so header it is
#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

/*!
    \brief The TopLevel interface defines a widget that is a top level widget.
*/
class TopLevel : public Widget
{
public:

    virtual void set_title(const std::string &t) = 0;
    virtual std::string get_title() = 0;

    /*
    virtual void maximize() = 0;
    virtual void minimize() = 0;
    */

    virtual void set_client_size(cpaf::Size s) = 0;
    virtual cpaf::Size get_client_size() = 0;
    virtual cpaf::Point get_client_position() = 0;

};

        } // gui
    } // api
} // cpaf
