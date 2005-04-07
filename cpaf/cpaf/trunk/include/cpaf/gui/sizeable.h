/*
Client wrapper for api::gui::Sizeable
*/

#ifndef CPAF_GUI_SIZEABLE_H
#define CPAF_GUI_SIZEABLE_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/defs.h>

namespace cpaf {
    namespace gui {

class CPAF_EXP Sizeable
{
protected:
    // Widget and Sizeable are responsible for cleaning up the implementation object
    // so they use the booast::shared_ptr typedefs instead of raw pointers
#if _MSC_VER
#   pragma warning(disable:4251) // class 'boost::shared_ptr<>' needs to have dll-interface to be used by clients
#endif
    cpaf::api::gui::SizeablePtr m_impl;
#if _MSV_VER
#   pragma warning(default:4251)
#endif

    Sizeable(const cpaf::api::gui::SizeablePtr &p);

public:
    virtual ~Sizeable();

    virtual void set_size(cpaf::Size s);
    virtual void set_min_size(cpaf::Size s);
    virtual void set_max_size(cpaf::Size s);
    virtual void set_position(cpaf::Point p);
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size();
    virtual cpaf::Size get_max_size();
    virtual cpaf::Point get_position();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_SIZEABLE_H
