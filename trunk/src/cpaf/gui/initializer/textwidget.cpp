/*!
    \file src/cpaf/gui/initializer/textwidget.cpp
    \brief cpaf::gui::TextWidget initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/textwidget.h>

void cpaf::gui::initializer::TextWidgetData::set_text(const std::string &str)
{
    m_text = str;
}

std::string cpaf::gui::initializer::TextWidgetData::get_text() const
{
    return m_text;
}
