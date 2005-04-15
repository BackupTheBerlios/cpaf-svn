/*
Client wrapper for api::gui::Object
*/

#ifndef CPAF_GUI_OBJECT_H
#define CPAF_GUI_OBJECT_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/defs.h>

namespace cpaf {
    namespace gui {

class CPAF_API Object
{
protected:
    cpaf::api::gui::Object *m_impl;

    //Object(const cpaf::api::gui::ObjectPtr &p);
    Object(cpaf::api::gui::Object *p);

public:
    virtual ~Object();

    operator cpaf::api::gui::Object *();

    virtual void set_size(const cpaf::Size &s);
    virtual void set_min_size(const cpaf::Size &s);
    virtual void set_max_size(const cpaf::Size &s);
    virtual void set_position(const cpaf::Point &p);
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size();
    virtual cpaf::Size get_max_size();
    virtual cpaf::Point get_position();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_OBJECT_H