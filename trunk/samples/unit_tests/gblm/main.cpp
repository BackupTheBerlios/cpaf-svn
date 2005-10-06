/*
    Test application for the grid bag layout manager
*/

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/panel.h>
#include <cpaf/gui/gridbaglayout.h>

using namespace cpaf::gui;

class MyApp : public cpaf::gui::App
{
    bool init();
};

bool MyApp::init()
{
    boost::shared_ptr<GridBagLayout> gblm(new GridBagLayout);
    boost::shared_ptr<Panel> panel = Panel::create(Panel::Initializer().layout_manager(gblm).show());

    GridBagLayoutInfo info;
    info.padding(5);

    Button::Initializer btn_init;
    btn_init.parent(panel).min_size(cpaf::Size(25,25)).show();

    gblm->add(Button::create(btn_init.label("1")),
        info.position(1,1).align_top().align_right().expand_both());
    gblm->add(Button::create(btn_init.label("2")),
        info.position(2,1).align_top().align_left().expand_both());
    gblm->add(Button::create(btn_init.label("3")),
        info.position(3,1).align_bottom().align_right().expand_both());
    gblm->add(Button::create(btn_init.label("4")),
        info. position(4,1).align_bottom().align_left().expand_both());

    gblm->add(Button::create(btn_init.label("5")),
        info.position(1,2).expand_both());
    gblm->add(Button::create(btn_init.label("6")),
        info.position(2,2).expand_horizontal().align_center_vertical());
    gblm->add(Button::create(btn_init.label("7")),
        info.position(3,2).expand_vertical().align_center_horizontal());
    gblm->add(Button::create(btn_init.label("8")),
        info.position(4,2).align_center().expand_both());

    gblm->add(Button::create(btn_init.label("9")),
        info.position(1,3).expand_both());
    gblm->add(Button::create(btn_init.label("10")),
        info.position(2,3));
    gblm->add(Button::create(btn_init.label("11")),
        info.position(3,3));
    gblm->add(Button::create(btn_init.label("12")),
        info.position(4,3));

    gblm->set_gap(10).set_row_weight(1,0).set_row_weight(3,0)
        .set_column_weight(1,0).set_column_weight(3,2);
    Window::create(Window::Initializer().content_panel(panel).show());

    return true;
}

cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
