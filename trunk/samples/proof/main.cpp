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

    void event_listener(cpaf::event::Event &e)
    {
        DBG_MSG("event_listener");
    }

    void event_listener_2(cpaf::event::Event &e)
    {
        DBG_MSG("event_listener_2");
    }
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

        This window will be visible without calling wnd->show().
    */
    cpaf::gui::Window *wnd = cpaf::gui::Window::Factory()
        .title("Cpaf")
        .show()
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

    // events testing
    get_events_manager().create_event_chain<cpaf::event::Event>(cpaf::event::OBJECT_ID_ANY, 1).connect(*this, &MyApp::event_listener).connect(*this, &MyApp::event_listener_2);
    get_events_manager().connect_after<cpaf::event::Event>(1, 1, *this, &MyApp::event_listener);
    cpaf::event::Event event(1);
    get_events_manager().send_event(2, event);

    return true;
}

/*
    Entry point for the application which returns an instance of the application object to use
*/
cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
