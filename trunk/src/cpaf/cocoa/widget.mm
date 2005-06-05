/**
 * \file src/cpaf/cocoa/widget.mm
 * \brief Implementation of Cocoa widget
 * \date Created: 2005-04-29
 */

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/cocoa/utils.h>

// for delete_implementation_wrapper
#include <cpaf/private/factory.h>

using namespace cpaf::cocoa::utils;

void cpaf::cocoa::gui::Widget::create(const cpaf::gui::factory::WidgetData &params, id widget)
{
    cpaf::gui::Widget *parent;

    //! \todo m_show, m_activate, m_enable
    //! \todo m_min_size, m_max_size

    m_view = widget;    
    parent = params.m_parent;

    if (parent)
    {
        //! \todo Check if the parent is a window or so
        [[(id)parent->get_handle() contentView] addSubview:m_view];
        if (params.m_default_position)
            set_position(cpaf::Point(0.0, 0.0));
        else
            set_position(params.m_pos);

        if (params.m_default_size)
            set_size(cpaf::Size(50.0, 50.0));
        else
            set_size(params.m_size);
    }
    
    // The widget shouldn't move when we resize the window
    [m_view setAutoresizingMask:NSViewMinYMargin];
}

cpaf::cocoa::gui::Widget::~Widget()
{
    //! \todo release the widget
    // delete our wrapper object safely
    cpaf::gui::factory::delete_implementation_wrapper(this);
}

void cpaf::cocoa::gui::Widget::set_size(const cpaf::Size& s)
{
    NSRect f = [m_view frame];
    f.size.width = s.width;
    f.origin.y += f.size.height - s.height;
    f.size.height = s.height;
    [m_view setFrame:f];
}

void cpaf::cocoa::gui::Widget::set_position(const cpaf::Point& s)
{
    NSRect f = [m_view frame];
    f.origin.x = s.x;
    f.origin.y = [[m_view superview] frame].size.height - s.y - f.size.height;
    [m_view setFrame:f];
}

cpaf::Size cpaf::cocoa::gui::Widget::get_size()
{
    return cpaf::Size();
}

void cpaf::cocoa::gui::Widget::enable(bool e)
{
}

void cpaf::cocoa::gui::Widget::show(bool show, bool activate)
{
}

bool cpaf::cocoa::gui::Widget::is_enabled()
{
    return false;
}

bool cpaf::cocoa::gui::Widget::is_shown()
{
    return false;
}
