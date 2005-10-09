/*!
    \file src/cpaf/cocoa/panel.mm
    \brief Implementation of cpaf::cocoa::gui::Panel
    \date Created: 
*/

#include <cpaf/cocoa/gui/panel.h>
#include <cpaf/exception.h>

CPAF_COCOA_INTERFACE(View)
CPAF_COCOA_IMPLEMENTATION(View)

using namespace cpaf::cocoa::gui;

void Panel::create(const cpaf::gui::initializer::PanelData &params)
{
    m_layout_manager = params.get_layout_manager();
    if( !m_layout_manager )
        throw cpaf::Exception(cpaf::Exception::PANEL_NO_LAYOUT_MANAGER, __LINE__, __FILE__);

    Widget::create(params, [[CpafView alloc] init]);

    send_event(cpaf::event::WIDGET_CREATE);
}
