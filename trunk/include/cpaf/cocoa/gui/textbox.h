/*!
    \file include/cpaf/cocoa/textbox.h
    \brief Cocoa version of cpaf::api::gui::TextBox
    \date Created: 2005-07-08
*/

#ifndef CPAF_COCOA_GUI_TEXTBOX_H
#define CPAF_COCOA_GUI_TEXTBOX_H

#include <cpaf/cocoa/gui/textwidget.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/gui/textbox.h>

#include <string>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class TextBox : public virtual cpaf::cocoa::gui::TextWidget, public virtual cpaf::api::gui::TextBox
{
public:
    TextBox() { }

    void create(const cpaf::gui::initializer::TextBoxData &params);
};

        } // gui
    } // cocoa
} // cpaf

#endif
