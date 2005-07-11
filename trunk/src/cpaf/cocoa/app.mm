/**
 * \file src/cpaf/cocoa/app.mm
 * \brief Implementation of cpaf::gui::App::run() for Cocoa
 * \date Created: 2005-04-29
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

@interface NSApplication(AppleMenu)
// setAppleMenu: disappeared from the header-file and the documentation
// for some reason in Tiger, so let's add it here...
- (void)setAppleMenu:(NSMenu *)menu;
@end

// Stolen from SDL (SDLMain.m)
static NSString *getApplicationName(void)
{
    NSDictionary *dict;
    NSString *appName = 0;

    /* Determine the application name */
    dict = (NSDictionary *)CFBundleGetInfoDictionary(CFBundleGetMainBundle());
    if (dict)
        appName = [dict objectForKey: @"CFBundleName"];
    
    if (![appName length])
        appName = [[NSProcessInfo processInfo] processName];

    return appName;
}

static void set_up_menubar()
{
    NSMenu *menuBar;
    NSMenu *appleMenu;
    NSMenu *servicesMenu;
    NSMenuItem *appleMenuItem;
    NSMenuItem *appleMenuQuitItem, *appleMenuHideItem, *appleMenuServicesItem;
    NSMenuItem *appleMenuHideOthersItem, *appleMenuShowAllItem;
    
    menuBar = [[[NSMenu alloc] initWithTitle:@""] autorelease];
    
    appleMenu = [[[NSMenu alloc] initWithTitle:@""] autorelease];
    servicesMenu = [[[NSMenu alloc] initWithTitle:@""] autorelease];
    
    appleMenuItem = [[[NSMenuItem alloc] init] autorelease];
    
    [appleMenuItem setSubmenu:appleMenu];

    [menuBar addItem:appleMenuItem];

    //! \todo Localization
    appleMenuServicesItem = [[[NSMenuItem alloc] initWithTitle:@"Services" action:@selector(terminate:) keyEquivalent:@""] autorelease];
    appleMenuQuitItem = [[[NSMenuItem alloc] initWithTitle:[NSString stringWithFormat:@"Quit %@", getApplicationName()] action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
    appleMenuHideItem = [[[NSMenuItem alloc] initWithTitle:[NSString stringWithFormat:@"Hide %@", getApplicationName()] action:@selector(hide:) keyEquivalent:@"h"] autorelease];
    appleMenuHideOthersItem = [[[NSMenuItem alloc] initWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"] autorelease];
    [appleMenuHideOthersItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];
    appleMenuShowAllItem = [[[NSMenuItem alloc] initWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""] autorelease];

    [appleMenuServicesItem setSubmenu:servicesMenu];
    
    [appleMenu addItem:appleMenuServicesItem];
    [appleMenu addItem:[NSMenuItem separatorItem]];
    [appleMenu addItem:appleMenuHideItem];
    [appleMenu addItem:appleMenuHideOthersItem];
    [appleMenu addItem:appleMenuShowAllItem];
    [appleMenu addItem:[NSMenuItem separatorItem]];
    [appleMenu addItem:appleMenuQuitItem];

    [NSApp setMainMenu:menuBar];
    [NSApp setAppleMenu:appleMenu];
    [NSApp setServicesMenu:servicesMenu];
}

void cpaf::gui::App::gui_init()
{
    pool = [[NSAutoreleasePool alloc] init];

    // Initialize the application
    [NSApplication sharedApplication];
    
    // Set up an initial menu bar, because the default one doesn't work as expected
    set_up_menubar();
}

int cpaf::gui::App::run()
{
    [pool release];

    [NSApp run]; // Run the application
    
    return 0;
}
