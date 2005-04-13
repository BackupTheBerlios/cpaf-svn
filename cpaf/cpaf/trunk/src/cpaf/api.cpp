/*
This file implements the static factory_key members for all of the api::gui classes that are constructable,
as well as the api::gui::Object dtor
*/

#include <cpaf/api/gui/window.h>
#include <cpaf/api/gui/button.h>

static int get_key()
{
    static int next = 5;

    return ++next;
}

int cpaf::api::gui::Window::factory_key = 6;
int cpaf::api::gui::Button::factory_key = 1000;

cpaf::api::gui::Object::~Object() { }
