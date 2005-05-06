/**
 * \file src/cpaf/cocoa/button.mm
 * \brief Implementation of Cocoa button
 * \date 2005-04-29
 */

#include <cpaf/cocoa/gui/button.h>

cpaf::cocoa::gui::Button::Button(cpaf::api::gui::Widget *parent)
    : Widget(parent, [[NSButton alloc] init])
{
    [m_widget setButtonType:NSToggleButton];
    [(NSButton*)m_widget setBezelStyle:NSRegularSquareBezelStyle];
    //[m_widget setAction:@selector(:)];
}

void cpaf::cocoa::gui::Button::set_label(const std::string &label)
{
    [m_widget setTitle:[NSString stringWithUTF8String:label.c_str()]];
}

std::string cpaf::cocoa::gui::Button::get_label()
{
    return [[m_widget title] UTF8String];
}
