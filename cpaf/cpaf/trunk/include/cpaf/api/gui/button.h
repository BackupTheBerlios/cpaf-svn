/*
Button interface definition
*/

#ifndef CPAF_API_GUI_BUTTON_H
#define CPAF_API_GUI_BUTTON_H

//! \todo "Controls" need a common base (checkboxes, radio, ...)
#include <cpaf/api/gui/widget.h>

#include <cpaf/string.h>

namespace cpaf {
    namespace api {
        namespace gui {

class Button : public virtual Widget
{
public:
    static int factory_key;

    /*!
        \brief Sets the label of the button

        \todo Move this to the common base
    */
    virtual void set_label(const cpaf::String &label) = 0;

    /*!
        \return The button label

        \todo Move this to the common base
    */
    virtual cpaf::String get_label() = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_BUTTON_H
