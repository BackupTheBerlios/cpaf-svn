/*!
    \file src/cpaf/win32/win.cpp
    \brief Implementation of various things for the win32 port
    \date Created: 2005-04-07
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

#include <cpaf/win32/win.h>
#include <cpaf/win32/gui/widget.h>
#include <cpaf/win32/exception.h>
#include <cpaf/win32/msgnames.h>

using namespace cpaf::win32::gui;

namespace {
    //typedef std::map<HWND, Widget *> WidgetMap;
    //WidgetMap widget_map;
    unsigned int num_widgets = 0;
    WidgetDeletionStack widget_deletion_stack;
}

void cpaf::win32::gui::associate_hwnd(HWND h, cpaf::win32::gui::Widget *wnd)
{
    //widget_map[h] = wnd;

    // don't store NULL pointers because that throws off the num_widgets count
    // when they are removed
    if( wnd == 0 )
        return;

    //! \todo Throw if this fails
    if( ::SetProp(h, "cpaf::widget", wnd) )
        num_widgets++;
}

void cpaf::win32::gui::disassociate_hwnd(HWND h)
{
    //WidgetMap::iterator i = widget_map.find(h);

    //if( i != widget_map.end() )
        //widget_map.erase(i);

    ::RemoveProp(h, "cpaf::widget");

    // we do not throw if the hwnd was not found in the map because this function is called by
    // win32::gui::Widget dtor. Throwing dtors are bad and cause all sorts of trouble as I recently
    // discovered...
}

Widget *cpaf::win32::gui::get_widget_from_hwnd(HWND h)
{
    /*
    WidgetMap::iterator i = widget_map.find(h);
    if( i != widget_map.end() )
        return i->second;
    else
        return NULL;
    */
    return static_cast<Widget*>(::GetProp(h, "cpaf::widget"));
}

bool cpaf::win32::gui::has_widgets()
{
    //return widget_map.empty();
    return num_widgets != 0;
}

void cpaf::win32::gui::widget_deletion_stack_push(Widget *w)
{
    widget_deletion_stack.push(w);
}

void cpaf::win32::gui::widget_deletion_stack_pop()
{
    num_widgets--;

    // remove the libraries reference to the wrapper object
    cpaf::gui::disassociate_widget_id(widget_deletion_stack.top()->get_id());

    widget_deletion_stack.pop();
}

bool cpaf::win32::gui::widget_deletion_stack_waiting()
{
    return !widget_deletion_stack.empty();
}

CreationInfo::CreationInfo(Widget *w)
    : wnd(w)
{ }

LRESULT CALLBACK cpaf::win32::gui::widget_wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    //DBG_MSG_2("cpaf::win32::gui::widget_wndproc: %s", cpaf::win32::MessageTypeNames[msg]);
    Widget *wnd = get_widget_from_hwnd(hwnd);

    // once we can find our widget class, use it to process messages
    if( wnd )
        return wnd->process_message(hwnd, msg, w_param, l_param);

    DebugReport() << "widget_wndproc failed to proceess a message: " << cpaf::win32::MessageTypeNames[msg];

    return ::DefWindowProc(hwnd, msg, w_param, l_param);
}


/********************

  CreationHook implementation

********************/

namespace {
    HHOOK m_hook; // hook procedure handle
}

CreationHook::CreationHook()
{
    // create the hook
    m_hook = ::SetWindowsHookEx(WH_CBT, CreationHook::hook_proc, NULL, ::GetCurrentThreadId());

    if( !m_hook )
        throw cpaf::win32::Exception(cpaf::win32::Exception::HOOK, ::GetLastError(), __LINE__, __FILE__);
}

CreationHook::~CreationHook()
{
    // unhook
    if( m_hook )
        ::UnhookWindowsHookEx(m_hook);
}

LRESULT CALLBACK cpaf::win32::gui::CreationHook::hook_proc(int code, WPARAM w_param, LPARAM l_param)
{
    if( code == HCBT_CREATEWND )
    {
        HWND hwnd = (HWND)w_param;
        LPCREATESTRUCT create = ((LPCBT_CREATEWND)l_param)->lpcs;
        CreationInfo *info = (CreationInfo*)create->lpCreateParams;

        if( info )
        {
            associate_hwnd(hwnd, info->wnd);

            // subclass the window
            info->wnd->set_old_proc((WNDPROC)(LONG_PTR)::SetWindowLongPtr(hwnd, GWL_WNDPROC, (LONG_PTR)widget_wndproc));

            // unhook now
            if( !::UnhookWindowsHookEx(m_hook) )
                throw cpaf::win32::Exception(cpaf::win32::Exception::UNHOOK, ::GetLastError(), __LINE__, __FILE__);
            else
                m_hook = 0;

            return 0;
        }
    }

    return ::CallNextHookEx(m_hook, code, w_param, l_param);
}
