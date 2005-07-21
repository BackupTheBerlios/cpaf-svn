/*!
    \file src/cpaf/win32/passwordbox.cpp
    \brief Implementation of cpaf::win32::gui::PasswordBox
    \date Created: 
*/

#include <cpaf/win32/gui/passwordbox.h>

void cpaf::win32::gui::PasswordBox::create(const cpaf::gui::initializer::PasswordBoxData &params)
{
    // create a password box
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, true, TEXT("EDIT"), params.m_text.c_str(),
        WS_CHILD | ES_PASSWORD, WS_EX_CLIENTEDGE);
}
