/**
 * \file src/cpaf/cocoa/widget.mm
 * \brief Implementation of Cocoa widget
 * \date Created: 2005-04-29
 */

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/gui/widget.h>
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
	m_wrapper = params.m_wrapper;
    cpaf::gui::Widget *parent;
    
    if ([widget respondsToSelector:@selector(setCpafWidget:)])
        [widget setCpafWidget:this];        

    //! \todo m_show, m_activate, m_enable
    //! \todo m_min_size, m_max_size

    m_object = widget;    
    parent = params.m_parent;

    if (params.m_default_size)
        set_size(cpaf::Size(50.0, 50.0));
    else
        set_size(params.m_size);

    //! \todo What's if we're adding the widget later to a container?
    if (parent)
    {
        //! \todo Check if the parent is a window or so
        [[(id)parent->get_handle() contentView] addSubview:m_object];

        if (params.m_default_position)
            set_position(cpaf::Point(0.0, 0.0));
        else
            set_position(params.m_pos);
    }

    // The widget shouldn't move when we resize the window
    [m_object setAutoresizingMask:NSViewMinYMargin];

    // Don't send a WIDGET_CREATE-event here, every subclass has to do that
}

void cpaf::cocoa::gui::Widget::send_event(cpaf::event::event_id event_id) // cocoa specific
{
    cpaf::event::Event event(event_id, m_wrapper->get_id());
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
    cpaf::gui::disassociate_widget_id(m_wrapper->get_id());
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

void cpaf::cocoa::gui::Widget::set_position(const cpaf::Point& s)
{
    NSRect f = [m_object frame];
    f.origin.x = s.x;
    f.origin.y = [[m_object superview] frame].size.height - s.y - f.size.height;
    [m_object setFrame:f];
}

cpaf::Size cpaf::cocoa::gui::Widget::get_size()
{
    return cpaf::Size(); //! \todo
}

void cpaf::cocoa::gui::Widget::enable(bool e)
{
    //! \todo
}

void cpaf::cocoa::gui::Widget::show(bool show, bool activate)
{
    //! \todo
}

bool cpaf::cocoa::gui::Widget::is_enabled()
{
    return false; //! \todo
}

bool cpaf::cocoa::gui::Widget::is_shown()
{
    return false; //! \todo
}
