/*
Client wrapper for api::gui::Widget
this object is not createable by client code
*/

#ifndef CPAF_GUI_WIDGET_H
#define CPAF_GUI_WIDGET_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/object.h>
#include <cpaf/gui/factory/widget.h>

namespace cpaf {
    namespace gui {

        class App;

class CPAF_API Widget : public Object
{
protected:
    cpaf::api::gui::Widget *m_impl;

    Widget();

public:
    virtual ~Widget();

    void set_impl(cpaf::api::gui::Object *impl);
    operator cpaf::api::gui::Widget *();

    virtual void *get_handle();
    virtual void enable(bool e);
    virtual void disable();
    virtual void show(bool show = true, bool focus = false);
    virtual void hide();
    virtual bool is_enabled();
    virtual bool is_shown();
    int get_id();

};

    } // gui
} // cpaf

#endif // CPAF_GUI_WIDGET_H
