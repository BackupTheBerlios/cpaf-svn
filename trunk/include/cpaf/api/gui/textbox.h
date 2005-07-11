/*!
    \file include/cpaf/api/gui/textbox.h
    \brief Widget interface declaration
    \date Created: 2005-07-07
*/

#ifndef CPAF_API_GUI_TEXTBOX_H
#define CPAF_API_GUI_TEXTBOX_H

#include <cpaf/gui/initializer/textbox.h>
#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class TextBox : public virtual Widget
{
public:
    typedef cpaf::gui::initializer::TextBoxData data_type; //!< Initialization data used for TextBoxes.

    virtual void create(const data_type &init_params) = 0;
    virtual void set_text(const std::string &) = 0;
    virtual std::string get_text() = 0;
};

        } // gui
    } // api
} // cpaf

#endif
