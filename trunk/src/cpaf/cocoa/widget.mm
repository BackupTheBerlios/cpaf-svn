/**
 * \file src/cpaf/cocoa/widget.mm
 * \brief Implementation of Cocoa widget
 * \date 2005-04-29
 */

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/cocoa/utils.h>

// for delete_implementation_wrapper
#include <cpaf/private/factory.h>

using namespace cpaf::cocoa::utils;

//cpaf::cocoa::gui::Widget::Widget(cpaf::api::gui::Widget *parent, id widget)
cpaf::cocoa::gui::Widget::Widget(const cpaf::gui::factory::WidgetData &params, id widget)
    : m_view(widget)
{
    cpaf::gui::Widget *parent = params.m_parent;
    if (parent)
    {
        //! \todo Check if the parent is a window or so
        [[(id)parent->get_handle() contentView] addSubview:m_view];
        set_position(cpaf::Point(0, 0));
    }
    
    // The widget shouldn't move when we resize the window
    [m_view setAutoresizingMask:NSViewMinYMargin];
}

cpaf::cocoa::gui::Widget::~Widget()
{
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
