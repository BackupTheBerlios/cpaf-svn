/**
 * \file src/cpaf/cocoa/window.mm
 * \brief Implementation of Cocoa window
 * \date 2005-04-29
 */

#include <cpaf/cocoa/gui/window.h>

cpaf::cocoa::gui::Window::Window(cpaf::api::gui::Window *parent)
{
}

void cpaf::cocoa::gui::Window::set_size(const cpaf::Size &s)
{
}

void cpaf::cocoa::gui::Window::set_min_size(const cpaf::Size &s)
{
}

void cpaf::cocoa::gui::Window::set_max_size(const cpaf::Size &s)
{
}

void cpaf::cocoa::gui::Window::set_position(const cpaf::Point &p)
{
}

cpaf::Size cpaf::cocoa::gui::Window::get_size()
{
    return cpaf::Size;
}

cpaf::Size cpaf::cocoa::gui::Window::get_min_size()
{
    return cpaf::Size;
}

cpaf::Size cpaf::cocoa::gui::Window::get_max_size()
{
    return cpaf::Size;
}

cpaf::Point cpaf::cocoa::gui::Window::get_position()
{
    return cpaf::Point;
}

void cpaf::cocoa::gui::Window::show(bool show, bool activate)
{
}

void cpaf::cocoa::gui::Window::set_title(const std::string &t)
{
}

std::string cpaf::cocoa::gui::Window::get_title()
{
    return "";
}

void cpaf::cocoa::gui::Window::set_client_size(const cpaf::Size &s)
{
}

cpaf::Size cpaf::cocoa::gui::Window::get_client_size()
{
    return cpaf::Size;
}

cpaf::Point cpaf::cocoa::gui::Window::get_client_position()
{
    return cpaf::Point;
}
