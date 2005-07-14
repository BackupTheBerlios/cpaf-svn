/**
 * \file src/cpaf/cocoa/entrybox.mm
 * \brief Implementation of cpaf::cocoa::gui::EntryBox
 * \date Created: 2005-07-14
 */

#include <cpaf/cocoa/gui/entrybox.h>
#include <cpaf/exception.h>

CPAF_COCOA_INTERFACE(TextField)
CPAF_COCOA_IMPLEMENTATION(TextField)

void cpaf::cocoa::gui::EntryBox::create(const cpaf::gui::initializer::EntryBoxData &params)
{
	if( !params.m_parent )
		throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);
		
    cpaf::cocoa::gui::TextWidget::create(params, [[CpafTextField alloc] init]);
    [[m_object cell] setScrollable:YES];
    
    send_event(cpaf::event::WIDGET_CREATE);
}
