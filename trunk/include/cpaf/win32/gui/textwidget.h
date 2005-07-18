/*!
    \file include/cpaf/win32/textwidget.h
    \brief win32 version of cpaf::api::gui::TextWidget
    \date Created: 2005-07-17
*/

#ifndef CPAF_WIN32_GUI_TEXTWIDGET_H
#define CPAF_WIN32_GUI_TEXTWIDGET_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/textwidget.h>
#include <cpaf/gui/textwidget.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class TextWidget : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::TextWidget
{
public:
    virtual void set_text(const std::string &s);
    virtual std::string get_text();
};

        } // gui
    } // win32
} // cpaf

#endif
