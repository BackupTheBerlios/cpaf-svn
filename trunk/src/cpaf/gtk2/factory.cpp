/**
 * \file src/cpaf/gtk2/factory.cpp
 * \brief Implementation of gtk2 factory
 * \date 2005-04-05
 */

#include <cpaf/private/factory.h>
#include <cpaf/gtk2/gui/window.h>
#include <cpaf/gtk2/gui/button.h>

IMPLEMENT_WIDGET_FACTORY(Window, window, gtk2)
IMPLEMENT_WIDGET_FACTORY(Button, button, gtk2)
