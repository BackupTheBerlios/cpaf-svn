/*!
    \file src/cpaf/win32/textbox.cpp
    \brief Implementation of cpaf::win32::gui::TextBox
    \date Created: 2005-07-07
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

#include <cpaf/win32/gui/textbox.h>

using namespace cpaf::win32::gui;

void TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
    // create a textbox
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, true, TEXT("EDIT"), params.get_text().c_str(),
        WS_CHILD | ES_MULTILINE | ES_NOHIDESEL | WS_VSCROLL | WS_TABSTOP, WS_EX_CLIENTEDGE);
}

std::string TextBox::get_text(const cpaf::TextRange &range) const
{
    int len = ::GetWindowTextLength(m_hwnd);
    TextRange r = range.normalize(len);

    // get the character buffer directly to access a range of text
    HLOCAL mem = (HLOCAL)::SendMessage(m_hwnd, EM_GETHANDLE, 0, 0);

    //! \todo This is coded for winxp only (maybe 2k also), won't work elsewhere
    // we need to convert to ansi for now
    wchar_t *wbuff = (wchar_t*)::LocalLock(mem);
    
    int size = ::WideCharToMultiByte(CP_ACP, 0, wbuff, len+1, 0, 0, 0, 0);

    char *buff = new char[size];

    ::WideCharToMultiByte(CP_ACP, 0, wbuff, len+1, buff, size, 0, 0);

    std::string str(buff, r.first, r.second - r.first);

    // unlock the buffer
    ::LocalUnlock(mem);

    delete[] buff;

    return str;
}
