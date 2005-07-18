/*!
    \file src/cpaf/win32/textwidget.cpp
    \brief Implementation of cpaf::win32::gui::TextWidget
    \date Created: 2005-07-17
*/

#include <cpaf/win32/gui/textwidget.h>

void cpaf::win32::gui::TextWidget::set_text(const std::string &s)
{
    set_window_text(s);
}

std::string cpaf::win32::gui::TextWidget::get_text()
{
    return get_window_text();
}
