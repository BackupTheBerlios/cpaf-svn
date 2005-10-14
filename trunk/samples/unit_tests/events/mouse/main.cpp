#include <cpaf/debug.h>
#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/entrybox.h>
#include <cpaf/gui/textbox.h>
#include <cpaf/gui/panel.h>
#include <cpaf/gui/gridbaglayout.h>
#include <cpaf/event/event.h>

using namespace cpaf::event;
using namespace cpaf::gui;

/*
    Our derived application class
*/
class MyApp : public App
{
public:
    bool init();
    void btn_mouse_event(const MouseEvent &event);
    void panel_mouse_event(const MouseEvent &event);
    void dump_event(const MouseEvent &event);
};

void MyApp::dump_event(const MouseEvent &event)
{
    cpaf::DebugReport() << "Button flags: " << event.get_button_flags();
    cpaf::DebugReport() << "Key flags: " << event.get_key_flags();
    cpaf::DebugReport() << "Position: " << event.get_position().x << "x" << event.get_position().y;
    //! \todo get_button/key_state()
    cpaf::DebugReport() << "";
}

void MyApp::btn_mouse_event(const MouseEvent &event)
{
    cpaf::DebugReport() << "Button mouse event:";
    dump_event(event);
}

void MyApp::panel_mouse_event(const MouseEvent &event)
{
    cpaf::DebugReport() << "Panel mouse event:";
    dump_event(event);
}

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    // panels must have a layout manager
    boost::shared_ptr<GridBagLayout> gblm(new GridBagLayout);
    boost::shared_ptr<cpaf::gui::Panel> panel = Panel::create(Panel::Initializer().layout_manager(gblm));


    boost::shared_ptr<Button> btn = Button::create(Button::Initializer()
        .parent(panel)
        .label("Button")
        .show()
        .min_size(cpaf::Size(150, 100))
        );

    boost::shared_ptr<Window> wnd = Window::create(Window::Initializer()
        .content_panel(panel)
        .title("Test window")
        .client_size(cpaf::Size(400, 300))
        );

    connect<MouseEvent>(MOUSE_ENTER, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_LEAVE, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_MOVE, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_HOVER, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_LEFT_DOWN, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_LEFT_UP, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_LEFT_DOUBLECLICK, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_MIDDLE_DOWN, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_MIDDLE_UP, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_MIDDLE_DOUBLECLICK, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_RIGHT_DOWN, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_RIGHT_UP, btn->get_id()) (&MyApp::btn_mouse_event, *this);
    connect<MouseEvent>(MOUSE_RIGHT_DOUBLECLICK, btn->get_id()) (&MyApp::btn_mouse_event, *this);

    connect<MouseEvent>(MOUSE_ENTER, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_LEAVE, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_MOVE, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_HOVER, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_LEFT_DOWN, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_LEFT_UP, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_LEFT_DOUBLECLICK, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_MIDDLE_DOWN, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_MIDDLE_UP, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_MIDDLE_DOUBLECLICK, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_RIGHT_DOWN, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_RIGHT_UP, panel->get_id()) (&MyApp::panel_mouse_event, *this);
    connect<MouseEvent>(MOUSE_RIGHT_DOUBLECLICK, panel->get_id()) (&MyApp::panel_mouse_event, *this);

    GridBagLayoutInfo info;
    gblm->add(btn, info.position(0, 0).align_top().align_left());
    gblm->set_margins(10);

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
