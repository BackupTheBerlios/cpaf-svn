/*!
    \file include/cpaf/api/gui/widget.h
    \brief Widget interface declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_API_GUI_WIDGET_H
#define CPAF_API_GUI_WIDGET_H

#include <cpaf/gui/initializer/widget.h>
#include <cpaf/api/gui/object.h>

namespace cpaf {
    namespace gui { class Panel; class Window; }
    namespace api {
        namespace gui {

class Widget : public virtual Object
{
public:
    typedef cpaf::gui::initializer::WidgetData data_type; //!< Initialization data used for Widgets.

    virtual void *get_handle() const = 0;
    virtual void enable(bool e) = 0;
    virtual void show(bool show, bool focus) = 0;
    virtual bool is_enabled() const = 0;
    virtual bool is_shown() const = 0;
    virtual void destroy() = 0;

    virtual cpaf::gui::Panel *get_parent() const = 0;
    virtual cpaf::gui::Window *get_parent_window() const = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_WIDGET_H
