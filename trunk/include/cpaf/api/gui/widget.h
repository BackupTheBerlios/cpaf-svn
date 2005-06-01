/*!
    \file include/cpaf/api/gui/widget.h
    \brief Widget interface declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_API_GUI_WIDGET_H
#define CPAF_API_GUI_WIDGET_H

#include <cpaf/api/gui/object.h>

namespace cpaf {
    namespace gui { class Widget; } // prototype
    namespace api {
        namespace gui {

/*!
    \brief The Widget interface represents a generic widget that appears on screen. All
    widgets are based off of this interface.
*/
class Widget : public virtual Object
{
public:
    /*!
        \return A native handle for the widget. This value is returned as a void*, and how you use this value
            is dependant on the port you are working with. For win32, simply casting the return value to a HWND
            is sufficient.
    */
    virtual void *get_handle() = 0;

    /*!
        \return A widget identifier which uniquely identifies this widget. Widget identifiers are assigned
            automatically during widget creation and cannot be changed.
    */
    virtual int get_id() = 0;

    /*!
        \brief Enables or disables the widget. Disabled widgets cannot recieve user input.
    */
    virtual void enable(bool e) = 0;

    /*!
        \brief Shows or hides a widget.
    */
    virtual void show(bool show, bool focus) = 0;

    /*!
        This function determines wether or not the widget is enabled. If any of a widget's parents
        are disabled, the widget is considered disabled. If all of the parents are enabled and the widget
        is also enabled, it is not disabled.
    */
    virtual bool is_enabled() = 0;

    /*!
        \return True if the widget is shown and none of its parents are hidden, false otherwise. A widget
        is shown if it would be drawn by the system. A widget may be completely obscured by another widget,
        but if the widget would otherwise be drawn, this function returns true.
    */
    virtual bool is_shown() = 0;

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
