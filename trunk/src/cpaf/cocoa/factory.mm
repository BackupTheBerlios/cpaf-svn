/**
 * \file src/cpaf/cocoa/factory.mm
 * \brief Implementation of Cocoa factory
 * \date Created: 2005-04-29
 */

#include <cpaf/private/factory.h>
#include <cpaf/cocoa/gui/window.h>
#include <cpaf/cocoa/gui/button.h>
#include <cpaf/cocoa/gui/textwidget.h>
#include <cpaf/cocoa/gui/entrybox.h>
#include <cpaf/cocoa/gui/textbox.h>

IMPLEMENT_WIDGET_FACTORY(Window, cocoa)
IMPLEMENT_WIDGET_FACTORY(Button, cocoa)
IMPLEMENT_WIDGET_FACTORY(TextWidget, cocoa)
IMPLEMENT_WIDGET_FACTORY(EntryBox, cocoa)
IMPLEMENT_WIDGET_FACTORY(TextBox, cocoa)
