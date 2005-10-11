/*!
    \file src/cpaf/win32/textbox.cpp
    \brief Implementation of cpaf::win32::gui::TextBox
    \date Created: 2005-07-17
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright (C) 2005 Robin McNeill
    http://www.snakesoft.net
    snakechomp (at) snakesoft [dot] net
*/

#include <cpaf/win32/gui/entrybox.h>

using namespace cpaf::win32::gui;

void EntryBox::create(const cpaf::gui::initializer::EntryBoxData &params)
{
    // create an entry box
    Widget::create(CreationInfo(this), params, true, TEXT("EDIT"), params.get_text().c_str(),
        WS_CHILD | WS_TABSTOP | ES_NOHIDESEL, WS_EX_CLIENTEDGE);
}

int EntryBox::process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch(msg)
    {
    case WM_GETDLGCODE:
        // allow tab navigation into and out of entryboxes
        // and select all of the text when navigating into an entrybox
        return DLGC_HASSETSEL | DLGC_WANTCHARS | DLGC_WANTARROWS;
    }

    return TextWidget::process_message(hwnd, msg, w_param, l_param);
}

void EntryBox::set_password_mode(bool mode)
{
    ::SendMessage(m_hwnd, EM_SETPASSWORDCHAR, (mode) ? '*' : 0, 0);
    ::RedrawWindow(m_hwnd, 0, 0, RDW_INVALIDATE);
}

bool EntryBox::get_password_mode()
{
    return ::SendMessage(m_hwnd, EM_GETPASSWORDCHAR, 0, 0) != 0;
}

std::string EntryBox::get_text(const cpaf::TextRange &range) const
{
    TextRange r = range.normalize(::GetWindowTextLength(m_hwnd));
    return get_window_text().substr(r.first, r.second - r.first);
}
