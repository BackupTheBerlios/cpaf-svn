/*!
    \file include/cpaf/api/gui/panel.h
    \brief Panel interface declaration
    \date Created: 
*/

#ifndef CPAF_API_GUI_PANEL_H
#define CPAF_API_GUI_PANEL_H

#include <cpaf/gui/initializer/panel.h>
#include <cpaf/api/gui/widget.h>

namespace cpaf {
    namespace api {
        namespace gui {

class Panel : public virtual Widget
{
public:
    typedef cpaf::gui::initializer::PanelData data_type; //!< Initialization data used for Panel.

    virtual void create(const data_type &init_params) = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_PANEL_H
