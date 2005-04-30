/**
 * \file src/cpaf/cocoa/widget.mm
 * \brief Implementation of Cocoa widget
 * \date 2005-04-29
 */

#include <cpaf/cocoa/gui/widget.h>

// for delete_implementation_wrapper
#include <cpaf/private/factory.h>

cpaf::cocoa::gui::Widget::Widget(id widget)
	: m_widget(widget)
{
}

cpaf::cocoa::gui::Widget::~Widget()
{
    // delete our wrapper object safely
    cpaf::gui::factory::delete_implementation_wrapper(this);
}

void cpaf::cocoa::gui::Widget::set_size(const cpaf::Size& s)
{
    NSRect f = [m_widget frame];
    f.size.width = s.width;
    f.size.height = s.height;
    [m_widget setFrame:f];
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
