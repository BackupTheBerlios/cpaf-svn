/*
Widget interface definition
*/

#ifndef _CPAF_API_GUI_WIDGET_H_
#define _CPAF_API_GUI_WIDGET_H_

#include <cpaf/api/gui/sizeable.h>

namespace cpaf {
    namespace api {
        namespace gui {

/*!
    \brief The Widget interface represents a generic widget that appears on screen. All
    widgets are based off of this interface.
*/
class Widget : public Sizeable
{
public:

    /*!
        \return A native handle for the widget.
    */
    virtual int get_handle() = 0; // int return value for now...

    /*!
        \brief Enables or disables the widget. Disabled widgets cannot recieve user input.
    */
    virtual void enable(bool e) = 0;

    /*!
        \brief Shows or hides a widget.
    */
    virtual void show(bool show, bool activate) = 0;

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

#endif // _CPAF_API_GUI_WIDGET_H_
