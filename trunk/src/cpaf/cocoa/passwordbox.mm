/*!
    \file src/cpaf/cocoa/passwordbox.mm
    \brief Implementation of cpaf::cocoa::gui::PasswordBox
    \date Created: 
*/

#include <cpaf/cocoa/gui/passwordbox.h>
#include <cpaf/exception.h>

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

void cpaf::cocoa::gui::PasswordBox::create(const cpaf::gui::initializer::PasswordBoxData &params)
{
    if( !params.m_parent )
        throw cpaf::Exception(cpaf::Exception::WIDGET_NO_PARENT, __LINE__, __FILE__);

    cpaf::cocoa::gui::TextWidget::create(params, [[CpafSecureTextField alloc] init]);
    [[m_object cell] setScrollable:YES];
    [[m_object cell] setWraps:NO];

    send_event(cpaf::event::WIDGET_CREATE);
}
