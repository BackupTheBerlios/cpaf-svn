/*!
    \file include/cpaf/api/gui/toplevel.h
    \brief TopLevel interface declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_API_GUI_TOPLEVEL_H
#define CPAF_API_GUI_TOPLEVEL_H

#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class TopLevel : public virtual Widget
{
public:

    virtual void set_title(const std::string &t) = 0
    virtual std::string get_title() = 0
    virtual void set_client_size(const cpaf::Size &s) = 0
    virtual cpaf::Size get_client_size() = 0
    virtual cpaf::Point get_client_position() = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_TOPLEVEL_H
