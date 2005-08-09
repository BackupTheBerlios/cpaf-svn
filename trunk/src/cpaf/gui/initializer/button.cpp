/*!
    \file src/cpaf/gui/initializer/button.cpp
    \brief cpaf::gui::Button initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/button.h>

using namespace cpaf::gui::initializer;

void ButtonData::set_label(const std::string &str)
{
    m_label = str;
}

std::string ButtonData::get_label() const
{
    return m_label;
}

cpaf::gui::ButtonInitializer::ButtonInitializer()
    : cpaf::gui::initializer::Button<ButtonInitializer>(new data_type)
{ }

cpaf::gui::ButtonInitializer::data_type cpaf::gui::ButtonInitializer::get_data() const
{
    return *m_data;
}
