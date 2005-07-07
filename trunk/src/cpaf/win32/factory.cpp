/*!
    \file src/cpaf/win32/factory.cpp
    \brief Implementation of win32 widget factories
    \date Created: 2005-04-07
*/

#include <cpaf/private/factory.h>
#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/gui/button.h>
#include <cpaf/win32/gui/textbox.h>

IMPLEMENT_WIDGET_FACTORY(Window, win32)
IMPLEMENT_WIDGET_FACTORY(Button, win32)
IMPLEMENT_WIDGET_FACTORY(TextBox, win32)
