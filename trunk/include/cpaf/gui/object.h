/*!
    \file include/cpaf/gui/object.h
    \brief cpaf::gui::Object declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_OBJECT_H
#define CPAF_GUI_OBJECT_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/types.h>
#include <cpaf/gui/factory/object.h>

namespace cpaf {
    namespace gui {

class CPAF_API Object
{
public:

protected:
    cpaf::api::gui::Object *m_impl;
    void set_impl(cpaf::api::gui::Object *impl);

    Object();

public:
    virtual ~Object();

    operator cpaf::api::gui::Object *();

    void set_size(const cpaf::Size &s);
    void set_min_size(const cpaf::Size &s);
    void set_max_size(const cpaf::Size &s);
    void set_position(const cpaf::Point &p);
    cpaf::Size get_size();
    cpaf::Size get_min_size();
    cpaf::Size get_max_size();
    cpaf::Point get_position();
};
    } // gui
} // cpaf

#endif // CPAF_GUI_OBJECT_H
