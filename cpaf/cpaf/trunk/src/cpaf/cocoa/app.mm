/**
 * \file src/cpaf/cocoa/app.mm
 * \brief Implementation of cpaf::gui::App::run() for Cocoa
 * \date 2005-04-29
 */

#include <cpaf/gui/app.h>
#import <Cocoa/Cocoa.h>

static int s_argc;
static char **s_argv;

void register_argc_argv(int argc, char *argv[])
{
    s_argc = argc;
    s_argv = argv;
}

void cpaf::gui::App::gui_init()
{
}

int cpaf::gui::App::run()
{
    return NSApplicationMain(s_argc, s_argv);
}
