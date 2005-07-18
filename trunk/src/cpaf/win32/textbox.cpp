/*!
    \file src/cpaf/win32/textbox.cpp
    \brief Implementation of cpaf::win32::gui::TextBox
    \date Created: 2005-07-07
*/

#include <cpaf/win32/gui/textbox.h>

void cpaf::win32::gui::TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
    // create a textbox
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, true, TEXT("EDIT"), params.m_text.c_str(),
        WS_CHILD | ES_MULTILINE | WS_VSCROLL, WS_EX_CLIENTEDGE);
}
