/**
 * \file src/cpaf/cocoa/entrybox.mm
 * \brief Implementation of cpaf::cocoa::gui::EntryBox
 * \date Created: 2005-07-14
 */

#include <cpaf/cocoa/gui/entrybox.h>
#include <cpaf/exception.h>

CPAF_COCOA_INTERFACE(TextField)
CPAF_COCOA_IMPLEMENTATION(TextField)

CPAF_COCOA_INTERFACE(SecureTextField)
CPAF_COCOA_IMPLEMENTATION(SecureTextField)

void cpaf::cocoa::gui::EntryBox::create(const cpaf::gui::initializer::EntryBoxData &params)
{
    id widget = nil;

    if( !params.m_parent )
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    if (params.m_in_password_mode)
        widget = [[CpafSecureTextField alloc] init];
    else
        widget = [[CpafTextField alloc] init];
    
    cpaf::cocoa::gui::TextWidget::create(params, widget);
    [[m_object cell] setScrollable:YES];
    [[m_object cell] setWraps:NO];

    send_event(cpaf::event::WIDGET_CREATE);
}

void cpaf::cocoa::gui::EntryBox::set_password_mode(bool mode)
{
    NSLog(@"todo");
}