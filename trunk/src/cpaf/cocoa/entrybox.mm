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

//! \todo This is a hack that fixes rendering bugs. There should be a better way to fix them,
//        because the bug doesn't occur in password fields created with Interface Builder
@interface CpafSecureTextField (RenderingHack)
- (void)textDidChange:(NSNotification *)n;
@end

@implementation CpafSecureTextField (RenderingHack)
- (void)textDidChange:(NSNotification *)n
{
    [[n object] display];
}
@end
// end hack

void cpaf::cocoa::gui::EntryBox::create(const cpaf::gui::initializer::EntryBoxData &params)
{
    id widget = nil;

    if( !params.m_parent )
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    // Create a password field or a text field?
    if (params.m_get_password_mode)
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
    if (mode == get_password_mode())
        return; // Don't have to change anything

    NSTextField *old_object = m_object;
    
    if (mode)
        m_object = [[CpafSecureTextField alloc] init];
    else
        m_object = [[CpafTextField alloc] init];

    // Set the properties (Is there a better way to do that?)
    // We need to update that when we change properties that are not listed here
    [[m_object cell] setScrollable:[[old_object cell] isScrollable]];
    [[m_object cell] setWraps:[[old_object cell] wraps]];
	[m_object setStringValue:[old_object stringValue]];
	[m_object setFrame:[old_object frame]];
    [m_object setAutoresizingMask:[old_object autoresizingMask]];
    
    // Set the cpaf widget
    [m_object setCpafWidget:this];

    // Add the new text field
    [[old_object superview] addSubview:m_object];

    // Remove the old field from its superview and release it
    [old_object removeFromSuperview];
    [old_object release];
}

bool cpaf::cocoa::gui::EntryBox::get_password_mode()
{
    return [m_object isKindOfClass:[NSSecureTextField class]];
}

void cpaf::cocoa::gui::EntryBox::set_text(const std::string &s)
{
    [m_object setStringValue:[NSString stringWithUTF8String:s.c_str()]];
}

std::string cpaf::cocoa::gui::EntryBox::get_text() const
{
    return [[m_object stringValue] UTF8String];
}

std::string cpaf::cocoa::gui::EntryBox::get_text(const cpaf::TextRange &range) const
{
    return "";
}

cpaf::text_range_t cpaf::cocoa::gui::EntryBox::get_length() const
{
    return get_text().length();
}

cpaf::TextRange cpaf::cocoa::gui::EntryBox::get_selection_range() const
{
    NSResponder *firstResponder = [[m_object window] firstResponder];

    // There's only a selection, when the EntryBox is focused
    if (firstResponder && [firstResponder isKindOfClass:[NSText class]])
    {
        if ([(NSText *)firstResponder delegate] == m_object)
        {
            NSRange range = [(NSText *)firstResponder selectedRange];

            // The insertion point is at the beginning of the selection
            return cpaf::TextRange(range.location+range.length, range.location);
        }
    }
    return cpaf::TextRange();
}

void cpaf::cocoa::gui::EntryBox::set_selection_range(const cpaf::TextRange &range)
{
}

bool cpaf::cocoa::gui::EntryBox::get_selection_bounds(cpaf::TextRange &range) const
{
    range = get_selection_range();
    range.normalize();
    return range.first != range.second;
}

void cpaf::cocoa::gui::EntryBox::set_selection_bounds(const cpaf::TextRange &range)
{

}

cpaf::text_range_t cpaf::cocoa::gui::EntryBox::get_insertion_point() const
{
    return get_selection_range().second;
}

void cpaf::cocoa::gui::EntryBox::set_insertion_point(cpaf::text_range_t pos)
{

}

void cpaf::cocoa::gui::EntryBox::delete_range(const cpaf::TextRange &range)
{

}

void cpaf::cocoa::gui::EntryBox::insert_text(cpaf::text_range_t pos, const std::string &str)
{

}

void cpaf::cocoa::gui::EntryBox::set_max_length(cpaf::text_range_t len)
{

}

void cpaf::cocoa::gui::EntryBox::set_read_only(bool b)
{
    [m_object setEditable:!b];
    
    // If the widget will be read only, make sure it isn't focused anymore
    if (b)
    {
        // \todo Remove duplicate code

        NSResponder *firstResponder = [[m_object window] firstResponder];

        if (firstResponder && [firstResponder isKindOfClass:[NSText class]])
        {
            if ([(NSText *)firstResponder delegate] == m_object)
            {
                // Focus the next responder
                [[m_object window] makeFirstResponder:[m_object nextResponder]];
            }
        }
    }
    [m_object display]; // Cocoa doesn't redisplay the entry box, do that here
}

bool cpaf::cocoa::gui::EntryBox::is_read_only() const
{
    return ![m_object isEditable];
}

