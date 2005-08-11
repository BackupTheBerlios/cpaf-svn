/*!
    \file src/cpaf/win32/textbox.cpp
    \brief Implementation of cpaf::win32::gui::TextBox
    \date Created: 2005-07-07
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
