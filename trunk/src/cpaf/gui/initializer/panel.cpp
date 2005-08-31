/*!
    \file src/cpaf/gui/initializer/panel.cpp
    \brief cpaf::gui::Panel initializer implementation
    \date Created: 
*/

#include <cpaf/gui/initializer/panel.h>

using namespace cpaf::gui::initializer;

PanelData::PanelData()
: m_layout_manager(0)
{ }

void PanelData::set_layout_manager(cpaf::gui::LayoutManager *manager)
{
    m_layout_manager = manager;
}

cpaf::gui::LayoutManager *PanelData::get_layout_manager()
{
    return m_layout_manager;
}

cpaf::gui::PanelInitializer::PanelInitializer()
    : cpaf::gui::initializer::Panel<PanelInitializer>(new data_type)
{ }

cpaf::gui::PanelInitializer::data_type cpaf::gui::PanelInitializer::get_data() const
{
    return *m_data;
}
