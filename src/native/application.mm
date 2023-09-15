#include <iostream>

#include "application.h"
#include <Cocoa/Cocoa.h>
#include "main_component.h"

@interface AppDelegate : NSObject <NSApplicationDelegate> {
  // tiler::Manager tilerManager;
  // NSStatusItem* statusItem;
  NSWindow *window;
  MainComponent *component;
}
@end

inline static NSMenu *CreateMenu() {

  NSMenu *menu = [[NSMenu alloc] initWithTitle:@"Title"];

  {
    NSMenu *aboutMenu = [[NSMenu alloc] initWithTitle:@"AppName"];

    NSMenuItem *item =
        [[NSMenuItem alloc] initWithTitle:@"Quit"
                                   action:@selector(OnMenuItemQuit:)
                            keyEquivalent:@""];
    [aboutMenu addItem:item];
    [item release];

    NSMenuItem *aboutMenuItem =
        [[NSMenuItem alloc] initWithTitle:@"About"
                                   action:@selector(OnMenuItemQuit:)
                            keyEquivalent:@""];
    [aboutMenuItem setSubmenu:aboutMenu];
    [aboutMenu release];

    [menu addItem:aboutMenuItem];
    [aboutMenuItem release];
  }

  {
    NSMenu *fileMenu = [[NSMenu alloc] initWithTitle:@"File"];

    NSMenuItem *item =
        [[NSMenuItem alloc] initWithTitle:@"Quit"
                                   action:@selector(OnMenuItemQuit:)
                            keyEquivalent:@""];
    [fileMenu addItem:item];
    [item release];

    NSMenuItem *fileMenuItem =
        [[NSMenuItem alloc] initWithTitle:@"File"
                                   action:@selector(OnMenuItemQuit:)
                            keyEquivalent:@""];
    [fileMenuItem setSubmenu:fileMenu];
    [fileMenu release];

    [menu addItem:fileMenuItem];
    [fileMenuItem release];
  }

  return menu;
}

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {

  NSMenu *menu = CreateMenu();
  NSApplication *app = [NSApplication sharedApplication];
  [app setMainMenu:menu];
  [menu release];

  NSWindowStyleMask style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable;
  window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 400, 400)
                                       styleMask:style
                                         backing:NSBackingStoreBuffered
                                           defer:false];

  [window setReleasedWhenClosed:false];
  //  [window makeKeyAndOrderFront];
  [window makeKeyWindow];
  [window orderFrontRegardless];
  [window center];

  std::cout << [window contentView] << std::endl;

  juce::MessageManager::getInstance();
  juce::MessageManagerLock lock;

  component = new MainComponent();

  std::cout << component->getWidth() << std::endl;
  component->addToDesktop(0, (void *)[window contentView]);
  component->setVisible(true);

  juce::Rectangle<int> rect = component->getBounds();
  [window setContentSize:NSMakeSize(rect.getWidth(), rect.getHeight())];
  [window setMinSize:NSMakeSize(rect.getWidth(), rect.getHeight())];
  [window setMaxSize:NSMakeSize(rect.getWidth(), rect.getHeight())];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
  component->removeFromDesktop();
  delete component;
  component = nullptr;

  [window release];
  window = nullptr;
  juce::DeletedAtShutdown::deleteAll();
  juce::MessageManager::deleteInstance();
}

- (void)OnMenuItemQuit:(id)sender {
  std::cout << "OnMenuItemQuit" << std::endl;
  [[NSApplication sharedApplication] terminate:self];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:
    (NSApplication *)sender {
  return true;
}

@end

namespace mstd {
int main(int argc, const char *argv[]) {
  NSApplication *nsApp = [NSApplication sharedApplication];
  AppDelegate *appDelegate = [[AppDelegate alloc] init];
  [nsApp setDelegate:appDelegate];

  return NSApplicationMain(argc, argv);
}
} // namespace mstd
