/*!
    \file src/cpaf/win32/textwidget.cpp
    \brief Implementation of cpaf::win32::gui::TextWidget
    \date Created: 2005-07-17
*/

#include <cpaf/win32/gui/textwidget.h>
#include <cpaf/win32/gui/entrybox.h>

int cpaf::win32::gui::TextWidget::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch(msg)
    {
    case WM_GETDLGCODE:
        // don't tab navigate out of a textwidget and don't
        // select all of the text when navigating into one
        return DLGC_WANTCHARS | DLGC_WANTARROWS | DLGC_WANTALLKEYS;
    }

    return cpaf::win32::gui::Widget::process_message(hwnd, msg, w_param, l_param);
}

void cpaf::win32::gui::TextWidget::set_text(const std::string &s)
{
    set_window_text(s);
}

std::string cpaf::win32::gui::TextWidget::get_text() const
{
    return get_window_text();
}

std::string cpaf::win32::gui::TextWidget::get_text(const cpaf::TextRange &range) const
{
    return "";
}

cpaf::text_range_t cpaf::win32::gui::TextWidget::get_length() const
{
    return 0;
}

cpaf::TextRange cpaf::win32::gui::TextWidget::get_selection_range() const
{
    return 0;
}

void cpaf::win32::gui::TextWidget::set_selection_range(const cpaf::TextRange &range)
{

}

bool cpaf::win32::gui::TextWidget::get_selection_bounds(cpaf::TextRange &range) const
{
    return false;
}

void cpaf::win32::gui::TextWidget::set_selection_bounds(const cpaf::TextRange &range)
{

}

cpaf::text_range_t cpaf::win32::gui::TextWidget::get_insertion_point() const
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

bool cpaf::win32::gui::TextWidget::is_read_only() const
{
    return false;
}
