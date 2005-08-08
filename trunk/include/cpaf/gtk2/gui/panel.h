/*!
    \file include/cpaf/gtk2/panel.h
    \brief gtk2 version of cpaf::api::gui::Panel
    \date Created: 
*/

#ifndef CPAF_GTK2_GUI_PANEL_H
#define CPAF_GTK2_GUI_PANEL_H

#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/api/gui/panel.h>
#include <cpaf/gui/panel.h>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class Panel : public virtual cpaf::gtk2::gui::Widget, public virtual cpaf::api::gui::Panel
{
public:
    void create(const cpaf::gui::initializer::PanelData &params);
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_PANEL_H
