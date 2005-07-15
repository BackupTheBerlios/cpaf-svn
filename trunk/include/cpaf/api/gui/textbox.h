/*!
    \file include/cpaf/api/gui/textbox.h
    \brief TextBox interface declaration
    \date Created: 2005-07-07
*/

#ifndef CPAF_API_GUI_TEXTBOX_H
#define CPAF_API_GUI_TEXTBOX_H

#include <cpaf/gui/initializer/textbox.h>
#include <cpaf/api/gui/textwidget.h>

namespace cpaf {
    namespace api {
        namespace gui {

class TextBox : public virtual TextWidget
{
public:
    typedef cpaf::gui::initializer::TextBoxData data_type; //!< Initialization data used for TextBoxes.

    virtual void create(const data_type &init_params) = 0;
};

        } // gui
    } // api
} // cpaf

#endif
