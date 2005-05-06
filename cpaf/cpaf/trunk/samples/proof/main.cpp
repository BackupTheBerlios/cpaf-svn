/*
Proof of concept demo for cpaf
*/

/*
IMPORTANT NOTE for using dll cpaf build
In order to do things like throwing across dll boundaries, and std::string cleanup
playing nice through dll boundaries, a dynamically linked run time library MUST BE USED
*/

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/exception.h>

class MyApp : public cpaf::gui::App
{
public:
    bool init();
};

bool MyApp::init()
{
    // believe it or not, these don't leak...
    cpaf::gui::Window *wnd = new cpaf::gui::Window;
    
    cpaf::gui::factory::Button fact_btn;
    cpaf::gui::Button *btn = fact_btn.label("Hello world!").parent(wnd).create();
    btn->show();

    btn->set_label("Hello World!");
    btn->set_size(cpaf::Size(300,50));
    
    wnd->set_title("Hello World!");

    cpaf::Size s(100,100);
    s = cpaf::Size(50,50) + s;

    wnd->set_size(s);
    wnd->set_position(cpaf::Point(0,0));
    wnd->show();
    btn->show();

    return true;
}

cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}




#if 0


class EventListener
{
public:
    virtual ~EventListener() { }
};

class Event
{
public:
    virtual ~Event() { }
};

class Paint : public Event
{
public:
    typedef void (EventListener::*ptr)(Paint&);
    static int id;
};

int Paint::id = 1;

class MyEventListener : public EventListener
{
public:
    void OnPaint(Paint&paint) { }
};

static void *_ptr;

template <typename T> void register_event_listener(typename T::ptr ptr)
{
    _ptr = &ptr;
}

template <typename T> void process_event(EventListener &obj, T &t)
{
    T::ptr ptr = *(static_cast<T::ptr*>(_ptr));
    (obj.*ptr)(t);
}

template <typename T, typename U> typename T::ptr cast_listener(U u)
{
    return static_cast<T::ptr>(u);
}

int main(int, char**)
{
    register_event_listener<Paint>(cast_listener<Paint>(MyEventListener::OnPaint));
    MyEventListener list;
    process_event<Paint>(list, Paint());
}

#endif
