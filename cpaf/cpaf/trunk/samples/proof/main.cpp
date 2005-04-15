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

class MyApp : public cpaf::gui::App
{
public:
    bool init();
};

bool MyApp::init()
{
    // memleaks, yea yea
    cpaf::gui::Window *wnd = new cpaf::gui::Window;
    cpaf::gui::Button *btn = new cpaf::gui::Button(wnd);
    btn->set_label("Hello World!");
    wnd->show();
    wnd->set_title("Hello World!");
    btn->show();
    //delete wnd;

    return true;
}

cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
