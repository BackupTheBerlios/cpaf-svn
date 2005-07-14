/*!
    \file include/cpaf/api/gui/textwidget.h
    \brief TextWidget interface declaration
    \date Created: 2005-07-14
*/

#ifndef CPAF_API_GUI_TEXTWIDGET_H
#define CPAF_API_GUI_TEXTWIDGET_H

#include <cpaf/gui/initializer/textwidget.h>
#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class TextWidget : public virtual Widget
{
public:
    typedef cpaf::gui::initializer::TextWidgetData data_type; //!< Initialization data used for TextWidgets.

    virtual void set_text(const std::string &) = 0;
    virtual std::string get_text() = 0;
};

        } // gui
    } // api
} // cpaf

#endif
