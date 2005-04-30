/**
 * \file src/cpaf/cocoa/window.mm
 * \brief Implementation of Cocoa window
 * \date 2005-04-29
 */

#include <cpaf/cocoa/gui/window.h>
#include <cpaf/cocoa/utils.h>

using namespace cpaf::cocoa::utils;


cpaf::cocoa::gui::Window::Window(cpaf::api::gui::Window *parent)
    : Widget([[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 400, 300) styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask) backing:NSBackingStoreBuffered defer:YES])
{
    //! \todo if (parent) { }
}

void cpaf::cocoa::gui::Window::set_size(const cpaf::Size &s)
{
    NSRect f = [m_widget frame];
    f.size.width = s.width;
    f.size.height = s.height;
    [m_widget setFrame:f display:YES];
}

void cpaf::cocoa::gui::Window::set_min_size(const cpaf::Size &s)
{
	[m_widget setMinSize:NSMakeSize(s.width, s.height)];
}

void cpaf::cocoa::gui::Window::set_max_size(const cpaf::Size &s)
{
	[m_widget setMaxSize:NSMakeSize(s.width, s.height)];
}

void cpaf::cocoa::gui::Window::set_position(const cpaf::Point &p)
{
    NSRect f = [m_widget frame];
	f.origin = convert_point(p);
    [m_widget setFrame:f display:YES];
}

cpaf::Size cpaf::cocoa::gui::Window::get_size()
{
    NSRect f = [m_widget frame];
    return cpaf::Size(f.size.width, f.size.height);
}

cpaf::Size cpaf::cocoa::gui::Window::get_min_size()
{
	NSSize size = [m_widget minSize];
    return cpaf::Size(size.width, size.height);
}

cpaf::Size cpaf::cocoa::gui::Window::get_max_size()
{
	NSSize size = [m_widget maxSize];
    return cpaf::Size(size.width, size.height);
}

cpaf::Point cpaf::cocoa::gui::Window::get_position()
{
    NSRect f = [m_widget frame];
    return convert_point(f.origin);
}

void cpaf::cocoa::gui::Window::show(bool show, bool activate)
{
	//! \todo show, activate
	[m_widget makeKeyAndOrderFront:nil];
}

void cpaf::cocoa::gui::Window::set_title(const std::string &t)
{
	[m_widget setTitle:[NSString stringWithUTF8String:t.c_str()]];
}

std::string cpaf::cocoa::gui::Window::get_title()
{
    return [[m_widget title] UTF8String];
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
