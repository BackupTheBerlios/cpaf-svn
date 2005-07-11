/*
WIDGET_CREATED and WIDGET_DESTROYED event test case
*/

/*
Expected Output

MyWindow::Ctor
MyWindow::on_create
MyWindow::on_destroy
MyWindow::on_btn_destroy
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

/*
    A derived window
*/
class MyWindow : public Window
{
private:
    Button *m_btn;

public:
    MyWindow()
    {
        DBG_MSG("MyWindow::Ctor");

        connect<Event, false>(WIDGET_DESTROY, get_id())(&MyWindow::on_destroy, *this);
        connect<Event, false>(WIDGET_CREATE, get_id())(&MyWindow::on_create, *this);
    }

    void on_create(Event &event)
    {
        DBG_MSG("MyWindow::on_create");

        // create our button child
        m_btn = create_widget<Button>(Button::Initializer().parent(this));

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
