/*!
    \file src/cpaf/win32/button.cpp
    \brief Implementation of cpaf::win32::gui::Button
    \date Created: 2005-04-05
*/

#include <cpaf/win32/gui/button.h>
#include <cpaf/gui/widget.h>
#include <cpaf/win32/exception.h>
#include <cpaf/gui/button.h>

void cpaf::win32::gui::Button::create(const cpaf::gui::factory::ButtonData &params)
{
    // this needs to go before the wnd_proc_replaced bit or I get an access violation from VC
    // for what ever stupid reason if the parent is null
    HWND hparent;
    cpaf::gui::Widget *parent = params.m_parent;
    if( parent )
        hparent = (HWND)parent->get_handle();
    else
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    CreationInfo info(this);
    int x = params.m_pos.x, y = params.m_pos.y;
    int w = params.m_size.width, h = params.m_size.height;

    if( params.m_default_position )
        x = CW_USEDEFAULT;
    if( params.m_default_size )
        w = CW_USEDEFAULT;

    {
        CreationHook hook; // hook WM_CREATE for initialization stuff

        m_hwnd = ::CreateWindowEx(0, TEXT("BUTTON"), params.m_label.c_str(), WS_CHILD | BS_PUSHBUTTON,
            x, y, w, h, hparent, NULL, ::GetModuleHandle(NULL),
            &info);
    }

    // the rest of the creation
    cpaf::win32::gui::Widget::create(params);
}

void cpaf::win32::gui::Button::set_label(const std::string &label)
{
    set_window_text(label);
}

std::string cpaf::win32::gui::Button::get_label()
{
    return get_window_text();
}
