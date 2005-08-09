/*!
    \file src/cpaf/win32/textbox.cpp
    \brief Implementation of cpaf::win32::gui::TextBox
    \date Created: 2005-07-17
*/

#include <cpaf/win32/gui/entrybox.h>

void cpaf::win32::gui::EntryBox::create(const cpaf::gui::initializer::EntryBoxData &params)
{
    // create an entry box
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, true, TEXT("EDIT"), params.get_text().c_str(),
        WS_CHILD | WS_TABSTOP, WS_EX_CLIENTEDGE);
}

int cpaf::win32::gui::EntryBox::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch(msg)
    {
    case WM_GETDLGCODE:
        // allow tab navigation into and out of entryboxes
        // and select all of the text when navigating into an entrybox
        return DLGC_HASSETSEL | DLGC_WANTCHARS | DLGC_WANTARROWS;
    }

    return cpaf::win32::gui::TextWidget::process_message(hwnd, msg, w_param, l_param);
}

void cpaf::win32::gui::EntryBox::set_password_mode(bool mode)
{
    ::SendMessage(m_hwnd, EM_SETPASSWORDCHAR, (mode) ? '*' : 0, 0);
    ::RedrawWindow(m_hwnd, 0, 0, RDW_INVALIDATE);
}

bool cpaf::win32::gui::EntryBox::get_password_mode()
{
    return ::SendMessage(m_hwnd, EM_GETPASSWORDCHAR, 0, 0) != 0;
}
