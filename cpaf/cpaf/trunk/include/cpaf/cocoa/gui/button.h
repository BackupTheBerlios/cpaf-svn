/**
 * \file include/cpaf/cocoa/gui/button.h
 * \brief Cocoa version of api::Button
 * \date 2005-04-29
 */

#ifndef CPAF_COCOA_GUI_BUTTON_H
#define CPAF_COCOA_GUI_BUTTON_H

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/api/gui/button.h>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class Button : public virtual cpaf::cocoa::gui::Widget, virtual cpaf::api::gui::Button
{
public:
    Button(cpaf::api::gui::Widget *parent);

    virtual void set_label(const std::string &label);
    virtual std::string get_label();

protected:
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_BUTTON_H
