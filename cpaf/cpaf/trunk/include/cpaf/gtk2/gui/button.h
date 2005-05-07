/**
 * \file include/cpaf/gtk2/gui/button.h
 * \brief Gtk2 version of api::Button
 * \date 2005-04-14
 */

#ifndef CPAF_GTK2_GUI_BUTTON_H
#define CPAF_GTK2_GUI_BUTTON_H

#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/api/gui/button.h>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class Button : public virtual cpaf::gtk2::gui::Widget, virtual cpaf::api::gui::Button
{
public:
    Button(const cpaf::gui::factory::ButtonData &params);

    virtual void set_label(const std::string &label);
    virtual std::string get_label();

protected:
    GtkWidget * m_label;
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_BUTTON_H
