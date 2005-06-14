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

/*
    Our derived application class
*/
class MyApp : public cpaf::gui::App
{
public:
    bool init();
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

        using namespace cpaf::event;
        connect<cpaf::event::Event, false>(cpaf::event::widget_create, get_id(), *this, &MyButton::on_create).connect(*this, &MyButton::on_create);
        connect<cpaf::event::Event, false>(cpaf::event::widget_destroy, get_id(), *this, &MyButton::on_destroy);
    }

    void on_create(cpaf::event::Event &event)
    {
        DBG_MSG("MyButton::on_create");
    }

    void on_destroy(cpaf::event::Event &event)
    {
        DBG_MSG("MyButton::on_destroy");
    }
};

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    /*
        Construct a window with a default position and a default size.
        The factory object initializes its members to specify "default values"
        which instruct an implementation to let the system determine an appropriate
        size and position. If the system is not capable of doing this, the implementation
        must chose reasonable values.

        This window will be visible without calling wnd->show() if .show() isn't commented out below.
    */
    cpaf::gui::Window *wnd = cpaf::gui::Window::Factory()
        .title("Cpaf")
        .client_size(cpaf::Size(400,400))
        //.show()
        .create();

    /*
        Create some explicitly sized and positioned buttons which are initially visible.
        One of these buttons is a derived button.
    */
    cpaf::gui::Button::Factory fact_btn;
    cpaf::gui::Button *btn = fact_btn
        .label("Hello world!")
        .parent(wnd)
        .size(cpaf::Size(100,20))
        .position(cpaf::Point(50,50))
        .show()
        .create();
    MyButton *my_btn = fact_btn
        .label("MyButton!")
        .position(cpaf::Point(100,100))
        .show()
        .create<MyButton>();

    // Show the toplevel last for proper visual appearance
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
