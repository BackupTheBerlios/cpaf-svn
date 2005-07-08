/**
 * \file include/cpaf/gtk2/textbox.h
 * \brief Gtk2 version of cpaf::api::gui::TextBox
 * \date Created: 2005-07-08
 */

#ifndef CPAF_GTK2_GUI_TEXTBOX_H
#define CPAF_GTK2_GUI_TEXTBOX_H

#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/api/gui/textbox.h>
#include <cpaf/gui/textbox.h>

#include <string>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class TextBox : public virtual cpaf::gtk2::gui::Widget, public virtual cpaf::api::gui::TextBox
{
public:
    TextBox() { }

    void create(const cpaf::gui::initializer::TextBoxData &params);

    virtual void set_text(const std::string &s);
    virtual std::string get_text();
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_TEXTBOX_H
