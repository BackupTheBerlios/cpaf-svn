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
    TextBox *text;
    EntryBox *entry;
    EntryBox *range_begin, *range_end, *insert_text;
    
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
    cpaf::gui::GridBagLayout *gblm;
    Panel *panel = Panel::create(Panel::Initializer().layout_manager(gblm = new cpaf::gui::GridBagLayout));


    Window *wnd = Window::create(Window::Initializer()
        //.content_panel(panel)
        .title("Cpaf")
        .client_size(cpaf::Size(450,450))
        );

    wnd->set_content_panel(panel);

    Button::Initializer btn_init;
    EntryBox::Initializer entry_init;
    btn_init.parent(panel);
    entry_init.parent(panel);

    Button *get_text = Button::create(btn_init
        .label("Get text")
        .size(cpaf::Size(100,30))
        .position(cpaf::Point(10,10))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_text->get_id()) (&MyApp::get_text, *this);
    Button *get_selection_range = Button::create(btn_init
        .label("Get selection range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(120,10))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_selection_range->get_id()) (&MyApp::get_selection_range, *this);
    Button *get_selection_bounds = Button::create(btn_init
        .label("Get selection bounds")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(280,10))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_selection_bounds->get_id()) (&MyApp::get_selection_bounds, *this);

    Button *get_insertion_point = Button::create(btn_init
        .label("Get insertion point")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,45))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_insertion_point->get_id()) (&MyApp::get_insertion_point, *this);
    Button *get_length = Button::create(btn_init
        .label("Get length")
        .size(cpaf::Size(100,30))
        .position(cpaf::Point(170,45))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_length->get_id()) (&MyApp::get_length, *this);
    Button *toggle_read_only = Button::create(btn_init
        .label("Toggle read only")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(280,45))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, toggle_read_only->get_id()) (&MyApp::toggle_read_only, *this);


    Button *get_text_in_range = Button::create(btn_init
        .label("Get text in range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,100))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_text_in_range->get_id()) (&MyApp::get_text_in_range, *this);
    Button *set_selection_range = Button::create(btn_init
        .label("Set selection range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,135))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_selection_range->get_id()) (&MyApp::set_selection_range, *this);
    Button *set_selection_bounds = Button::create(btn_init
        .label("Set selection bounds")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,170))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_selection_bounds->get_id()) (&MyApp::set_selection_bounds, *this);
    Button *set_insertion_point = Button::create(btn_init
        .label("Set insertion point")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(170,100))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_insertion_point->get_id()) (&MyApp::set_insertion_point, *this);
    Button *delete_range = Button::create(btn_init
        .label("Delete range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(170,135))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, delete_range->get_id()) (&MyApp::delete_range, *this);
    Button *insert = Button::create(btn_init
        .label("Insert")
        .size(cpaf::Size(75,30))
        .position(cpaf::Point(170,170))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, insert->get_id()) (&MyApp::insert, *this);
    Button *set_max_length = Button::create(btn_init
        .label("Set max length")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,205))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_max_length->get_id()) (&MyApp::set_max_length, *this);

    range_begin = EntryBox::create(entry_init
        .text("3")
        .position(cpaf::Point(330,100))
        .size(cpaf::Size(50,30))
        .show()
        );
    range_end = EntryBox::create(entry_init
        .text("5")
        .position(cpaf::Point(390,100))
        .show()
        );

    insert_text = EntryBox::create(entry_init
        .text("Text to insert")
        .position(cpaf::Point(255, 170))
        .size(cpaf::Size(185,30))
        .show()
        );

    /*
        Create an EntryBox
    */
    entry = EntryBox::create(EntryBox::Initializer()
        .parent(panel)
        .text("I'm an entry box!")
        .position(cpaf::Point(10,260))
        .size(cpaf::Size(200,30))
        .show()
        );

    /*
        Create a TextBox
    */
    text = TextBox::create(TextBox::Initializer()
        .parent(panel)
        .text("I'm a multline text box!\nHere's the second line\nLorem ipsum dolor sit amet, sed consectetuer adipiscing elit.")
        .position(cpaf::Point(10,300))
        .size(cpaf::Size(300,130))
        .show()
        );

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
