/*!
    \file include/cpaf/win32/button.h
    \brief win32 version of cpaf::api::gui::Button
    \date Created: 2005-04-05
*/

#ifndef CPAF_WIN32_GUI_BUTTON_H
#define CPAF_WIN32_GUI_BUTTON_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/button.h>

// for the initializer factory
#include <cpaf/gui/button.h>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Button : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::Button
{
public:
    Button() { }

    void create(const cpaf::gui::initializer::ButtonData &params);

    virtual void set_label(const std::string &label);
    virtual std::string get_label();
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_BUTTON_H
