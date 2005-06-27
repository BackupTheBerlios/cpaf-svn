/*!
    \file include/cpaf/api/gui/button.h
    \brief Button interface declaration
    \date Created: 2005-04-05
*/

#ifndef CPAF_API_GUI_BUTTON_H
#define CPAF_API_GUI_BUTTON_H

#include <cpaf/gui/initializer/button.h>
#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class Button : public virtual Widget
{
    //! \todo "Controls" need a common base (checkboxes, radio, ...)
public:
    typedef cpaf::gui::initializer::ButtonData data_type; //!< Initialization data used for Buttons

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    virtual void create(const data_type &init_params) = 0;

    /*!
        \brief Sets the label of the button

        \todo Move this to the common base
    */
    virtual void set_label(const std::string &label) = 0;

    /*!
        \return The button label

        \todo Move this to the common base
    */
    virtual std::string get_label() = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_BUTTON_H
