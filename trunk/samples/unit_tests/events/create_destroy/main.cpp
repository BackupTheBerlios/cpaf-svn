/*!
    \brief WIDGET_CREATED, WIDGET_DESTROYED and object deallocation test case
*/

/*
Expected Output

MyWindow::MyWindow
MyWindow::WIDGET_CREATE
MyPanel::MyPanel
MyPanel::WIDGET_CREATE
MyButton::MyButton
MyButton::WIDGET_CREATE
MyWindow::WIDGET_DESTROY
MyPanel::WIDGET_DESTROY
MyButton::WIDGET_DESTROY
MyButton::~MyButton
MyPanel::~MyPanel
MyWindow::~MyWindow
create_destroy.exe has exited with code 0 (0x0).
*/

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/textbox.h>
#include <cpaf/gui/panel.h>
#include <cpaf/gui/gridbaglayout.h>

#include <cpaf/debug.h>

using namespace cpaf::gui;
using namespace cpaf::event;

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
    static boost::shared_ptr<MyButton> create(const Initializer &initializer)
    {
        MyButton *wrapper = new MyButton;
        return boost::dynamic_pointer_cast<MyButton>(wrapper->initialize(initializer));
    }

protected:
    MyButton()
    {
        cpaf::DebugReport() << "MyButton::MyButton";
        
        connect<Event, false>(WIDGET_DESTROY, get_id())(&MyButton::on_destroy, *this);
        connect<Event, false>(WIDGET_CREATE, get_id())(&MyButton::on_create, *this);
    }

    ~MyButton()
    {
        cpaf::DebugReport() << "MyButton::~MyButton";
    }

    void on_create(Event &event)
    {
        cpaf::DebugReport() << "MyButton::WIDGET_CREATE";
    }

    void on_destroy(Event &event);
};

/*
    Derived panel
*/
class MyPanel : public Panel
{
public:
    static boost::shared_ptr<MyPanel> create(const Initializer &initializer)
    {
        MyPanel *wrapper = new MyPanel;
        return boost::dynamic_pointer_cast<MyPanel>(wrapper->initialize(initializer));
    }

protected:
    MyPanel()
    {
        cpaf::DebugReport() << "MyPanel::MyPanel";

        connect<Event, false>(WIDGET_CREATE, get_id()) (&MyPanel::on_create, *this);
    }
    ~MyPanel()
    {
        cpaf::DebugReport() << "MyPanel::~MyPanel";
    }

    void on_create(Event &event)
    {
        cpaf::DebugReport() << "MyPanel::WIDGET_CREATE";
    }
};

/*
    A derived window
*/
class MyWindow : public Window
{
private:
    boost::shared_ptr<MyButton> m_btn;

public:
    void *my_data;

    static boost::shared_ptr<MyWindow> create(const Initializer &initializer)
    {
        MyWindow *wrapper = new MyWindow;
        return boost::dynamic_pointer_cast<MyWindow>(wrapper->initialize(initializer));
    }

protected:
    MyWindow()
    {
        cpaf::DebugReport() << "MyWindow::MyWindow";

        // connect events
        connect<Event, false>(WIDGET_DESTROY, get_id())(&MyWindow::on_destroy, *this);
        connect<Event, false>(WIDGET_CREATE, get_id())(&MyWindow::on_create, *this);

        parent = this;
        my_data = 0;
    }

    ~MyWindow()
    {
        cpaf::DebugReport() << "MyWindow::~MyWindow";

        parent = 0;
    }

    void on_create(Event &event)
    {
        cpaf::DebugReport() << "MyWindow::WIDGET_CREATE";

        // create the root panel
        boost::shared_ptr<Panel> panel = MyPanel::create(Panel::Initializer()
            .layout_manager(boost::shared_ptr<cpaf::gui::LayoutManager>(new cpaf::gui::GridBagLayout)));
        connect<Event, false>(WIDGET_DESTROY, panel->get_id())(&MyWindow::on_panel_destroy, *this);

        // set our content panel
        set_content_panel(panel);

        // create our button child
        m_btn = MyButton::create(MyButton::Initializer().parent(panel));

        // listen for button destruction event
        connect<Event, false>(WIDGET_DESTROY, m_btn->get_id())(&MyWindow::on_btn_destroy, *this);
    }

    void on_destroy(Event &event)
    {
        cpaf::DebugReport() << "MyWindow::WIDGET_DESTROY";

        // the button must exist at this point so accessing it shouldn't crash
        m_btn->get_label();
        m_btn->get_position();
    }

    void on_btn_destroy(Event &event)
    {
        cpaf::DebugReport() << "MyButton::WIDGET_DESTROY";

        // the button must exist at this point so accessing it shouldn't crash
        m_btn->get_label();
        m_btn->get_position();

        /*
            Release the reference to the button to retain desired deallocation order.
            If we held onto this resource, object deallocation order would change.
            You do not need to release your shared pointers in your own code, we
            do it in this sample to make sure the object deallocation order that the
            api gaurentees is being respected on all platforms
        */
        m_btn.reset();
    }

    void on_panel_destroy(Event &event)
    {
        cpaf::DebugReport() << "MyPanel::WIDGET_DESTROY";
    }
};

// We need to implement that here
void MyButton::on_destroy(Event &event)
{
    // the parent widget must not be freed yet so this is ok
    parent->my_data;
}

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    MyWindow::create(MyWindow::Initializer()
        .show()
        )->destroy();

    return true;
}

/*
    Entry point for the application which returns an instance of the application object to use
*/
cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
