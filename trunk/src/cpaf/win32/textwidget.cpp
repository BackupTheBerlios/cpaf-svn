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

std::string cpaf::win32::gui::TextWidget::get_text(const cpaf::TextRange &range)
{
    return "";
}

cpaf::text_range_t cpaf::win32::gui::TextWidget::get_length()
{
    return 0;
}

cpaf::TextRange cpaf::win32::gui::TextWidget::get_selection_range()
{
    return 0;
}

void cpaf::win32::gui::TextWidget::set_selection_range(const cpaf::TextRange &range)
{

}

bool cpaf::win32::gui::TextWidget::get_selection_bounds(cpaf::TextRange &range)
{
    return false;
}

void cpaf::win32::gui::TextWidget::set_selection_bounds(const cpaf::TextRange &range)
{

}

cpaf::text_range_t cpaf::win32::gui::TextWidget::get_insertion_point()
{
    return 0;
}

void cpaf::win32::gui::TextWidget::set_insertion_point(cpaf::text_range_t pos)
{

}

void cpaf::win32::gui::TextWidget::delete_range(const cpaf::TextRange &range)
{

}

void cpaf::win32::gui::TextWidget::insert_text(cpaf::text_range_t pos, const std::string &str)
{

}

void cpaf::win32::gui::TextWidget::set_max_length(cpaf::text_range_t len)
{

}

void cpaf::win32::gui::TextWidget::set_read_only(bool b)
{

}

bool cpaf::win32::gui::TextWidget::is_read_only()
{
    return false;
}
