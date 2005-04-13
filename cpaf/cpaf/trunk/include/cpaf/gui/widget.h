/*
Client wrapper for api::gui::Widget
this object is not createable by client code
*/

#ifndef CPAF_GUI_WIDGET_H
#define CPAF_GUI_WIDGET_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/gui/object.h>

namespace cpaf {
    namespace gui {

        class App;

class CPAF_API Widget : public Object
{
    friend class cpaf::gui::App;

protected:
    cpaf::api::gui::Widget *m_impl;

    //Widget(const cpaf::api::gui::WidgetPtr &p);
    Widget(cpaf::api::gui::Widget *p);

public:
    virtual ~Widget();

    operator cpaf::api::gui::Widget *();

    virtual void *get_handle();
    virtual void enable(bool e);
    virtual void disable();
    virtual void show(bool show = true, bool focus = false);
    virtual void hide();
    virtual bool is_enabled();
    virtual bool is_shown();

};

    } // gui
} // cpaf

#endif // CPAF_GUI_WIDGET_H
