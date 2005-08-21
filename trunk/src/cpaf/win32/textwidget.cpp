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

cpaf::text_range_t TextWidget::get_length() const
{
    return ::GetWindowTextLength(m_hwnd);
}

cpaf::TextRange TextWidget::get_selection_range() const
{
    // unfortunately, the win32 api returns a normalized ranged.
    // in other words, we cannot find out where the caret is in relation
    // to the end of the selection. At least not for EntryBox and TextBox
    TextRange r;
    ::SendMessage(m_hwnd, EM_GETSEL, (WPARAM)&r.first, (LPARAM)&r.second);
    return r;
}

void TextWidget::set_selection_range(const cpaf::TextRange &range)
{
    int len = ::GetWindowTextLength(m_hwnd);
    TextRange r = range;
    if( r.first < 0 )
        r.first += len;
    else if( r.first == r.END )
        r.first = len;
    if( r.second < 0 )
        r.second += len;
    else if( r.second == r.END )
        r.second = len;
        
    ::SendMessage(m_hwnd, EM_SETSEL, r.first, r.second);
}

bool TextWidget::get_selection_bounds(cpaf::TextRange &range) const
{
    ::SendMessage(m_hwnd, EM_GETSEL, (WPARAM)&range.first, (LPARAM)&range.second);
    return range.first != range.second;
}

void TextWidget::set_selection_bounds(const cpaf::TextRange &range)
{
    TextRange r = range.normalize(::GetWindowTextLength(m_hwnd));
    ::SendMessage(m_hwnd, EM_SETSEL, r.first, r.second);
}

cpaf::text_range_t TextWidget::get_insertion_point() const
{
    cpaf::text_range_t p;
    ::SendMessage(m_hwnd, EM_GETSEL, (WPARAM)&p, 0);
    return p;
}

void TextWidget::set_insertion_point(cpaf::text_range_t pos)
{
    ::SendMessage(m_hwnd, EM_SETSEL, pos, pos);
}

void TextWidget::delete_range(const cpaf::TextRange &range)
{
    //! \todo Prevent the sending of spurious messages

    // store the current selection
    cpaf::TextRange cur_sel = get_selection_range();

    cpaf::TextRange r = range.normalize(::GetWindowTextLength(m_hwnd));

    // select the range to delete
    ::SendMessage(m_hwnd, EM_SETSEL, r.first, r.second);
    // replace the range with "" to delete it
    //! \todo Should this operation be undo-able?
    ::SendMessage(m_hwnd, EM_REPLACESEL, false, (LPARAM)"");

    // restore the old selection
    set_selection_range(cur_sel);
}

cpaf::text_range_t TextWidget::insert_text(const std::string &str, cpaf::text_range_t pos)
{
    //! \todo Prevent the sending of spurious messages

    // store the current selection
    cpaf::TextRange cur_sel = get_selection_range();

    // move the insertion point
    ::SendMessage(m_hwnd, EM_SETSEL, pos, pos);

    // insert text
    //! \todo Should this operation be undo-able?
    ::SendMessage(m_hwnd, EM_REPLACESEL, false, (LPARAM)str.c_str());

    // if the insertion point was before any existing selection, move the selection
    // so that it still selects the same text
    if( pos < cur_sel.first )
    {
        cur_sel.first += str.length();
        cur_sel.second += str.length();
    }

    // restore the previous selection
    set_selection_range(cur_sel);

    // return the position just after the newly inserted text
    return pos + str.length();
}

cpaf::text_range_t TextWidget::insert_text(const std::string &str)
{
    //! \todo Prevent the sending of spurious messages

    //! \todo Figure out what to do if there is already a selection

    // insert text
    //! \todo Should this operation be undo-able?
    ::SendMessage(m_hwnd, EM_REPLACESEL, false, (LPARAM)str.c_str());


    return 0;
}

void TextWidget::set_max_length(cpaf::text_range_t len)
{
    //! \todo override this for RichEdits because the value 0 means 64,000 and not "no limit"
    ::SendMessage(m_hwnd, EM_SETLIMITTEXT, len, 0);
}

void TextWidget::set_read_only(bool b)
{
    ::SendMessage(m_hwnd, EM_SETREADONLY, b, 0);
}

bool TextWidget::is_read_only() const
{
    return (::GetWindowLong(m_hwnd, GWL_STYLE) & ES_READONLY) != 0;
}
