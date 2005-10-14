/*!
    \file src/cpaf/cocoa/app.mm
    \brief Implementation of cpaf::gui::App for Cocoa
    \date Created: 2005-04-29
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright (C) 2005 Thomas Steinacher
    http://www.eggdrop.ch/
    tom (at) eggdrop [dot] ch
*/

#include <cpaf/gui/app.h>
#include <cpaf/exception.h>

#import <Cocoa/Cocoa.h>

namespace {
	int s_argc;
	char **s_argv;
	NSAutoreleasePool *pool;
} // anon namespace

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
    appleMenuServicesItem = [[[NSMenuItem alloc] initWithTitle:@"Services" action:nil keyEquivalent:@""] autorelease];
    appleMenuQuitItem = [[[NSMenuItem alloc] initWithTitle:[NSString stringWithFormat:@"Quit %@", getApplicationName()] action:@selector(cpafTerminate:) keyEquivalent:@"q"] autorelease];
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

@interface CpafApplicationDelegate : NSObject
- (void)cpafTerminate:(id)sender;
@end

@implementation CpafApplicationDelegate
- (void)cpafTerminate:(id)sender
{
    // Quit the application
    cpaf::get_app().quit();
}
@end

void cpaf::gui::App::gui_init()
{
    pool = [[NSAutoreleasePool alloc] init];

    // Initialize the application
    [NSApplication sharedApplication];
    [NSApp setDelegate:[CpafApplicationDelegate new]];
    
    // Set up an initial menu bar, because the default one doesn't work as expected
    set_up_menubar();
}

void cpaf::gui::App::_quit()
{
    [NSApp terminate:nil];
    [pool release];
}
