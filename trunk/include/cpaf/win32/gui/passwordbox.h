/*!
    \file include/cpaf/win32/passwordbox.h
    \brief win32 version of cpaf::api::gui::PasswordBox
    \date Created: 
*/

#ifndef CPAF_WIN32_GUI_PASSWORDBOX_H
#define CPAF_WIN32_GUI_PASSWORDBOX_H

#include <cpaf/win32/gui/textwidget.h>
#include <cpaf/api/gui/passwordbox.h>
#include <cpaf/gui/passwordbox.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class PasswordBox : public virtual cpaf::win32::gui::TextWidget, public virtual cpaf::api::gui::PasswordBox
{
public:
    void create(const cpaf::gui::initializer::PasswordBoxData &params);
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_PASSWORDBOX_H