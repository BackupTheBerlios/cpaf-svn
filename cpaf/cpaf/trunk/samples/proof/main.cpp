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
    cpaf::gui::Button *btn = new cpaf::gui::Button((cpaf::gui::Widget*)wnd);
    btn->set_label("Hello World!");
    btn->set_size(cpaf::Size(300,50));
    wnd->show();
    wnd->set_title("Hello World!");
    btn->show();

    return true;
}

#include <cpaf/win32/gui/button.h>


class api_Object
{
public:
    virtual ~api_Object() { }
};

cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
