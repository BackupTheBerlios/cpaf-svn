/**
 * \file src/cpaf/cocoa/textbox.mm
 * \brief Implementation of cpaf::cocoa::gui::TextBox
 * \date Created: 2005-07-08
 */

#include <cpaf/cocoa/gui/textbox.h>
#include <cpaf/exception.h>

//! \todo Use TextView instead of TextField
//CPAF_COCOA_INTERFACE(TextView)
//CPAF_COCOA_IMPLEMENTATION(TextView)
CPAF_COCOA_INTERFACE(TextField)

void cpaf::cocoa::gui::TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
	if( !params.m_parent )
		throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);
		
    cpaf::cocoa::gui::TextWidget::create(params, [[CpafTextField alloc] init]);
    [[m_object cell] setScrollable:YES];
    
    send_event(cpaf::event::WIDGET_CREATE);
}
