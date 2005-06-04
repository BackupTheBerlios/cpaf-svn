/**
 * \file src/cpaf/cocoa/window.mm
 * \brief Implementation of Cocoa window
 * \date 2005-04-29
 */

#include <cpaf/cocoa/gui/window.h>
#include <cpaf/cocoa/utils.h>

using namespace cpaf::cocoa::utils;

cpaf::cocoa::gui::Window::Window()
{
}

void cpaf::cocoa::gui::Window::create(const cpaf::gui::factory::WindowData &params)
{
    double x = params.m_pos.x, y = params.m_pos.y;
    double w = params.m_size.width, h = params.m_size.height;

    m_window = [[NSWindow alloc] initWithContentRect:NSMakeRect(x, y, w, h)
        styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask)
        backing:NSBackingStoreBuffered defer:YES];
    [m_window setReleasedWhenClosed:NO];

    if (params.m_use_client_size)
        set_client_size(params.m_client_size);
    else if (params.m_default_size)
        set_size(cpaf::Size(400.0, 300.0));
    else
        set_size(params.m_size);

    if (params.m_default_position)
        set_position(cpaf::Point(0.0, 0.0));
    else
        set_position(params.m_pos);

    set_min_size(params.m_min_size);
    set_max_size(params.m_max_size);

    set_title(params.m_title);

    //! \todo params.m_parent, params.m_enable

    show(params.m_show, params.m_activate);
}

void cpaf::cocoa::gui::Window::set_size(const cpaf::Size &s)
{
    NSRect f = [m_window frame];
    f.size.width = s.width;
    f.size.height = s.height;
    [m_window setFrame:f display:YES];
}

void cpaf::cocoa::gui::Window::set_min_size(const cpaf::Size &s)
{
    [m_window setMinSize:NSMakeSize(s.width, s.height)];
}

void cpaf::cocoa::gui::Window::set_max_size(const cpaf::Size &s)
{
    // FLT_MAX means "no limit"
    [m_window setMaxSize:NSMakeSize(s.width?s.width:FLT_MAX, s.height?s.height:FLT_MAX)];
}

void cpaf::cocoa::gui::Window::set_position(const cpaf::Point &p)
{
    NSRect f = [m_window frame];
    f.origin = convert_point(p);
    [m_window setFrame:f display:YES];
}

cpaf::Size cpaf::cocoa::gui::Window::get_size()
{
    NSRect f = [m_window frame];
    return cpaf::Size(f.size.width, f.size.height);
}

cpaf::Size cpaf::cocoa::gui::Window::get_min_size()
{
    NSSize size = [m_window minSize];
    return cpaf::Size(size.width, size.height);
}

cpaf::Size cpaf::cocoa::gui::Window::get_max_size()
{
    NSSize size = [m_window maxSize];
    return cpaf::Size(size.width, size.height);
}

cpaf::Point cpaf::cocoa::gui::Window::get_position()
{
    NSRect f = [m_window frame];
    return convert_point(f.origin);
}

void cpaf::cocoa::gui::Window::show(bool show, bool activate)
{
    if (show)
        if (activate)
            [m_window makeKeyAndOrderFront:nil];
        else
            [m_window orderFront:nil]; // is this correct behaviour?
    else
        [m_window close];
}

void cpaf::cocoa::gui::Window::set_title(const std::string &t)
{
    [m_window setTitle:[NSString stringWithUTF8String:t.c_str()]];
}

std::string cpaf::cocoa::gui::Window::get_title()
{
    return [[m_window title] UTF8String];
}

void cpaf::cocoa::gui::Window::set_client_size(const cpaf::Size &s)
{
    NSRect cf = [[m_window contentView] frame];
    NSRect wf = [m_window frame];
    
    // we have to do some math here because [[m_window contentView] setFrame:] doesn't resize the window

    NSSize delta = NSMakeSize(wf.size.width - cf.size.width, wf.size.height - cf.size.height);
    NSSize newSize = NSMakeSize(delta.width + s.width, delta.height + s.height);
    
    wf.origin.y += wf.size.height - newSize.height;
    wf.size.width = newSize.width;
    wf.size.height = newSize.height;
    
    [m_window setFrame:wf display:YES];
}

cpaf::Size cpaf::cocoa::gui::Window::get_client_size()
{
    return cpaf::Size(); //! \todo
}

cpaf::Point cpaf::cocoa::gui::Window::get_client_position()
{
    return cpaf::Point(); //! \todo
}
