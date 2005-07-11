/*!
    \file src/cpaf/win32/textbox.cpp
    \brief Implementation of cpaf::win32::gui::TextBox
    \date Created: 2005-07-07
*/

#include <cpaf/win32/gui/textbox.h>
#include <cpaf/win32/exception.h>

void cpaf::win32::gui::TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
    // create a textbox
    cpaf::win32::gui::Widget::create(CreationInfo(this), params, true, TEXT("EDIT"), params.m_text.c_str(),
        WS_CHILD | WS_BORDER);
}

void cpaf::win32::gui::TextBox::set_text(const std::string &s)
{
    set_window_text(s);
}

std::string cpaf::win32::gui::TextBox::get_text()
{
    return get_window_text();
}
