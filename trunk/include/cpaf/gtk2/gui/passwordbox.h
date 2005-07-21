/*!
    \file include/cpaf/gtk2/passwordbox.h
    \brief gtk2 version of cpaf::api::gui::PasswordBox
    \date Created: 
*/

#ifndef CPAF_GTK2_GUI_PASSWORDBOX_H
#define CPAF_GTK2_GUI_PASSWORDBOX_H

#include <cpaf/gtk2/gui/textwidget.h>
#include <cpaf/api/gui/passwordbox.h>
#include <cpaf/gui/passwordbox.h>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class PasswordBox : public virtual cpaf::gtk2::gui::TextWidget, public virtual cpaf::api::gui::PasswordBox
{
public:
    void create(const cpaf::gui::initializer::PasswordBoxData &params);
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_PASSWORDBOX_H
