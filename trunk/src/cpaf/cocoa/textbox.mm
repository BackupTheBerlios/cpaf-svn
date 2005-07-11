/**
 * \file src/cpaf/cocoa/textbox.mm
 * \brief Implementation of cpaf::cocoa::gui::TextBox
 * \date Created: 2005-07-08
 */

#include <cpaf/cocoa/gui/textbox.h>
#include <cpaf/exception.h>

CPAF_COCOA_INTERFACE(TextField)
CPAF_COCOA_IMPLEMENTATION(TextField)

void cpaf::cocoa::gui::TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
	if( !params.m_parent )
		throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);
		
    cpaf::cocoa::gui::Widget::create(params, [[CpafTextField alloc] init]);
    [[m_object cell] setScrollable:YES];
    
    set_text(params.m_text);
    
    send_event(cpaf::event::WIDGET_CREATE);
}

void cpaf::cocoa::gui::TextBox::set_text(const std::string &s)
{
    [m_object setStringValue:[NSString stringWithUTF8String:s.c_str()]];
}

std::string cpaf::cocoa::gui::TextBox::get_text()
{
    return [[m_object stringValue] UTF8String];
}
