/*!
    \file src/cpaf/win32/textwidget.cpp
    \brief Implementation of cpaf::win32::gui::TextWidget
    \date Created: 2005-07-17
*/

#include <cpaf/win32/gui/textwidget.h>
#include <cpaf/win32/gui/entrybox.h>

using namespace cpaf::win32::gui;

int TextWidget::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch(msg)
    {
    case WM_GETDLGCODE:
        // don't tab navigate out of a textwidget and don't
        // select all of the text when navigating into one
        return DLGC_WANTCHARS | DLGC_WANTARROWS | DLGC_WANTALLKEYS;
    }

    return Widget::process_message(hwnd, msg, w_param, l_param);
}

void TextWidget::set_text(const std::string &s)
{
    set_window_text(s);
}

std::string TextWidget::get_text() const
{
    return get_window_text();
}

std::string TextWidget::get_text(const cpaf::TextRange &range) const
{
    return "";
}

cpaf::text_range_t TextWidget::get_length() const
{
    return 0;
}

cpaf::TextRange TextWidget::get_selection_range() const
{
    return 0;
}

void TextWidget::set_selection_range(const cpaf::TextRange &range)
{

}

bool TextWidget::get_selection_bounds(cpaf::TextRange &range) const
{
    return false;
}

void TextWidget::set_selection_bounds(const cpaf::TextRange &range)
{

}

cpaf::text_range_t TextWidget::get_insertion_point() const
{
    return 0;
}

void TextWidget::set_insertion_point(cpaf::text_range_t pos)
{

}

void TextWidget::delete_range(const cpaf::TextRange &range)
{

}

cpaf::text_range_t TextWidget::insert_text(const std::string &str, cpaf::text_range_t pos)
{
    return 0;
}

cpaf::text_range_t TextWidget::insert_text(const std::string &str)
{
    return 0;
}

void TextWidget::set_max_length(cpaf::text_range_t len)
{

}

void TextWidget::set_read_only(bool b)
{

}

bool TextWidget::is_read_only() const
{
    return false;
}
