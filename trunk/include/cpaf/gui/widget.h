/*!
    \file include/cpaf/gui/widget.h
    \brief cpaf::gui::Widget declaration
    \date Created: 2005-04-05
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
    void set_impl(cpaf::api::gui::Widget *impl);

    Widget();

public:
    ~Widget();

    operator cpaf::api::gui::Widget *();

    void *get_handle();
    void enable(bool e);
    void disable();
    void show(bool show = true, bool focus = false);
    void hide();
    bool is_enabled();
    bool is_shown();
    int get_id();

};

    } // gui
} // cpaf

#endif // CPAF_GUI_WIDGET_H
