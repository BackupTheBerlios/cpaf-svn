/**
 * \file src/cpaf/cocoa/widget.mm
 * \brief Implementation of Cocoa widget
 * \date Created: 2005-04-29
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

// So we don't get compiler warnings
@interface NSObject (CpafObject)
- (void)setCpafWidget:(cpaf::cocoa::gui::Widget *)widget;
- (cpaf::cocoa::gui::Widget *)cpafWidget;
@end


void cpaf::cocoa::gui::Widget::create(const cpaf::gui::initializer::WidgetData &params, id widget)
{
    m_wrapper = params.get_wrapper();

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

void cpaf::cocoa::gui::Widget::send_event(cpaf::event::event_id event_id) // cocoa specific
{
    cpaf::event::Event event(event_id, m_wrapper.lock()->get_id());
    cpaf::event::get_manager().send_event(event);
}

void cpaf::cocoa::gui::Widget::destroy()
{
    if (m_object)
    {
        NSArray *subviews = nil;
        
        // Send the destroy-event
        send_event(cpaf::event::WIDGET_DESTROY);

        if ([m_object isKindOfClass:[NSView class]])
            subviews = [m_object subviews];
        if ([m_object isKindOfClass:[NSWindow class]])
            subviews = [[m_object contentView] subviews];

        // Release the children
        if (subviews)
        {
            NSEnumerator *e = [subviews objectEnumerator];
            NSView *view;
            
            // Loop through the children
            while ((view = [e nextObject]) != nil)
            {
                cpaf::cocoa::gui::Widget *widget;
                
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

cpaf::cocoa::gui::Widget::~Widget()
{
    // delete our wrapper
    //delete m_wrapper;
}

void cpaf::cocoa::gui::Widget::set_size(const cpaf::Size& s)
{
    NSRect f = [m_object frame];
    f.size.width = s.width;
    f.origin.y += f.size.height - s.height;
    f.size.height = s.height;
    [m_object setFrame:f];
}

void cpaf::cocoa::gui::Widget::set_min_size(const cpaf::Size& size)
{
    m_min_size = size;
}

void cpaf::cocoa::gui::Widget::set_max_size(const cpaf::Size& size)
{
    m_max_size = size;
}

void cpaf::cocoa::gui::Widget::set_natural_size(const cpaf::Size& size)
{
    m_natural_size = size;
}

void cpaf::cocoa::gui::Widget::set_position(const cpaf::Point& s)
{
    NSRect f = [m_object frame];
    f.origin.x = s.x;
    f.origin.y = [[m_object superview] frame].size.height - s.y - f.size.height;
    [m_object setFrame:f];
}

cpaf::Size cpaf::cocoa::gui::Widget::get_size() const
{
    //! \todo
    NSLog(@"TODO: Widget::get_size()");
    return cpaf::Size();
}

cpaf::Size cpaf::cocoa::gui::Widget::get_min_size() const
{
    return m_min_size;
}

cpaf::Size cpaf::cocoa::gui::Widget::get_max_size() const
{
    return m_max_size;
}

cpaf::Size cpaf::cocoa::gui::Widget::get_natural_size() const
{
    return m_natural_size;
}

cpaf::Point cpaf::cocoa::gui::Widget::get_position() const
{
    //! \todo
    NSLog(@"TODO: Widget::get_position()");
    return cpaf::Point();
}

void cpaf::cocoa::gui::Widget::set_rect(const cpaf::Rect& rect)
{
    //! \todo use setFrame: directly and remove the debug message
    NSLog(@"set rect to %@: %f %f %f %f", [m_object description], rect.position.x, rect.position.y, rect.size.width, rect.size.height);
    set_position(rect.position);
    set_size(rect.size);
}

cpaf::Rect cpaf::cocoa::gui::Widget::get_rect() const
{
    //! \todo
    return cpaf::Rect();
}

void cpaf::cocoa::gui::Widget::enable(bool e)
{
    //! \todo
}

void cpaf::cocoa::gui::Widget::show(bool show, bool activate)
{
    //! \todo
}

bool cpaf::cocoa::gui::Widget::is_enabled() const
{
    return false; //! \todo
}

bool cpaf::cocoa::gui::Widget::is_shown() const
{
    return false; //! \todo
}

boost::shared_ptr<cpaf::gui::Panel> cpaf::cocoa::gui::Widget::get_parent() const
{
    id parent = [m_object superview];

    if (parent && [parent respondsToSelector:@selector(cpafWidget)])
    {
        cpaf::cocoa::gui::Widget *w = [parent cpafWidget];
        return w->get_wrapper<cpaf::gui::Panel>();
    }

    //! \todo What should I do if the parent doesn't'respond to cpafWidget ?
    return boost::shared_ptr<cpaf::gui::Panel>();
}
boost::shared_ptr<cpaf::gui::Window> cpaf::cocoa::gui::Widget::get_parent_window() const
{
    NSWindow *win = [m_object window];

    if ([win respondsToSelector:@selector(cpafWidget)])
    {
        cpaf::cocoa::gui::Widget *w = [win cpafWidget];
        return w->get_wrapper<cpaf::gui::Window>();
    }

    //! \todo What should I do if the parent doesn't'respond to cpafWidget ?
    return boost::shared_ptr<cpaf::gui::Window>();
}
