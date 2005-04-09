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

class MyApp : public cpaf::gui::App
{
public:
    bool init();
};

bool MyApp::init()
{
    // memleaks, yea yea
    cpaf::gui::Window *wnd = new cpaf::gui::Window;
    wnd->set_title("Hello world!");
    wnd->show(true, false);

    return true;
}

cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
