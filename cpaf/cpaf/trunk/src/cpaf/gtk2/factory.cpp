/**
 * \file src/cpaf/gtk2/factory.cpp
 * \brief Implementation of gtk2 factory
 * \date 2005-04-05
 */

#include <cpaf/private/factory.h>
#include <cpaf/gtk2/factory.h>
#include <cpaf/gtk2/gui/window.h>
#include <cpaf/gtk2/gui/button.h>

DEFINE_FACTORY(Window, window)
{
    return new cpaf::gtk2::gui::Window(params);
}

DEFINE_FACTORY(Window, window)
{
    return new cpaf::gtk2::gui::Button(params);
}
