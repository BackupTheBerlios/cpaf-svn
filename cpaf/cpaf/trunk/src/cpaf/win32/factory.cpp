/*
win32 factory implementation
*/

#include <cpaf/private/factory.h>
#include <cpaf/win32/factory.h>
#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/gui/button.h>

DEFINE_FACTORY(Window, window)
{
    return new cpaf::win32::gui::Window(params);
}

DEFINE_FACTORY(Button, button)
{
    return new cpaf::win32::gui::Button(params);
}
