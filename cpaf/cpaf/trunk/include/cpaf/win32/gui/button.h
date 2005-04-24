/*
win32 version of api::Button
*/

#ifndef CPAF_WIN32_GUI_BUTTON_H
#define CPAF_WIN32_GUI_BUTTON_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/button.h>

namespace cpaf {
    namespace gui { class Widget; }
    namespace win32 {
        namespace gui {

class Button : public virtual cpaf::win32::gui::Widget, virtual cpaf::api::gui::Button
{
public:
    Button(int id, cpaf::api::gui::Widget *parent);

    virtual void set_label(const std::string &label);
    virtual std::string get_label();
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_BUTTON_H
