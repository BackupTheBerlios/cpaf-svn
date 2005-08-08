/**
 * \file src/cpaf/gtk2/factory.cpp
 * \brief Implementation of gtk2 factory
 * \date Created: 2005-04-05
 */

#include <cpaf/private/factory.h>
#include <cpaf/gtk2/gui/window.h>
#include <cpaf/gtk2/gui/button.h>
#include <cpaf/gtk2/gui/entrybox.h>
#include <cpaf/gtk2/gui/textbox.h>

IMPLEMENT_WIDGET_FACTORY(Window, gtk2)
IMPLEMENT_WIDGET_FACTORY(Button, gtk2)
IMPLEMENT_WIDGET_FACTORY(EntryBox, gtk2)
IMPLEMENT_WIDGET_FACTORY(TextBox, gtk2)
