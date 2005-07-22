/**
 * \file src/cpaf/cocoa/textbox.mm
 * \brief Implementation of cpaf::cocoa::gui::TextBox
 * \date Created: 2005-07-08
 */

#include <cpaf/cocoa/gui/textbox.h>
#include <cpaf/exception.h>

CPAF_COCOA_INTERFACE(ScrollView)
CPAF_COCOA_IMPLEMENTATION(ScrollView)

void cpaf::cocoa::gui::TextBox::create(const cpaf::gui::initializer::TextBoxData &params)
{
    NSSize size;

    if( !params.m_parent )
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    // Initialize the NSTextView, before calling TextWidget::create() (because this will call set_text())
    m_textview = [[NSTextView alloc] init];

    cpaf::cocoa::gui::TextWidget::create(params, [[CpafScrollView alloc] init]);

    // Set up the NSScrollView
    [m_object setHasVerticalScroller:YES];
    [m_object setAutohidesScrollers:YES];
    [m_object setBorderType:NSBezelBorder];

    // Get the size of the NSScrollView and resize the NSTextView
    size = [m_object frame].size;
    [m_textview setFrame:NSMakeRect(0.0, 0.0, size.width, size.height)];

    // Autosize, so the NSTextView is always as big as the NSScrollView
    [m_textview setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];

    [m_textview setRichText:NO];
    [m_textview setUsesFontPanel:NO]; // Don't allow changing the font

    // Add the NSTextView to the NSScrollView
    [m_object setDocumentView:m_textview];
    [m_textview release];

    send_event(cpaf::event::WIDGET_CREATE);
}

void cpaf::cocoa::gui::TextBox::set_text(const std::string &s)
{
    [m_textview setString:[NSString stringWithUTF8String:s.c_str()]];
}

std::string cpaf::cocoa::gui::TextBox::get_text()
{
    return [[m_textview string] UTF8String];
}
