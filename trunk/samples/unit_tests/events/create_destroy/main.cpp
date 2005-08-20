/*!
    \brief WIDGET_CREATED and WIDGET_DESTROYED event test case
*/

/*
Expected Output

MyWindow::ctor
MyWindow::on_create
MyButton::ctor
MyButton::on_create
MyWindow::on_destroy
MyWindow::on_panel_destroy
MyButton::on_destroy        * Note: These two functions can be invoked in any order. They both connect to the same
MyWindow::on_btn_destroy    * event from the same object and the order in which the slots are invoked is undefined.
MyButton::dtor
MyWindow::dtor
The program '[2204] create_destroy.exe: Native' has exited with code 0 (0x0).
*/

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/textbox.h>
#include <cpaf/gui/panel.h>

#include <cpaf/debug.h>

using namespace cpaf::gui;
using namespace cpaf::event;
using cpaf::gui::factory::create_widget;

/*
    Our derived application class
*/
class MyApp : public App
{
public:
    bool init();
};

class MyWindow;
MyWindow *parent;

/*
    A derived button
*/
class MyButton : public Button
{
public:
    MyButton()
    {
        cpaf::DebugReport() << "MyButton::ctor";
        
        connect<Event, false>(WIDGET_DESTROY, get_id())(&MyButton::on_destroy, *this);
        connect<Event, false>(WIDGET_CREATE, get_id())(&MyButton::on_create, *this);
    }

    ~MyButton()
    {
        cpaf::DebugReport() << "MyButton::dtor";
    }

    void on_create(Event &event)
    {
        cpaf::DebugReport() << "MyButton::on_create";
    }

    void on_destroy(Event &event);
};

/*
    A derived window
*/
class MyWindow : public Window
{
private:
    MyButton *m_btn;
    Panel *m_panel;

public:
    void *my_data;

    MyWindow()
    {
        cpaf::DebugReport() << "MyWindow::ctor";

        // create the root panel
        m_panel = create_widget<Panel>(Panel::Initializer());

        // connect events
        connect<Event, false>(WIDGET_DESTROY, get_id())(&MyWindow::on_destroy, *this);
        connect<Event, false>(WIDGET_CREATE, get_id())(&MyWindow::on_create, *this);
        connect<Event, false>(WIDGET_DESTROY, m_panel->get_id())(&MyWindow::on_panel_destroy, *this);

        parent = this;
        my_data = 0;
    }

    ~MyWindow()
    {
        cpaf::DebugReport() << "MyWindow::dtor";

        parent = NULL;
    }

    void on_create(Event &event)
    {
        cpaf::DebugReport() << "MyWindow::on_create";

        // set our content panel
        set_content_panel(m_panel);

        // create our button child
        m_btn = create_widget<MyButton>(MyButton::Initializer().parent(m_panel));

        // listen for button destruction event
        connect<Event, false>(WIDGET_DESTROY, m_btn->get_id())(&MyWindow::on_btn_destroy, *this);
    }

    void on_destroy(Event &event)
    {
        cpaf::DebugReport() << "MyWindow::on_destroy";

        // the button must exist at this point so accessing it shouldn't crash
        m_btn->get_label();
        m_btn->get_position();
        m_btn->set_size(cpaf::Size(100,100));
    }

    void on_btn_destroy(Event &event)
    {
        cpaf::DebugReport() << "MyWindow::on_btn_destroy";

        // the button must exist at this point so accessing it shouldn't crash
        m_btn->get_label();
        m_btn->get_position();
        m_btn->set_size(cpaf::Size(100,100));
    }

    void on_panel_destroy(Event &event)
    {
        cpaf::DebugReport() << "MyWindow::on_panel_destroy";
    }
};

// We need to implement that here
void MyButton::on_destroy(Event &event)
{
    cpaf::DebugReport() << "MyButton::on_destroy";
    
    // the parent widget must not be freed yet so this is ok
    parent->my_data;
}

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    create_widget<MyWindow>(
        MyWindow::Initializer().show()
        );

    return true;
}

/*
    Entry point for the application which returns an instance of the application object to use
*/
cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
