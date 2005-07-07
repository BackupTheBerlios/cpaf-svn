/*!
    \file src/cpaf/win32/textbox.cpp
    \brief Implementation of cpaf::win32::gui::TextBox
    \date Created: 2005-07-07
*/

#include <cpaf/win32/gui/textbox.h>
#include <cpaf/win32/exception.h>

void cpaf::win32::gui::TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
    HWND hparent;
    cpaf::gui::Widget *parent = params.m_parent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    m_wrapper = params.m_wrapper;
    m_id = m_wrapper->get_id();

    CreationInfo info(this);
    int x = params.m_pos.x, y = params.m_pos.y;
    int w = params.m_size.width, h = params.m_size.height;

    if( params.m_default_position )
        x = CW_USEDEFAULT;
    if( params.m_default_size )
        w = CW_USEDEFAULT;

    {
        CreationHook hook; // hook WM_CREATE for initialization stuff

        m_hwnd = ::CreateWindowEx(0, TEXT("EDIT"), params.m_text.c_str(), WS_CHILD | WS_BORDER,
            x, y, w, h, hparent, NULL, ::GetModuleHandle(NULL),
            &info);
    }

    // the rest of the creation
    cpaf::win32::gui::Widget::create(params);
}

void cpaf::win32::gui::TextBox::set_text(const std::string &s)
{
    set_window_text(s);
}

std::string cpaf::win32::gui::TextBox::get_text()
{
    return get_window_text();
}
