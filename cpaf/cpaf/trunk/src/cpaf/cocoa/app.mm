/**
 * \file src/cpaf/cocoa/app.mm
 * \brief Implementation of cpaf::gui::App::run() for Cocoa
 * \date 2005-04-29
 */

#include <cpaf/gui/app.h>
#include <cpaf/exception.h>
#import <Cocoa/Cocoa.h>

static int s_argc;
static char **s_argv;
static NSAutoreleasePool *pool;

void register_argc_argv(int argc, char *argv[])
{
    s_argc = argc;
    s_argv = argv;
}

void cpaf::gui::App::gui_init()
{
    pool = [[NSAutoreleasePool alloc] init];
    
    // We need to call NSApplicationLoad() if we're creating a window before NSApplicationMain() is called
    if (NSApplicationLoad() == NO)
        throw cpaf::Exception(cpaf::Exception::GUI_INIT_FAILED, __LINE__, __FILE__);
}

int cpaf::gui::App::run()
{
    [pool release];
    return NSApplicationMain(s_argc, (const char **)s_argv);
}
