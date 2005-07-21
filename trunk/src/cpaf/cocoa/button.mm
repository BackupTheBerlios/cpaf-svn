/**
 * \file src/cpaf/cocoa/button.mm
 * \brief Implementation of Cocoa button
 * \date Created: 2005-04-29
 */

#include <cpaf/cocoa/gui/button.h>
#include <cpaf/exception.h>
#include <cpaf/gui/widget.h>

CPAF_COCOA_INTERFACE(Button)
CPAF_COCOA_IMPLEMENTATION(Button)

@interface CpafButton (Cpaf)
- (void)cpafButtonClickEvent;
@end

@implementation CpafButton (Cpaf)
- (void)cpafButtonClickEvent
{
    [self cpafSendEvent:cpaf::event::BUTTON_CLICK];
}
@end

void cpaf::cocoa::gui::Button::create(const cpaf::gui::initializer::ButtonData &params)
{
	if( !params.m_parent )
		throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);
		
    cpaf::cocoa::gui::Widget::create(params, [[CpafButton alloc] init]);
    
    [m_object setButtonType:NSToggleButton];
    [(NSButton*)m_object setBezelStyle:NSRegularSquareBezelStyle];
    
    // Click event
    [m_object setTarget:m_object];
    [m_object setAction:@selector(cpafButtonClickEvent)];
    
    set_label(params.m_label);
    
    send_event(cpaf::event::WIDGET_CREATE);
}

void cpaf::cocoa::gui::Button::set_label(const std::string &label)
{
    [m_object setTitle:[NSString stringWithUTF8String:label.c_str()]];
}

std::string cpaf::cocoa::gui::Button::get_label()
{
    return [[m_object title] UTF8String];
}
