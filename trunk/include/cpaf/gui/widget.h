/*!
    \file include/cpaf/gui/widget.h
    \brief cpaf::gui::Widget declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_GUI_WIDGET_H
#define CPAF_GUI_WIDGET_H

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/types.h>
//#include <cpaf/gui/object.h>
#include <cpaf/gui/factory/widget.h>

namespace cpaf {
    namespace gui {

        class App;

class CPAF_API Widget
{
protected:
    cpaf::api::gui::Widget *m_impl;
    void set_impl(cpaf::api::gui::Widget *impl);

    Widget();

public:
    virtual ~Widget();

    operator cpaf::api::gui::Widget *();

    void set_size(const cpaf::Size &s);
    void set_min_size(const cpaf::Size &s);
    void set_max_size(const cpaf::Size &s);
    void set_position(const cpaf::Point &p);
    cpaf::Size get_size();
    cpaf::Size get_min_size();
    cpaf::Size get_max_size();
    cpaf::Point get_position();

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
