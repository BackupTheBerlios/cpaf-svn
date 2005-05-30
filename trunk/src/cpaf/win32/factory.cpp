/*
win32 factory implementation
*/

#include <cpaf/private/factory.h>
//#include <cpaf/win32/factory.h>
#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/gui/button.h>

IMPLEMENT_FACTORY(Window, window, win32)
IMPLEMENT_FACTORY(Button, button, win32)
