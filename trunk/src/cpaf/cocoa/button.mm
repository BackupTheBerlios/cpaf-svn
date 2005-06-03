/**
 * \file src/cpaf/cocoa/button.mm
 * \brief Implementation of Cocoa button
 * \date 2005-04-29
 */

#include <cpaf/cocoa/gui/button.h>

/*
    Please move all object construction related code into the empty create method below.
*/

cpaf::cocoa::gui::Button::Button()
{
}
    /*: Widget(params, [[NSButton alloc] init])
{
    [m_view setButtonType:NSToggleButton];
    [(NSButton*)m_view setBezelStyle:NSRegularSquareBezelStyle];
    set_label(params.m_label);
    //[m_view setAction:@selector(:)];
}*/

void cpaf::cocoa::gui::Button::create(const cpaf::gui::factory::ButtonData &params)
{

}

void cpaf::cocoa::gui::Button::set_label(const std::string &label)
{
    [m_view setTitle:[NSString stringWithUTF8String:label.c_str()]];
}

std::string cpaf::cocoa::gui::Button::get_label()
{
    return [[m_view title] UTF8String];
}
