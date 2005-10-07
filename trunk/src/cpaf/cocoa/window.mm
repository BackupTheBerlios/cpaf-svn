/**
 * \file src/cpaf/cocoa/window.mm
 * \brief Implementation of Cocoa window
 * \date Created: 2005-04-29
 */

#include <cpaf/cocoa/gui/window.h>
#include <cpaf/cocoa/utils.h>
#include <cpaf/gui/widget.h>

using namespace cpaf::cocoa::utils;

CPAF_COCOA_INTERFACE(Window)
CPAF_COCOA_IMPLEMENTATION(Window)

void cpaf::cocoa::gui::Window::create(const cpaf::gui::initializer::WindowData &params)
{
	m_wrapper = params.get_wrapper();


    m_object = [[CpafWindow alloc] initWithContentRect:NSMakeRect(0.0, 0.0, 0.0, 0.0)
        styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask)
        backing:NSBackingStoreBuffered defer:YES];
    [m_object setReleasedWhenClosed:NO];

    if ([m_object respondsToSelector:@selector(setCpafWidget:)])
        [m_object setCpafWidget:this];

    set_client_size(params.get_client_size());
    
    if (!params.default_position())
        set_position(params.get_position());
    //! \todo else: estimate a good default position

    set_min_size(params.get_min_size());
    set_max_size(params.get_max_size());

    set_title(params.get_title());

    //! \todo params.m_parent, params.m_enable

    show(params.get_show(), params.get_activate());

    send_event(cpaf::event::WIDGET_CREATE);
}

void cpaf::cocoa::gui::Window::set_size(const cpaf::Size &s)
{
    NSRect f = [m_object frame];
    f.size.width = s.width;
    f.size.height = s.height;
    [m_object setFrame:f display:YES];
}

void cpaf::cocoa::gui::Window::set_min_size(const cpaf::Size &s)
{
    [m_object setMinSize:NSMakeSize(s.width, s.height)];
}

void cpaf::cocoa::gui::Window::set_max_size(const cpaf::Size &s)
{
    // FLT_MAX means "no limit"
    [m_object setMaxSize:NSMakeSize(s.width?s.width:FLT_MAX, s.height?s.height:FLT_MAX)];
}

void cpaf::cocoa::gui::Window::set_position(const cpaf::Point &p)
{
    NSRect f = [m_object frame];
    f.origin = convert_point(p);
    [m_object setFrame:f display:YES];
}

cpaf::Size cpaf::cocoa::gui::Window::get_size() const
{
    NSRect f = [m_object frame];
    return cpaf::Size(f.size.width, f.size.height);
}

cpaf::Size cpaf::cocoa::gui::Window::get_min_size() const
{
    NSSize size = [m_object minSize];
    return cpaf::Size(size.width, size.height);
}

cpaf::Size cpaf::cocoa::gui::Window::get_max_size() const
{
    NSSize size = [m_object maxSize];
    return cpaf::Size(size.width, size.height);
}

cpaf::Point cpaf::cocoa::gui::Window::get_position() const
{
    NSRect f = [m_object frame];
    return convert_point(f.origin);
}

void cpaf::cocoa::gui::Window::show(bool show, bool activate)
{
    if (show)
        if (activate)
            [m_object makeKeyAndOrderFront:nil];
        else
            [m_object orderFront:nil]; // is this correct behaviour?
    else
        [m_object close];
}

void cpaf::cocoa::gui::Window::set_title(const std::string &t)
{
    [m_object setTitle:[NSString stringWithUTF8String:t.c_str()]];
}

std::string cpaf::cocoa::gui::Window::get_title()
{
    return [[m_object title] UTF8String];
}

void cpaf::cocoa::gui::Window::set_client_size(const cpaf::Size &s)
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

cpaf::Size cpaf::cocoa::gui::Window::get_client_size()
{
    return cpaf::Size(); //! \todo
}

cpaf::Point cpaf::cocoa::gui::Window::get_client_position()
{
    return cpaf::Point(); //! \todo
}
