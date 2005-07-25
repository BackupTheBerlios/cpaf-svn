// \todo Include some test cases. This is just a stub.

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/entrybox.h>
#include <cpaf/gui/textbox.h>

#if defined(_MSC_VER) && defined(_DEBUG)
#   include <crtdbg.h>
#   define DBG_MSG(s)      _CrtDbgReport(_CRT_WARN, __FILE__, __LINE__, "", s ## "\n");
#   define DBG_MSG_2(f, s) _CrtDbgReport(_CRT_WARN, __FILE__, __LINE__, "", f ## "\n", s);
#elif defined(__APPLE__) && defined(_DEBUG)
#   include <stdio.h>
#   define DBG_MSG(s)      printf("%s:%d %s\n", __FILE__, __LINE__, s)
#else
#   define DBG_MSG(s)
#   define DBG_MSG_2(f,s)
#endif

using cpaf::gui::factory::create_widget;
using namespace cpaf::event;

/*
    Our derived application class
*/
class MyApp : public cpaf::gui::App
{
public:
    bool init();
};

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    cpaf::gui::Window *wnd = create_widget<cpaf::gui::Window>(
        cpaf::gui::Window::Initializer()
        .title("Cpaf")
        .client_size(cpaf::Size(400,400))
        );

    cpaf::gui::Button *btn = create_widget<cpaf::gui::Button>(cpaf::gui::Button::Initializer()
        .parent(wnd)
        .label("A button")
        .size(cpaf::Size(200,40))
        .position(cpaf::Point(50,50))
        .show()
        );

    /*
        Create an EntryBox
    */
    cpaf::gui::EntryBox *entry = create_widget<cpaf::gui::EntryBox>(cpaf::gui::EntryBox::Initializer()
        .parent(wnd)
        .text("I'm an entry box!")
        .position(cpaf::Point(10,150))
        .size(cpaf::Size(200,30))
        .password_mode(false)
        .show()
        );

    /*
        Create a TextBox
    */
    cpaf::gui::TextBox *text = create_widget<cpaf::gui::TextBox>(cpaf::gui::TextBox::Initializer()
        .parent(wnd)
        .text("I'm a multline text box!\nHere's the second line\n\nLorem ipsum dolor sit amet, sed consectetuer adipiscing elit.")
        .position(cpaf::Point(10,200))
        .size(cpaf::Size(300,100))
        .show()
        );

    // Show the window last for proper visual appearance
    wnd->show();

    return true;
}

/*
    Entry point for the application which returns an instance of the application object to use
*/
cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
