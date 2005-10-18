/*
    Test application for the grid bag layout manager
*/

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/panel.h>
#include <cpaf/gui/gridbaglayout.h>
#include <cpaf/flags.h>

using namespace cpaf::gui;
using namespace cpaf::flags;

class MyApp : public cpaf::gui::App
{
    bool init();
};

bool MyApp::init()
{
    boost::shared_ptr<GridBagLayout> gblm(new GridBagLayout);
    boost::shared_ptr<Panel> panel = Panel::create(Panel::Initializer().layout_manager(gblm).show());

    GridBagLayoutInfo info;

    Button::Initializer btn_init;
    btn_init.parent(panel).min_size(cpaf::Size(25,25)).show();

    gblm->add(Button::create(btn_init.label("1")),
        info.position(1,1));
    gblm->add(Button::create(btn_init.label("2")),
        info.position(2,1).flags(EXPAND_BOTH));
    gblm->add(Button::create(btn_init.label("3")),
        info.position(3,1));
    gblm->add(Button::create(btn_init.label("4")),
        info. position(4,1));

    gblm->add(Button::create(btn_init.label("5")),
        info.position(1,2));
    gblm->add(Button::create(btn_init.label("6")),
        info.position(2,2).flags(EXPAND_HORIZONTAL | ALIGN_CENTER_VERTICAL));
    gblm->add(Button::create(btn_init.label("7")),
        info.position(3,2).flags(EXPAND_VERTICAL | ALIGN_CENTER_HORIZONTAL).row_span(2));

    /*
        Button 8 is special. It is expanded in both directions but also has a minimal
        size, with centered alignment flags. What this means is that so long as the button
        is given a size less than its maximum, it will be expanded to fill up all of
        the space available to it. But, if there is more space available than the maximum size,
        the button will be centered with a size equal to its maximum.
    */
    gblm->add(Button::create(btn_init.label("8").max_size(cpaf::Size(100,100))),
        info.position(4,2).flags(ALIGN_CENTER | EXPAND_BOTH).row_span(1));

    gblm->add(Button::create(btn_init.label("9").max_size(cpaf::Size(0,0))),
        info.position(1,3));
    gblm->add(Button::create(btn_init.label("10")),
        info.position(2,3));
    gblm->add(Button::create(btn_init.label("12")),
        info.position(4,3));

    gblm->add(Button::create(btn_init.label("13")),
        info.position(1,4).col_span(2));
    gblm->add(Button::create(btn_init.label("14")),
        info.position(3,4));

    gblm->set_gap(10).set_margins(5).set_row_weight(1,0).set_row_weight(3,0)
        .set_column_weight(1,0).set_column_weight(3,2);

    Window::create(Window::Initializer().content_panel(panel).show());

    return true;
}

cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
