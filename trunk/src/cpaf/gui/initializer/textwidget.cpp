/*!
    \file src/cpaf/gui/initializer/textwidget.cpp
    \brief cpaf::gui::TextWidget initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/textwidget.h>

using namespace cpaf::gui::initializer;

void TextWidgetData::set_text(const std::string &str)
{
    m_text = str;
}

std::string TextWidgetData::get_text() const
{
    return m_text;
}
