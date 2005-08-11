/*!
    \file include/cpaf/win32/textbox.h
    \brief win32 version of cpaf::api::gui::TextBox
    \date Created: 2005-07-07
*/

#ifndef CPAF_WIN32_GUI_TEXTBOX_H
#define CPAF_WIN32_GUI_TEXTBOX_H

#include <cpaf/win32/gui/textwidget.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/gui/textbox.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class TextBox : public virtual cpaf::win32::gui::TextWidget, public virtual cpaf::api::gui::TextBox
{
public:
    void create(const cpaf::gui::initializer::TextBoxData &params);

    std::string get_text(const cpaf::TextRange &range) const;
};

        } // gui
    } // win32
} // cpaf

#endif
