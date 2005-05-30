/**
 * \file src/cpaf/cocoa/factory.mm
 * \brief Implementation of Cocoa factory
 * \date 2005-04-29
 */

#include <cpaf/private/factory.h>
#include <cpaf/cocoa/factory.h>
#include <cpaf/cocoa/gui/window.h>
#include <cpaf/cocoa/gui/button.h>

IMPLEMENT_FACTORY(Window, window)
{
    return new cpaf::cocoa::gui::Window(params);
}

IMPLEMENT_FACTORY(Button, button)
{
    return new cpaf::cocoa::gui::Button(params);
}
