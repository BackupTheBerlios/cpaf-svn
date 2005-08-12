/*
Proof of concept demo for cpaf
*/

/*
IMPORTANT NOTE for using dll cpaf build
In order to do things like throwing across dll boundaries and std::string cleanup
playing nice through dll boundaries, a dynamically linked run time library MUST BE USED
*/

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/entrybox.h>
#include <cpaf/gui/textbox.h>
#include <cpaf/gui/panel.h>

#if defined(_MSC_VER) && defined(_DEBUG)
#   include <crtdbg.h>
#   define DBG_MSG(s)      _CrtDbgReport(_CRT_WARN, __FILE__, __LINE__, "", s ## "\n");
#   define DBG_MSG_2(f, s) _CrtDbgReport(_CRT_WARN, __FILE__, __LINE__, "", f ## "\n", s);
#elif defined(__GNUG__) && defined(_DEBUG)
#   include <stdio.h>
#   define DBG_MSG(s)      printf("%s:%d: %s\n", __FILE__, __LINE__, s)
#   define DBG_MSG_2(f,s)  printf("%s:%d: " f "\n", __FILE__, __LINE__, s);
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
    cpaf::gui::EntryBox *pw; // The password box
    cpaf::gui::Button *destroy_btn;

    bool init();
    void toggle_password_mode(Event &event);
    void destroy_button(Event &event);
};

/*
    A derived button
*/
class MyButton : public cpaf::gui::Button
{
public:
    MyButton()
    {
        DBG_MSG("MyButton::Ctor");

        // connected one event listener
        connect<Event, false>(WIDGET_DESTROY, get_id()) (&MyButton::on_destroy, *this);

        // connecting multiple event listeners into a chain
        // also store the event chain object for later use
        EventChainWrapper<Event> w = connect<Event, false>(WIDGET_CREATE, get_id())
            (&MyButton::on_create, *this)
            (&MyButton::on_create, *this);

        // connect another listener
        w(&MyButton::on_create, *this);

        // connect the click-event
        connect<Event, false>(BUTTON_CLICK, get_id()) (&MyButton::on_btn_click, *this);
    }

    void on_create(cpaf::event::Event &event)
    {
        DBG_MSG("MyButton::on_create");

        // let the other listeners in the chain process
        event.continue_processing();
    }

    virtual void on_btn_click(cpaf::event::Event &event)
    {
        static int status = 0;
        DBG_MSG("MyButton::on_btn_click");
        if (status++ == 0)
            set_label("Thank you! Click again to quit!");
        else
            cpaf::get_app().quit();
    }

    virtual void on_destroy(cpaf::event::Event &event)
    {
        DBG_MSG("MyButton::on_destroy");
    }
};

/*
    Another derived class demonstration the use of virtual event listener functions
*/
class MyButton2 : public MyButton
{
public:

    MyButton2() { }

    // override the base event listener
    void on_destroy(cpaf::event::Event &event)
    {
        DBG_MSG("MyButton2::on_destroy");
    }
};

void MyApp::toggle_password_mode(Event &event)
{
    DBG_MSG("MyApp::toggle_password_mode");
    pw->set_password_mode(!pw->get_password_mode());
}

void MyApp::destroy_button(Event &event)
{
    DBG_MSG("MyApp::destroy_button");
    destroy_btn->destroy();
}

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    cpaf::gui::Panel *panel = create_widget<cpaf::gui::Panel>(cpaf::gui::Panel::Initializer());

    /*
        Create some explicitly sized and positioned buttons which are initially visible.
        One of these buttons is a derived button.
        We also reuse the data initializer object to create these buttons.
    */
    cpaf::gui::Button::Initializer btn_init;
    cpaf::gui::Button *btn = create_widget<cpaf::gui::Button>(btn_init
        .parent(panel)
        .label("Toggle password mode")
        .size(cpaf::Size(200,40))
        .position(cpaf::Point(50,50))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, btn->get_id()) (&MyApp::toggle_password_mode, *this);

    MyButton2 *my_btn = create_widget<MyButton2>(btn_init
        .label("Click me!")
        .position(cpaf::Point(100,100))
        );

    destroy_btn = create_widget<cpaf::gui::Button>(btn_init
        .parent(panel)
        .label("Click to destroy me")
        .size(cpaf::Size(200,30))
        .position(cpaf::Point(50, 320))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, destroy_btn->get_id()) (&MyApp::destroy_button, *this);

    /*
        Create an EntryBox
    */
    cpaf::gui::EntryBox *entry = create_widget<cpaf::gui::EntryBox>(cpaf::gui::EntryBox::Initializer()
        .parent(panel)
        .text("I'm an entry box!")
        .position(cpaf::Point(10,150))
        .size(cpaf::Size(200,30))
        .show()
        );

    /*
        Create a TextBox
    */
    cpaf::gui::TextBox *text = create_widget<cpaf::gui::TextBox>(cpaf::gui::TextBox::Initializer()
        .parent(panel)
        .text("I'm a multline text box!\nHere's the second line\n\nLorem ipsum dolor sit amet, sed consectetuer adipiscing elit.")
        .position(cpaf::Point(10,200))
        .size(cpaf::Size(300,100))
        .show()
        );

    /*
        Create a EntryBox for passwords
    */
    pw = create_widget<cpaf::gui::EntryBox>(cpaf::gui::EntryBox::Initializer()
        .parent(panel)
        .text("I'm a password box!")
        .position(cpaf::Point(10,10))
        .size(cpaf::Size(200,30))
        .password_mode()
        .show()
        );

    // test get_parent(). This should not change the value of panel
    DBG_MSG_2("panel before == %ld", (long)panel);
    panel = text->get_parent();
    DBG_MSG_2("panel after  == %ld", (long)panel);

    /*
        Construct a window with a default position and a default size.
        The factory object initializes its members to specify "default values"
        which instruct an implementation to let the system determine an appropriate
        size and position. If the system is not capable of doing this, the implementation
        must chose reasonable values.

        This window will be visible without calling wnd->show() if .show() isn't commented out below.
    */
    cpaf::gui::Window *wnd = create_widget<cpaf::gui::Window>(
        cpaf::gui::Window::Initializer()
        .content_panel(panel)
        .title("Cpaf")
        .client_size(cpaf::Size(400,400))
        //.show()
        );

    // test get_parent_window. This should not change the value of wnd
    DBG_MSG_2("Window before == %ld", (long)wnd);
    wnd = pw->get_parent_window();
    DBG_MSG_2("Window after  == %ld", (long)wnd);
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
