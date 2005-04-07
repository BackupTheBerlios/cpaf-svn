/*
Client wrapper for api::gui::TopLevel
this object is not createable by client code
*/

#ifndef _CPAF_GUI_TOPLEVEL_H_
#define _CPAF_GUI_TOPLEVEL_H_

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>

// would rather not need this but no way around it right now
#include <string>

namespace cpaf {
    namespace gui {

class CPAF_EXP TopLevel : public Widget
{
private:
    // not shared_ptr because this object will never be responsible for deleting this pointer
    // it only serves to save extraneous casting in source
    cpaf::api::gui::TopLevel *m_impl;

protected:
    TopLevel(const cpaf::api::gui::TopLevelPtr &p);

public:
    virtual void set_title(const std::string &t);
    virtual std::string get_title();

    virtual void set_client_size(cpaf::Size s);
    virtual cpaf::Size get_client_size();
    virtual cpaf::Point get_client_position();
};

    } // gui
} // cpaf

#endif // _CPAF_GUI_TOPLEVEL_H_
