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
    boost::shared_ptr<Button> test_btn;
    boost::shared_ptr<Window> test_wnd;
    boost::shared_ptr<Button> showhidebtn_btn;
    boost::shared_ptr<Button> showhidewnd_btn;

    bool init();
    void showhidebtn(const Event &event);
    void showhidewnd(const Event &event);
};

void MyApp::showhidebtn(const Event &event)
{
    cpaf::DebugReport() << "MyApp::showhidebtn";
    test_btn->show(!test_btn->is_shown());
}

void MyApp::showhidewnd(const Event &event)
{
    cpaf::DebugReport() << "MyApp::showhidewnd";
    test_wnd->show(!test_wnd->is_shown());
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

    btn_init.parent(panel).show();

    showhidewnd_btn = Button::create(btn_init.label("Show/hide the window"));
    connect<Event>(BUTTON_CLICK, showhidewnd_btn->get_id()) (&MyApp::showhidewnd, *this);

    showhidebtn_btn = Button::create(btn_init.label("Show/hide the button"));
    connect<Event>(BUTTON_CLICK, showhidebtn_btn->get_id()) (&MyApp::showhidebtn, *this);

    test_btn = Button::create(btn_init.label("The test button").show(false));

    boost::shared_ptr<Window> wnd = Window::create(Window::Initializer()
        .content_panel(panel)
        .title("Show/hide unit test")
        .client_size(cpaf::Size(500,300))
        );

    test_wnd = Window::create(Window::Initializer().title("Test window").client_size(cpaf::Size(200,20)));

    GridBagLayoutInfo info;
    gblm->add(
        EntryBox::create(EntryBox::Initializer().parent(panel)
            .text("The test button and the test window should be hidden by default")
            .min_size(cpaf::Size(100,25)).show()),
        info.position(0,0).align_top().expand_horizontal()
    );
    info.expand_both();
    gblm->add(showhidewnd_btn, info.position(0,1));
    gblm->add(showhidebtn_btn, info.position(0,2));
    gblm->add(test_btn, info.position(0,3));
    gblm->set_row_weight(0, 0);
    gblm->set_margins(5);

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
