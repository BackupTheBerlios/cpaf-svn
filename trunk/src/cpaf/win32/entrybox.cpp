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
        WS_CHILD, WS_EX_CLIENTEDGE);
    //::SendMessage(m_hwnd, WM_SETFONT, (WPARAM)::GetStockObject(DEFAULT_GUI_FONT), 1);
}

void cpaf::win32::gui::EntryBox::set_password_mode(bool mode)
{
    ::SendMessage(m_hwnd, EM_SETPASSWORDCHAR, (mode) ? '*' : 0, 0);
    ::RedrawWindow(m_hwnd, 0, 0, RDW_INVALIDATE);
}

bool cpaf::win32::gui::EntryBox::get_password_mode()
{
    return ::SendMessage(m_hwnd, EM_GETPASSWORDCHAR, 0, 0);
}
