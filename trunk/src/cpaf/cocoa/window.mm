/**
 * \file src/cpaf/cocoa/window.mm
 * \brief Implementation of Cocoa window
 * \date 2005-04-29
 */

#include <cpaf/cocoa/gui/window.h>
#include <cpaf/cocoa/utils.h>

using namespace cpaf::cocoa::utils;

/*
    Please move all object construction related code into the empty create method below
*/

cpaf::cocoa::gui::Window::Window(const cpaf::gui::factory::WindowData &params)
    /*: m_window([[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 400, 300) styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask) backing:NSBackingStoreBuffered defer:YES])
{
    //! \todo Is there some default size?
    set_position(cpaf::Point(0, 0));
    set_title(params.m_title);
    //! \todo if (parent) { }
}*/

void cpaf::cocoa::gui::Window::create(const cpaf::gui::factory::WindowData &params)
{

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
    [m_window setMaxSize:NSMakeSize(s.width, s.height)];
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
    //! \todo show, activate
    [m_window makeKeyAndOrderFront:nil];
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
    set_size(s);
}

cpaf::Size cpaf::cocoa::gui::Window::get_client_size()
{
    return cpaf::Size();
}

cpaf::Point cpaf::cocoa::gui::Window::get_client_position()
{
    return cpaf::Point();
}
