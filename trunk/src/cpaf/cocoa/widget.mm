/*!
    \file src/cpaf/cocoa/widget.mm
    \brief Implementation of Cocoa widget
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
*/

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/gui/widget.h>
#include <cpaf/gui/panel.h>
#include <cpaf/gui/window.h>
#include <cpaf/cocoa/utils.h>
#include <cpaf/event/event.h>

// for delete_implementation_wrapper
#include <cpaf/private/factory.h>

using namespace cpaf::cocoa::utils;
using namespace cpaf::cocoa::gui;

// So we don't get compiler warnings
@interface NSObject (CpafObject)
- (void)setCpafWidget:(Widget *)widget;
- (Widget *)cpafWidget;
@end


void Widget::create(const cpaf::gui::initializer::WidgetData &params, id widget)
{
    m_wrapper = params.get_wrapper();
    m_wrapper_id = params.get_wrapper()->get_id();

    m_object = widget;
    
    if ([widget respondsToSelector:@selector(setCpafWidget:)])
        [widget setCpafWidget:this];        

    //! \todo m_show, m_activate, m_enable

    m_min_size = params.get_min_size();
    m_max_size = params.get_max_size();
    m_natural_size = params.get_natural_size();

    //! \todo What's if we're adding the widget later to a container?
    if (params.get_parent())
    {
        id parent = (id)params.get_parent()->get_handle();
        if ([parent isKindOfClass:[NSWindow class]])
            [parent setContentView:m_object];
        else if ([parent isKindOfClass:[NSView class]])
            [parent addSubview:m_object];
        //! \todo else?
        //! \todo do_layout?
    }

    // The widget shouldn't move when we resize the window
    //! \todo Remove this?
    // [m_object setAutoresizingMask:NSViewMinYMargin];

    // Don't send a WIDGET_CREATE-event here, every subclass has to do that
}

void Widget::send_event(cpaf::event::event_id event_id) // cocoa specific
{
    cpaf::event::Event event(event_id, m_wrapper.lock()->get_id());
    cpaf::event::get_manager().send_event(event);
}

void Widget::destroy()
{
    if (m_object)
    {
        NSArray *subviews = nil;
        
        // Send the destroy-event
        send_event(cpaf::event::WIDGET_DESTROY);

        if ([m_object isKindOfClass:[NSView class]])
            subviews = [m_object subviews];
        if ([m_object isKindOfClass:[NSWindow class]])
            subviews = [NSArray arrayWithObject:[m_object contentView]];

        // Release the children
        if (subviews)
        {
            NSEnumerator *e = [subviews objectEnumerator];
            NSView *view;
            
            // Loop through the children
            while ((view = [e nextObject]) != nil)
            {
                Widget *widget;
                
                // Is there an implementation object available? 
                if ([view respondsToSelector:@selector(cpafWidget)])
                {
                    widget = [view cpafWidget];
                    widget->destroy(); // Destroy it
                }
            }
        }

        if ([m_object isKindOfClass:[NSView class]] && [m_object superview])
            [m_object removeFromSuperview];

        [m_object release];
        m_object = nil;
    }

    // remove the {ID, Widget} pair from the widget id map
    cpaf::gui::disassociate_widget_id(m_wrapper_id);
}

Widget::~Widget()
{
    // delete our wrapper
    //delete m_wrapper;
}

void Widget::set_size(const cpaf::Size& s)
{
    NSRect f = [m_object frame];
    f.size.width = s.width;
    f.origin.y += f.size.height - s.height;
    f.size.height = s.height;
    [m_object setFrame:f];
}

void Widget::set_min_size(const cpaf::Size& size)
{
    m_min_size = size;
}

void Widget::set_max_size(const cpaf::Size& size)
{
    m_max_size = size;
}

void Widget::set_natural_size(const cpaf::Size& size)
{
    m_natural_size = size;
}

void Widget::set_position(const cpaf::Point& s)
{
    NSRect f = [m_object frame];
    f.origin.x = s.x;
    f.origin.y = [[m_object superview] frame].size.height - s.y - f.size.height;
    [m_object setFrame:f];
}

cpaf::Size Widget::get_size() const
{
    //! \todo
    NSLog(@"TODO: Widget::get_size()");
    return cpaf::Size();
}

cpaf::Size Widget::get_min_size() const
{
    return m_min_size;
}

cpaf::Size Widget::get_max_size() const
{
    return m_max_size;
}

cpaf::Size Widget::get_natural_size() const
{
    return m_natural_size;
}

cpaf::Point Widget::get_position() const
{
    //! \todo
    NSLog(@"TODO: Widget::get_position()");
    return cpaf::Point();
}

void Widget::set_rect(const cpaf::Rect& rect)
{
    NSRect f = [m_object frame];

    /*!
        \note I am rounding the coordinates, because Mac OS X up to 10.4 has rendering bugs with
              not rounded coordinates. We may need to change that behaviour when Mac OS X 10.5 is
              out, which may support UI-scaling.

        \todo There are other places where we have to round the coordinates
    */

    f.origin.x = rintf(rect.position.x);
    f.origin.y = [[m_object superview] frame].size.height - rintf(rect.position.y) - rintf(rect.size.height);
    f.size.width = rintf(rect.size.width);
    f.size.height = rintf(rect.size.height);

    [m_object setFrame:f];
}

cpaf::Rect Widget::get_rect() const
{
    //! \todo
    NSLog(@"TODO: Widget::get_rect()");
    return cpaf::Rect();
}

void Widget::enable(bool e)
{
    //! \todo
    NSLog(@"TODO: Widget::enable()");
}

void Widget::show(bool show, bool activate)
{
    //! \todo
    NSLog(@"TODO: Widget::show()");
}

bool Widget::is_enabled() const
{
    NSLog(@"TODO: Widget::is_enabled()");
    return false; //! \todo
}

bool Widget::is_shown() const
{
    NSLog(@"TODO: Widget::is_shown()");
    return false; //! \todo
}

boost::shared_ptr<cpaf::gui::Panel> Widget::get_parent() const
{
    id parent = [m_object superview];

    if (parent && [parent respondsToSelector:@selector(cpafWidget)])
    {
        Widget *w = [parent cpafWidget];
        return w->get_wrapper<cpaf::gui::Panel>();
    }

    //! \todo What should I do if the parent doesn't'respond to cpafWidget ?
    return boost::shared_ptr<cpaf::gui::Panel>();
}

boost::shared_ptr<cpaf::gui::Window> Widget::get_parent_window() const
{
    NSWindow *win = [m_object window];

    if ([win respondsToSelector:@selector(cpafWidget)])
    {
        Widget *w = [win cpafWidget];
        return w->get_wrapper<cpaf::gui::Window>();
    }

    //! \todo What should I do if the parent doesn't'respond to cpafWidget ?
    return boost::shared_ptr<cpaf::gui::Window>();
}
