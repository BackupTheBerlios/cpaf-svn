/*
This file implements the static factory_key members for all of the api::gui classes that are constructable
*/

#include <cpaf/api/gui/window.h>

static int get_key()
{
    static int next;

    return next++;
}

int cpaf::api::gui::Window::factory_key = get_key();
