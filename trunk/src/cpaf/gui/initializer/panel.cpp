/*!
    \file src/cpaf/gui/initializer/panel.cpp
    \brief cpaf::gui::Panel initializer implementation
    \date Created: 
*/

#include <cpaf/gui/initializer/panel.h>

cpaf::gui::PanelInitializer::PanelInitializer()
    : cpaf::gui::initializer::Panel<PanelInitializer>(new data_type)
{ }

cpaf::gui::PanelInitializer::data_type cpaf::gui::PanelInitializer::get_data() const
{
    return *m_data;
}
