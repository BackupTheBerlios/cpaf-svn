/*!
    \file include/cpaf/cocoa/passwordbox.h
    \brief cocoa version of cpaf::api::gui::PasswordBox
    \date Created: 
*/

#ifndef CPAF_COCOA_GUI_PASSWORDBOX_H
#define CPAF_COCOA_GUI_PASSWORDBOX_H

#include <cpaf/cocoa/gui/textwidget.h>
#include <cpaf/api/gui/passwordbox.h>
#include <cpaf/gui/passwordbox.h>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class PasswordBox : public virtual cpaf::cocoa::gui::TextWidget, public virtual cpaf::api::gui::PasswordBox
{
public:
    void create(const cpaf::gui::initializer::PasswordBoxData &params);
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_PASSWORDBOX_H
