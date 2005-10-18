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
#include <cpaf/flags.h>

using namespace cpaf::event;
using namespace cpaf::gui;
using namespace cpaf::flags;

/*
    Our derived application class
*/
class MyApp : public App
{
public:
    boost::shared_ptr<EntryBox> pw; // The password box
    boost::shared_ptr<Button> destroy_btn;

    bool init();
    void toggle_password_mode(const Event &event);
    void destroy_button(const Event &event);
    void on_text_changed(const Event &event);
    void get_pos(const Event &event);
};

/*
    A derived button
*/
class MyButton : public Button
{
public:
    static boost::shared_ptr<MyButton> create(const Initializer &initializer)
    {
        MyButton *wrapper = new MyButton;
        return boost::dynamic_pointer_cast<MyButton>(wrapper->initialize(initializer));
    }

protected:
    MyButton()
    {
        cpaf::DebugReport() << "MyButton::Ctor";

        // connected one event listener
        connect<Event>(WIDGET_DESTROY, get_id()) (&MyButton::on_destroy, *this);

        // connecting multiple event listeners into a chain
        // also store the event chain object for later use
        SlotChainWrapper<Event> w = connect<Event>(WIDGET_CREATE, get_id())
            (&MyButton::on_create, *this)
            (&MyButton::on_create, *this);

        // connect another listener
        w(&MyButton::on_create, *this);

        // connect the click-event
        connect<Event>(BUTTON_CLICK, get_id()) (&MyButton::on_btn_click, *this);
    }

    void on_create(const Event &event)
    {
        cpaf::DebugReport() << "MyButton::on_create";

        // let the other listeners in the chain process
        event.continue_processing();
    }

    virtual void on_btn_click(const Event &event)
    {
        static int status = 0;

        cpaf::DebugReport() << "MyButton::on_btn_click";

        if (status++ == 0)
            set_label("Thank you! Click again to quit!");
        else
            cpaf::get_app().quit();
    }

    virtual void on_destroy(const Event &event)
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
    static boost::shared_ptr<MyButton2> create(const Initializer &initializer)
    {
        MyButton2 *wrapper = new MyButton2;
        return boost::dynamic_pointer_cast<MyButton2>(wrapper->initialize(initializer));
    }

protected:
    MyButton2() { }

    // override the base event listener
    void on_destroy(cpaf::event::Event &event)
    {
        cpaf::DebugReport() << "MyButton2::on_destroy";
    }
};

void MyApp::toggle_password_mode(const Event &event)
{
    cpaf::DebugReport() << "MyApp::toggle_password_mode";
    pw->set_password_mode(!pw->get_password_mode());
}

void MyApp::destroy_button(const Event &event)
{
    cpaf::DebugReport() << "MyApp::destroy_button";
    destroy_btn->destroy();

    // we don't need the button reference anymore so allow memory to be reclaimed
    destroy_btn.reset();
}

void MyApp::on_text_changed(const Event &event)
{
    cpaf::DebugReport() << "MyApp::on_text_changed";
}

void MyApp::get_pos(const Event &event)
{
    cpaf::Point p = cpaf::gui::get_widget_from_id(event.get_object_id())->get_parent_window()->get_position();
    cpaf::DebugReport() << "MyApp::get_pos " << p.x << " x " << p.y;
}

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    // panels must have a layout manager
    boost::shared_ptr<GridBagLayout> gblm(new GridBagLayout);
    boost::shared_ptr<cpaf::gui::Panel> panel = Panel::create(Panel::Initializer().layout_manager(gblm));

    Button::Initializer btn_init;
    boost::shared_ptr<Button> pw_mode = Button::create(btn_init
        .parent(panel)
        .label("Toggle password mode")
        .show()
        );
    connect<Event>(BUTTON_CLICK, pw_mode->get_id()) (&MyApp::toggle_password_mode, *this);
    pw_mode->set_min_size(cpaf::Size(250,10));
    //pw_mode->set_natural_size(cpaf::Size(300,0));

    boost::shared_ptr<Button> get_pos = Button::create(btn_init
        .parent(panel)
        .label("Get window position")
        .show()
        );
    connect<Event>(BUTTON_CLICK, get_pos->get_id()) (&MyApp::get_pos, *this);
    get_pos->set_min_size(cpaf::Size(250,10));

    boost::shared_ptr<MyButton2> my_btn = MyButton2::create(btn_init
        .label("Click me!")
        .min_size(cpaf::Size(100,30))
        );

    destroy_btn = Button::create(btn_init
        .parent(panel)
        .label("Click to destroy me")
        .show()
        );
    connect<Event>(BUTTON_CLICK, destroy_btn->get_id()) (&MyApp::destroy_button, *this);

    /*
        Create an EntryBox
    */
    boost::shared_ptr<EntryBox> entry = EntryBox::create(EntryBox::Initializer()
        .parent(panel)
        .text("I'm an entry box!")
        .show()
        );

    /*
        Create a TextBox
    */
    boost::shared_ptr<TextBox> text = TextBox::create(TextBox::Initializer()
        .parent(panel)
        .text("I'm a multline text box!\nHere's the second line\n\nLorem ipsum dolor sit amet, sed consectetuer adipiscing elit.")
        .show()
        );

    connect<Event>(TEXT_CHANGED, text->get_id()) (&MyApp::on_text_changed, *this);

    /*
        Create a EntryBox for passwords
    */
    pw = EntryBox::create(EntryBox::Initializer()
        .parent(panel)
        .text("I'm a password box!")
        .password_mode()
        .show()
        );

    boost::shared_ptr<Window> wnd = Window::create(Window::Initializer()
        .content_panel(panel)
        .title("Cpaf")
        .client_size(cpaf::Size(400,400))
        );

    // all children must be added to their parents layout manager
    GridBagLayoutInfo info;
    gblm->add(pw_mode,
        info.position(0,1).flags(EXPAND_BOTH));
    gblm->add(pw,
        info.position(0,0));
    gblm->add(my_btn,
        info.position(1, 0));
    gblm->add(destroy_btn,
        info.position(1,1));
    gblm->add(entry,
        info.position(3, 0));
    gblm->add(text,
        info.position(3, 1));
    gblm->add(get_pos,
        info.position(0,2));

    gblm->set_column_weight(0, 0);
    gblm->set_column_weight(1, 2);
    gblm->set_column_weight(2, 1);
    gblm->set_row_weight(0, 0);
    gblm->set_row_weight(1, 2);
    gblm->set_margins(5);

    // test get_parent(). This should not change the value of *panel
    cpaf::DebugReport() << "panel before:\t" << std::hex << std::setfill('0') << std::setw(8) << panel;
    panel = text->get_parent();
    cpaf::DebugReport() << "panel after:\t" << std::hex << std::setfill('0') << std::setw(8) << panel;

    // test get_parent_window. This should not change the value of *wnd
    cpaf::DebugReport() << "Window before:\t" << std::hex << std::setfill('0') << std::setw(8) << wnd;
    wnd = pw->get_parent_window();
    cpaf::DebugReport() << "Window after:\t" << std::hex << std::setfill('0') << std::setw(8) << wnd;

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
