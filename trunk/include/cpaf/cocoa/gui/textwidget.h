/*!
    \file include/cpaf/cocoa/textwidget.h
    \brief Cocoa version of cpaf::api::gui::TextWidget
    \date Created: 2005-07-14
*/

#ifndef CPAF_COCOA_GUI_TEXTWIDGET_H
#define CPAF_COCOA_GUI_TEXTWIDGET_H

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/api/gui/textwidget.h>
#include <cpaf/gui/textwidget.h>

#include <string>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class TextWidget : public virtual cpaf::cocoa::gui::Widget, public virtual cpaf::api::gui::TextWidget
{
public:
    TextWidget() { }

    void create(const cpaf::gui::initializer::TextWidgetData &params, id widget);

    virtual void set_text(const std::string &s);
    virtual std::string get_text();
};

        } // gui
    } // cocoa
} // cpaf

#endif
