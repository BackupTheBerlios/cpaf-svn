/*!
    \file src/cpaf/win32/textbox.cpp
    \brief Implementation of cpaf::win32::gui::TextBox
    \date Created: 2005-07-17
*/

#include <cpaf/win32/gui/entrybox.h>

void cpaf::win32::gui::EntryBox::create(const cpaf::gui::initializer::EntryBoxData &params)
{
    // create an entry box
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, true, TEXT("EDIT"), params.m_text.c_str(),
        WS_CHILD, WS_EX_CLIENTEDGE);
}
