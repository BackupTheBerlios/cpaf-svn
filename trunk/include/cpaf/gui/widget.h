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
#include <cpaf/gui/initializer/widget.h>

namespace cpaf {
    namespace gui {

class CPAF_API Widget
{
public:
    typedef cpaf::api::gui::Widget api_type;

    void destroy();

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

    virtual ~Widget();

private:
    int m_id;

    cpaf::api::gui::Widget *m_impl;

protected:
    Widget(cpaf::api::gui::Widget *impl);

    template<typename T> T *get_impl()
    {
        return dynamic_cast<T*>(m_impl);
    }

public:
    operator cpaf::api::gui::Widget *();
};

    } // gui
} // cpaf

#endif // CPAF_GUI_WIDGET_H
