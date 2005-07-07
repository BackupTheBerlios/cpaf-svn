/*!
    \file include/cpaf/win32/textbox.h
    \brief win32 version of cpaf::api::gui::TextBox
    \date Created: 2005-07-07
*/

#ifndef CPAF_WIN32_GUI_TEXTBOX_H
#define CPAF_WIN32_GUI_TEXTBOX_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/gui/textbox.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class TextBox : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::TextBox
{
public:
    TextBox() { }

    void create(const cpaf::gui::initializer::TextBoxData &params);

    virtual void set_text(const std::string &s);
    virtual std::string get_text();
};

        } // gui
    } // win32
} // cpaf

#endif
