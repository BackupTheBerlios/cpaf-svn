/*
Client wrapper for api::gui::Widget
this object is not createable by client code
*/

#ifndef CPAF_GUI_WIDGET_H
#define CPAF_GUI_WIDGET_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/sizeable.h>

namespace cpaf {
    namespace gui {

class CPAF_API Widget : public Sizeable
{
protected:
    // Widget and Sizeable are responsible for cleaning up the implementation object
    // so they use the booast::shared_ptr typedefs instead of raw pointers
#if _MSC_VER
#   pragma warning(disable:4251) // class 'boost::shared_ptr<>' needs to have dll-interface to be used by clients
#endif
    cpaf::api::gui::WidgetPtr m_impl;
#if _MSV_VER
#   pragma warning(default:4251)
#endif

    Widget(const cpaf::api::gui::WidgetPtr &p);

public:
    virtual ~Widget();

    virtual int get_handle();
    virtual void enable(bool e);
    virtual void disable();
    virtual void show(bool show = true, bool activate = true);
    virtual void hide();
    virtual bool is_enabled();
    virtual bool is_shown();

};

    } // gui
} // cpaf

#endif // CPAF_GUI_WIDGET_H
