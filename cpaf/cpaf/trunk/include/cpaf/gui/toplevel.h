/*
Client wrapper for api::gui::TopLevel
this object is not createable by client code
*/

#ifndef CPAF_GUI_TOPLEVEL_H
#define CPAF_GUI_TOPLEVEL_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/widget.h>

#include <cpaf/string.h>

namespace cpaf {
    namespace gui {

class CPAF_API TopLevel : public Widget
{
private:
    // not shared_ptr because this object will never be responsible for deleting this pointer
    // it only serves to save extraneous casting in source
    cpaf::api::gui::TopLevel *m_impl;

protected:
    //TopLevel(const cpaf::api::gui::TopLevelPtr &p);
    TopLevel(cpaf::api::gui::TopLevel *p);

public:
    virtual ~TopLevel();

    operator cpaf::api::gui::TopLevel *();

    virtual void show(bool show = true, bool focus = true);

    virtual void set_title(const cpaf::String &t);
    virtual cpaf::String get_title();

    virtual void set_client_size(const cpaf::Size &s);
    virtual cpaf::Size get_client_size();
    virtual cpaf::Point get_client_position();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_TOPLEVEL_H
