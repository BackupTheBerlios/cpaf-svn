/*!
    \file src/cpaf/cocoa/window.mm
    \brief Implementation of Cocoa window
    \date Created: 2005-04-29
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

    Copyright (C) 2005 Thomas Steinacher
    http://www.eggdrop.ch/
    tom (at) eggdrop [dot] ch
*/

#include <cpaf/cocoa/gui/window.h>
#include <cpaf/cocoa/gui/panel.h>
#include <cpaf/cocoa/utils.h>
#include <cpaf/gui/widget.h>

using namespace cpaf::cocoa::utils;
using namespace cpaf::cocoa::gui;

CPAF_COCOA_INTERFACE(Window)
CPAF_COCOA_IMPLEMENTATION(Window)

void Window::create(const cpaf::gui::initializer::WindowData &params)
{
    m_wrapper = params.get_wrapper();

    m_object = [[CpafWindow alloc] initWithContentRect:NSMakeRect(0.0, 0.0, 0.0, 0.0)
        styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask)
        backing:NSBackingStoreBuffered defer:YES];
    [m_object setReleasedWhenClosed:NO];
    [m_object setDelegate:m_object];

    if ([m_object respondsToSelector:@selector(setCpafWidget:)])
        [m_object setCpafWidget:this];

    //! \todo Is there no default_size() ?
    if (params.get_client_size().width > 0 && params.get_client_size().height > 0)
      set_client_size(params.get_client_size());
    else
      set_client_size(cpaf::Size(400.0, 300.0)); //! \todo What's'a good default size?
    
    if (!params.default_position())
        set_position(params.get_position());
    //! \todo else: estimate a good default position

    set_min_size(params.get_min_size());
    set_max_size(params.get_max_size());

    set_title(params.get_title());

    if (params.get_content_panel())
        set_content_panel(params.get_content_panel()->get_impl());

    //! \todo params.m_parent, params.m_enable

    show(params.get_show(), params.get_activate());

    send_event(cpaf::event::WIDGET_CREATE);
}

void Window::set_size(const cpaf::Size &s)
{
    NSRect f = [m_object frame];
    f.size.width = s.width;
    f.size.height = s.height;
    [m_object setFrame:f display:YES];
}

void Window::set_min_size(const cpaf::Size &s)
{
    [m_object setMinSize:NSMakeSize(s.width, s.height)];
}

void Window::set_max_size(const cpaf::Size &s)
{
    // FLT_MAX means "no limit"
    [m_object setMaxSize:NSMakeSize(s.width?s.width:FLT_MAX, s.height?s.height:FLT_MAX)];
}

void Window::set_position(const cpaf::Point &p)
{
    NSRect f = [m_object frame];
    f.origin = convert_point(p);
    [m_object setFrame:f display:YES];
}

cpaf::Size Window::get_size() const
{
    NSRect f = [m_object frame];
    return cpaf::Size(f.size.width, f.size.height);
}

cpaf::Size Window::get_min_size() const
{
    NSSize size = [m_object minSize];
    return cpaf::Size(size.width, size.height);
}

cpaf::Size Window::get_max_size() const
{
    NSSize size = [m_object maxSize];
    return cpaf::Size(size.width, size.height);
}

cpaf::Point Window::get_position() const
{
    NSRect f = [m_object frame];
    return convert_point(f.origin);
}

void Window::enable(bool sensitive)
{
    //! \todo
    NSLog(@"TODO: Window::enable()");
}

bool Window::is_enabled() const
{
    //! \todo
    NSLog(@"TODO: Window::is_enabled()");
    return false;
}

bool Window::is_shown() const
{
    //! \todo
    NSLog(@"TODO: Window::is_shown()");
    return false;
}

void Window::show(bool show, bool activate)
{
    //! \todo That's only a temporary fix
    if (m_root_panel && show)
    {
        id view = (id)m_root_panel->get_handle();
        [view performSelector:@selector(cpafDoLayout)];
    }

    if (show)
        if (activate)
            [m_object makeKeyAndOrderFront:nil];
        else
            [m_object orderFront:nil]; // is this correct behaviour?
    else
        [m_object close];
}

void Window::set_title(const std::string &t)
{
    [m_object setTitle:[NSString stringWithUTF8String:t.c_str()]];
}

std::string Window::get_title()
{
    return [[m_object title] UTF8String];
}

void Window::set_client_size(const cpaf::Size &s)
{
    NSRect cf = [[m_object contentView] frame];
    NSRect wf = [m_object frame];
    
    // we have to do some math here because [[m_object contentView] setFrame:] doesn't resize the window

    NSSize delta = NSMakeSize(wf.size.width - cf.size.width, wf.size.height - cf.size.height);
    NSSize newSize = NSMakeSize(delta.width + s.width, delta.height + s.height);
    
    wf.origin.y += wf.size.height - newSize.height;
    wf.size.width = newSize.width;
    wf.size.height = newSize.height;
    
    [m_object setFrame:wf display:YES];
}

cpaf::Size Window::get_client_size()
{
    NSRect f = [[m_object contentView] frame];
    return cpaf::Size(f.size.width, f.size.height);
}

cpaf::Point Window::get_client_position()
{
    NSRect f = [[m_object contentView] frame];
    return convert_point(f.origin);
}

void Window::set_content_panel(cpaf::api::gui::Panel *p)
{
    //! \todo What's happening with the old panel?

    m_root_panel = dynamic_cast<Panel*>(p);
    id view = (id)m_root_panel->get_handle();
    [m_object setContentView:view];
    [view performSelector:@selector(cpafDoLayout)];
    m_root_panel->show(true, false);
}

boost::shared_ptr<cpaf::gui::Panel> Window::get_content_panel() const
{
    return m_root_panel->get_wrapper<cpaf::gui::Panel>();
}
