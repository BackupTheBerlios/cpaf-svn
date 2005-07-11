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
    namespace api {
        namespace gui {


class Widget : public virtual Object
{
public:
    typedef cpaf::gui::initializer::WidgetData data_type; //!< Initialization data used for Widgets.

    virtual void *get_handle() = 0;
    virtual void enable(bool e) = 0;
    virtual void show(bool show, bool focus) = 0;
    virtual bool is_enabled() = 0;
    virtual bool is_shown() = 0;
    virtual void destroy() = 0;

    // commented until they are needed
    /*
    virtual void get_children() = 0;
    virtual void set_sizer(cpaf::api::Sizer s) = 0;
    virtual cpaf::api::Sizer set_sizer() = 0;
    */
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_WIDGET_H
