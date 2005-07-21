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

#include <cpaf/exception.h>

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

cpaf::gui::Window *parent;

/*
    A derived button
*/
class MyButton : public Button
{
public:
    MyButton()
    {
        DBG_MSG("MyButton::ctor");
        
        connect<Event, false>(WIDGET_DESTROY, get_id())(&MyButton::on_destroy, *this);
        connect<Event, false>(WIDGET_CREATE, get_id())(&MyButton::on_create, *this);
    }

    ~MyButton()
    {
        DBG_MSG("MyButton::dtor");
    }

    void on_create(Event &event)
    {
        DBG_MSG("MyButton::on_create");
    }

    void on_destroy(Event &event)
    {
        DBG_MSG("MyButton::on_destroy");
    }
};

/*
    A derived window
*/
class MyWindow : public Window
{
private:
    MyButton *m_btn;

public:
    MyWindow()
    {
        DBG_MSG("MyWindow::ctor");

        connect<Event, false>(WIDGET_DESTROY, get_id())(&MyWindow::on_destroy, *this);
        connect<Event, false>(WIDGET_CREATE, get_id())(&MyWindow::on_create, *this);

        parent = this;
    }

    ~MyWindow()
    {
        DBG_MSG("MyWindow::dtor");

        parent = NULL;
    }

    void on_create(Event &event)
    {
        DBG_MSG("MyWindow::on_create");

        // create our button child
        m_btn = create_widget<MyButton>(MyButton::Initializer().parent(this));

        // listen for button destruction event
        connect<Event, false>(WIDGET_DESTROY, m_btn->get_id())(&MyWindow::on_btn_destroy, *this);
    }

    void on_destroy(Event &event)
    {
        DBG_MSG("MyWindow::on_destroy");

        // the button must exist at this point so accessing it shouldn't crash
        m_btn->get_label();
        m_btn->get_position();
        m_btn->set_size(cpaf::Size(100,100));
    }

    void on_btn_destroy(Event &event)
    {
        DBG_MSG("MyWindow::on_btn_destroy");

        // the button must exist at this point so accessing it shouldn't crash
        m_btn->get_label();
        m_btn->get_position();
        m_btn->set_size(cpaf::Size(100,100));
    }
};

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
