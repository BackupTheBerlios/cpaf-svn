/*!
    \file include/cpaf/cocoa/panel.h
    \brief cocoa version of cpaf::api::gui::Panel
    \date Created: 
*/

#ifndef CPAF_COCOA_GUI_PANEL_H
#define CPAF_COCOA_GUI_PANEL_H

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/api/gui/panel.h>
#include <cpaf/gui/panel.h>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class Panel : public virtual cpaf::cocoa::gui::Widget, public virtual cpaf::api::gui::Panel
{
public:
    void create(const cpaf::gui::initializer::PanelData &params);
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_PANEL_H
