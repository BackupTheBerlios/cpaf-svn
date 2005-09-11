/*
Proof of concept demo for cpaf
*/

/*
IMPORTANT NOTE for using dll cpaf build
In order to do things like throwing across dll boundaries and std::string cleanup
playing nice through dll boundaries, a dynamically linked run time library MUST BE USED
*/

#include <cpaf/debug.h>
#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/entrybox.h>
#include <cpaf/gui/textbox.h>
#include <cpaf/gui/panel.h>
#include <cpaf/gui/gridbaglayout.h>

using namespace cpaf::event;
using namespace cpaf::gui;

/*
    Our derived application class
*/
class MyApp : public App
{
public:
    EntryBox *pw; // The password box
    Button *destroy_btn;

    bool init();
    void toggle_password_mode(Event &event);
    void destroy_button(Event &event);
};

/*
    A derived button
*/
class MyButton : public Button
{
public:
    static MyButton *create(const Initializer &initializer)
    {
        MyButton *wrapper = new MyButton;
        wrapper->initialize(initializer);
        return wrapper;
    }

protected:
    MyButton()
    {
        cpaf::DebugReport() << "MyButton::Ctor";

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
        cpaf::DebugReport() << "MyButton::on_create";

        // let the other listeners in the chain process
        event.continue_processing();
    }

    virtual void on_btn_click(cpaf::event::Event &event)
    {
        static int status = 0;

        cpaf::DebugReport() << "MyButton::on_btn_click";

        if (status++ == 0)
            set_label("Thank you! Click again to quit!");
        else
            cpaf::get_app().quit();
    }

    virtual void on_destroy(cpaf::event::Event &event)
    {
        cpaf::DebugReport() << "MyButton::on_destroy";
    }
};

/*
    Another derived class demonstration the use of virtual event listener functions
*/
class MyButton2 : public MyButton
{
public:
    static MyButton2 *create(const Initializer &initializer)
    {
        MyButton2 *wrapper = new MyButton2;
        wrapper->initialize(initializer);
        return wrapper;
    }

protected:
    MyButton2() { }

    // override the base event listener
    void on_destroy(cpaf::event::Event &event)
    {
        cpaf::DebugReport() << "MyButton2::on_destroy";
    }
};

void MyApp::toggle_password_mode(Event &event)
{
    cpaf::DebugReport() << "MyApp::toggle_password_mode";
    pw->set_password_mode(!pw->get_password_mode());
}

void MyApp::destroy_button(Event &event)
{
    cpaf::DebugReport() << "MyApp::destroy_button";
    destroy_btn->destroy();
}

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    // panels must have a layout manager
    GridBagLayout *gblm;
    Panel *panel = Panel::create(Panel::Initializer().layout_manager(gblm = new GridBagLayout));

    /*
        Create some explicitly sized and positioned buttons which are initially visible.
        One of these buttons is a derived button.
        We also reuse the data initializer object to create these buttons.
    */
    Button::Initializer btn_init;
    Button *btn = Button::create(btn_init
        .parent(panel)
        .label("Toggle password mode")
        .size(cpaf::Size(200,40))
        .position(cpaf::Point(50,50))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, btn->get_id()) (&MyApp::toggle_password_mode, *this);
    btn->set_min_size(cpaf::Size(150,50));

    // all children must be added to their parents layout manager
    GridBagLayoutInfo info;
    info.position(0,0).padding(5).align_center();
    gblm->add_widget(btn, info);

    MyButton2 *my_btn = MyButton2::create(btn_init
        .label("Click me!")
        .position(cpaf::Point(100,100))
        );

    info.position(1, 0).expand_both();
    gblm->add_widget(my_btn, info);
    my_btn->set_min_size(cpaf::Size(100,30));

    gblm->set_column_weight(0, 1);
    gblm->set_column_weight(1, 2);
    gblm->set_column_weight(2, 1);
    gblm->set_row_weight(0, 1);
    gblm->set_row_weight(1, 2);

    destroy_btn = Button::create(btn_init
        .parent(panel)
        .label("Click to destroy me")
        .size(cpaf::Size(200,30))
        .position(cpaf::Point(50, 320))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, destroy_btn->get_id()) (&MyApp::destroy_button, *this);

    info.position(2,1).padding_bottom(0).padding_right(0);
    gblm->add_widget(destroy_btn, info);

#if 0
    /*
        Create an EntryBox
    */
    EntryBox *entry = EntryBox::create(EntryBox::Initializer()
        .parent(panel)
        .text("I'm an entry box!")
        .position(cpaf::Point(10,150))
        .size(cpaf::Size(200,30))
        .show()
        );

    /*
        Create a TextBox
    */
    TextBox *text = TextBox::create(TextBox::Initializer()
        .parent(panel)
        .text("I'm a multline text box!\nHere's the second line\n\nLorem ipsum dolor sit amet, sed consectetuer adipiscing elit.")
        .position(cpaf::Point(10,200))
        .size(cpaf::Size(300,100))
        .show()
        );

    /*
        Create a EntryBox for passwords
    */
    pw = EntryBox::create(EntryBox::Initializer()
        .parent(panel)
        .text("I'm a password box!")
        .position(cpaf::Point(10,10))
        .size(cpaf::Size(200,30))
        .password_mode()
        .show()
        );

    // test get_parent(). This should not change the value of panel
    cpaf::DebugReport() << "panel before:\t" << std::hex << std::setfill('0') << std::setw(8) << panel;
    panel = text->get_parent();
    cpaf::DebugReport() << "panel after:\t" << std::hex << std::setfill('0') << std::setw(8) << panel;
#endif
    /*
        Construct a window with a default position and a default size.
        The factory object initializes its members to specify "default values"
        which instruct an implementation to let the system determine an appropriate
        size and position. If the system is not capable of doing this, the implementation
        must chose reasonable values.

        This window will be visible without calling wnd->show() if .show() isn't commented out below.
    */
    Window *wnd = Window::create(Window::Initializer()
        .content_panel(panel)
        .title("Cpaf")
        .client_size(cpaf::Size(400,400))
        //.show()
        );

#if 0
    // test get_parent_window. This should not change the value of wnd
    cpaf::DebugReport() << "Window before:\t" << std::hex << std::setfill('0') << std::setw(8) << wnd;
    wnd = pw->get_parent_window();
    cpaf::DebugReport() << "Window after:\t" << std::hex << std::setfill('0') << std::setw(8) << wnd;
#endif

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
