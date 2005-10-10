// \todo Include some test cases. This is just a stub.

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/entrybox.h>
#include <cpaf/gui/textbox.h>
#include <cpaf/gui/panel.h>
#include <cpaf/gui/window.h>
#include <cpaf/debug.h>
#include <cpaf/gui/gridbaglayout.h>

#include <sstream>

using namespace cpaf::event;
using namespace cpaf::gui;

/*
    Our derived application class
*/
class MyApp : public App
{
public:
    boost::shared_ptr<TextBox> text;
    boost::shared_ptr<EntryBox> entry;
    boost::shared_ptr<EntryBox> range_begin, range_end, insert_text;
    
    bool init();
    
    void get_text(Event &event);
    void get_selection_range(Event &event);
    void get_selection_bounds(Event &event);
    void get_insertion_point(Event &event);
    void get_length(Event &event);
    void toggle_read_only(Event &event);
    void get_text_in_range(Event &event);
    void set_selection_range(Event &event);
    void set_selection_bounds(Event &event);
    void set_max_length(Event &event);
    void set_insertion_point(Event &event);
    void delete_range(Event &event);
    void insert(Event &event);

private:
    cpaf::TextRange get_range();
};

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
    boost::shared_ptr<cpaf::gui::GridBagLayout> gblm_outer(new cpaf::gui::GridBagLayout);
    boost::shared_ptr<Panel> panel_outer =Panel::create(Panel::Initializer().layout_manager(gblm_outer));

    // use a second panel with another GBLM to simulate column spanning until I implement it
    boost::shared_ptr<cpaf::gui::GridBagLayout> gblm(new cpaf::gui::GridBagLayout);
    boost::shared_ptr<Panel> panel_inner =Panel::create(Panel::Initializer().parent(panel_outer).show().layout_manager(gblm));

    // work around for incomplete GBLM implementation (can't calculate gblm min size)
    panel_inner->set_min_size(cpaf::Size(0, 134));

    // add the inner panel to the outer panel's gblm
    gblm_outer->add(panel_inner, cpaf::gui::GridBagLayoutInfo().expand_both().position(0,0));

    boost::shared_ptr<Window> wnd =Window::create(Window::Initializer()
        .content_panel(panel_outer)
        .title("Cpaf")
        .client_size(cpaf::Size(600,450))
        );

    Button::Initializer btn_init;
    EntryBox::Initializer entry_init;
    btn_init.parent(panel_inner).min_size(cpaf::Size(100, 30));
    entry_init.parent(panel_inner);

    boost::shared_ptr<Button> get_text =Button::create(btn_init
        .label("Get text")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_text->get_id()) (&MyApp::get_text, *this);
    boost::shared_ptr<Button> get_selection_range =Button::create(btn_init
        .label("Get selection range")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_selection_range->get_id()) (&MyApp::get_selection_range, *this);
    boost::shared_ptr<Button> get_selection_bounds =Button::create(btn_init
        .label("Get selection bounds")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_selection_bounds->get_id()) (&MyApp::get_selection_bounds, *this);

    boost::shared_ptr<Button> get_insertion_point =Button::create(btn_init
        .label("Get insertion point")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_insertion_point->get_id()) (&MyApp::get_insertion_point, *this);
    boost::shared_ptr<Button> get_length =Button::create(btn_init
        .label("Get length")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_length->get_id()) (&MyApp::get_length, *this);
    boost::shared_ptr<Button> toggle_read_only =Button::create(btn_init
        .label("Toggle read only")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, toggle_read_only->get_id()) (&MyApp::toggle_read_only, *this);


    boost::shared_ptr<Button> get_text_in_range =Button::create(btn_init
        .label("Get text in range")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_text_in_range->get_id()) (&MyApp::get_text_in_range, *this);
    boost::shared_ptr<Button> set_selection_range =Button::create(btn_init
        .label("Set selection range")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_selection_range->get_id()) (&MyApp::set_selection_range, *this);
    boost::shared_ptr<Button> set_selection_bounds =Button::create(btn_init
        .label("Set selection bounds")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_selection_bounds->get_id()) (&MyApp::set_selection_bounds, *this);
    boost::shared_ptr<Button> set_insertion_point =Button::create(btn_init
        .label("Set insertion point")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_insertion_point->get_id()) (&MyApp::set_insertion_point, *this);
    boost::shared_ptr<Button> delete_range =Button::create(btn_init
        .label("Delete range")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, delete_range->get_id()) (&MyApp::delete_range, *this);
    boost::shared_ptr<Button> insert =Button::create(btn_init
        .label("Insert")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, insert->get_id()) (&MyApp::insert, *this);
    boost::shared_ptr<Button> set_max_length =Button::create(btn_init
        .label("Set max length")
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_max_length->get_id()) (&MyApp::set_max_length, *this);

    range_begin = EntryBox::create(entry_init
        .text("3")
        .min_size(cpaf::Size(50,30))
        .show()
        );
    range_end = EntryBox::create(entry_init
        .text("5")
        .show()
        );

    insert_text = EntryBox::create(entry_init
        .text("Text to insert")
        .min_size(cpaf::Size(0, 30))
        .show()
        );

    /*
        Create an EntryBox
    */
    entry = EntryBox::create(EntryBox::Initializer()
        .parent(panel_outer)
        .text("I'm an entry box!")
        .min_size(cpaf::Size(0,30))
        .show()
        );

    /*
        Create a TextBox
    */
    text = TextBox::create(TextBox::Initializer()
        .parent(panel_outer)
        .text("I'm a multline text box!\nHere's the second line\nLorem ipsum dolor sit amet, sed consectetuer adipiscing elit.")
        .min_size(cpaf::Size(0,30))
        .show()
        );

    // add things to the GBLM
    cpaf::gui::GridBagLayoutInfo info;

    info.expand_horizontal();

    gblm->add(get_text, info.position(0,0));
    gblm->add(get_selection_range, info.position(1, 0));
    gblm->add(get_selection_bounds, info.position(2, 0));
    gblm->add(get_insertion_point, info.position(3, 0));
    
    gblm->add(get_length, info.position(0, 1));
    gblm->add(toggle_read_only, info.position(1, 1));
    gblm->add(get_text_in_range, info.position(2, 1));
    gblm->add(set_selection_range, info.position(3, 1));

    gblm->add(set_selection_bounds, info.position(0, 2));
    gblm->add(set_insertion_point, info.position(1, 2));
    gblm->add(delete_range, info.position(2, 2));
    gblm->add(insert, info.position(3, 2));

    gblm->add(set_max_length, info.position(0, 3));
    gblm->add(range_begin, info.position(1, 3));
    gblm->add(range_end, info.position(2, 3));
    gblm->add(insert_text, info.position(3, 3));

    gblm->set_gap(4);
    gblm->set_row_weight(0, 0).set_row_weight(1, 0).set_row_weight(2, 0)
        .set_row_weight(3, 0).set_row_weight(4, 0);

    gblm_outer->add(entry, info.position(0, 1));
    gblm_outer->add(text, info.position(0, 2).expand_both());

    gblm_outer->set_gap(4).set_margins(4);
    gblm_outer->set_row_weight(0, 0).set_row_weight(1,0);

    wnd->show();

    return true;
}

cpaf::TextRange MyApp::get_range()
{
    cpaf::text_range_t begin = 0, end = 0;

    std::stringstream ss;

    // begin
    ss.str(range_begin->get_text());
    if( ss.str() == "END" )
        begin = cpaf::TextRange::END;
    else
        ss >> begin;

    ss.clear();

    // end
    ss.str(range_end->get_text());
    if( ss.str() == "END" )
        end = cpaf::TextRange::END;
    else
        ss >> end;

    return cpaf::TextRange(begin, end);
}

void MyApp::get_text(Event &event)
{
    cpaf::DebugReport() << "Get Text:";
    cpaf::DebugReport() << "entry:\t" << entry->get_text();
    cpaf::DebugReport() << "text:\n" << text->get_text() << "\n";
}

void MyApp::get_selection_range(Event &event)
{
    cpaf::TextRange e = entry->get_selection_range();
    cpaf::TextRange t = text->get_selection_range();
    cpaf::DebugReport() << "Get Selection Range:";
    cpaf::DebugReport() << "entry:\t" << e.first << " " << e.second;
    cpaf::DebugReport() << "text:\t" << t.first << " " << t.second << "\n";
}

void MyApp::get_selection_bounds(Event &event)
{
    cpaf::TextRange e, t;
    bool e_ret = entry->get_selection_bounds(e);
    bool t_ret = text->get_selection_bounds(t);
    cpaf::DebugReport() << "Get Selection Bounds:";
    cpaf::DebugReport() << "entry:\t" << e.first << " " << e.second << " return value: "<< e_ret;
    cpaf::DebugReport() << "text:\t" << t.first << " " << t.second << " return value: " << t_ret << "\n";
}

void MyApp::get_insertion_point(Event &event)
{
    cpaf::DebugReport() << "Get Insertion Point:";
    cpaf::DebugReport() << "entry:\t" << entry->get_insertion_point();
    cpaf::DebugReport() << "text:\t" << text->get_insertion_point() << "\n";
}

void MyApp::get_length(Event &event)
{
    cpaf::DebugReport() << "Get Length";
    cpaf::DebugReport() << "entry:\t" << entry->get_length();
    cpaf::DebugReport() << "text:\t" << text->get_length() << "\n";
}

void MyApp::toggle_read_only(Event &event)
{
    cpaf::DebugReport() << "Toggle read only" << "\n";
    entry->set_read_only(!entry->is_read_only());
    text->set_read_only(!text->is_read_only());
}

void MyApp::get_text_in_range(Event &event)
{
    cpaf::DebugReport() << "Get Text In Range:";
    cpaf::DebugReport() << "entry:\t" << entry->get_text(get_range());
    cpaf::DebugReport() << "text:\t" << text->get_text(get_range()) << "\n";
}

void MyApp::set_selection_range(Event &event)
{
    cpaf::DebugReport() << "Set Selection Range" << "\n";
    entry->set_selection_range(get_range());
    text->set_selection_range(get_range());
}

void MyApp::set_selection_bounds(Event &event)
{
    cpaf::DebugReport() << "Set Selection Bounds" << "\n";
    entry->set_selection_bounds(get_range());
    text->set_selection_bounds(get_range());
}

void MyApp::set_max_length(Event &event)
{
    cpaf::DebugReport() << "Set Max Length" << "\n";
    entry->set_max_length(get_range().first);
    text->set_max_length(get_range().first);
}

void MyApp::set_insertion_point(Event &event)
{
    cpaf::DebugReport() << "Set Isertion Point" << "\n";
    entry->set_insertion_point(get_range().first);
    text->set_insertion_point(get_range().first);
}

void MyApp::delete_range(Event &event)
{
    cpaf::DebugReport() << "Delete Range" << "\n";
    entry->delete_range(get_range());
    text->delete_range(get_range());
}

void MyApp::insert(Event &event)
{
    cpaf::DebugReport() << "Insert Text" << "\n";
    entry->insert_text(insert_text->get_text());
    text->insert_text(insert_text->get_text());
}

/*
    Entry cpaf::Point for the application which returns an instance of the application object to use
*/
cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
