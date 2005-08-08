// \todo Include some test cases. This is just a stub.

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/entrybox.h>
#include <cpaf/gui/textbox.h>
#include <cpaf/gui/panel.h>
#include <iostream>

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

using cpaf::gui::factory::create_widget;
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
    Panel *panel = create_widget<Panel>(Panel::Initializer());

    Window *wnd = create_widget<Window>(Window::Initializer()
        //.content_panel(panel)
        .title("Cpaf")
        .client_size(cpaf::Size(450,450))
        );

    wnd->set_content_panel(panel);

    Button::Initializer btn_init;
    EntryBox::Initializer entry_init;
    btn_init.parent(panel);
    entry_init.parent(panel);

    Button *get_text = create_widget<Button>(btn_init
        .label("Get text")
        .size(cpaf::Size(100,30))
        .position(cpaf::Point(10,10))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_text->get_id()) (&MyApp::get_text, *this);
    Button *get_selection_range = create_widget<Button>(btn_init
        .label("Get selection range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(120,10))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_selection_range->get_id()) (&MyApp::get_selection_range, *this);
    Button *get_selection_bounds = create_widget<Button>(btn_init
        .label("Get selection bounds")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(280,10))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_selection_bounds->get_id()) (&MyApp::get_selection_bounds, *this);

    Button *get_insertion_point = create_widget<Button>(btn_init
        .label("Get insertion point")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,45))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_insertion_point->get_id()) (&MyApp::get_insertion_point, *this);
    Button *get_length = create_widget<Button>(btn_init
        .label("Get length")
        .size(cpaf::Size(100,30))
        .position(cpaf::Point(170,45))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_length->get_id()) (&MyApp::get_length, *this);
    Button *toggle_read_only = create_widget<Button>(btn_init
        .label("Toggle read only")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(280,45))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, toggle_read_only->get_id()) (&MyApp::toggle_read_only, *this);


    Button *get_text_in_range = create_widget<Button>(btn_init
        .label("Get text in range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,100))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, get_text_in_range->get_id()) (&MyApp::get_text_in_range, *this);
    Button *set_selection_range = create_widget<Button>(btn_init
        .label("Set selection range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,135))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_selection_range->get_id()) (&MyApp::set_selection_range, *this);
    Button *set_selection_bounds = create_widget<Button>(btn_init
        .label("Set selection bounds")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,170))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_selection_bounds->get_id()) (&MyApp::set_selection_bounds, *this);
    Button *set_insertion_point = create_widget<Button>(btn_init
        .label("Set insertion point")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(170,100))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_insertion_point->get_id()) (&MyApp::set_insertion_point, *this);
    Button *delete_range = create_widget<Button>(btn_init
        .label("Delete range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(170,135))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, delete_range->get_id()) (&MyApp::delete_range, *this);
    Button *insert = create_widget<Button>(btn_init
        .label("Insert")
        .size(cpaf::Size(75,30))
        .position(cpaf::Point(170,170))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, insert->get_id()) (&MyApp::insert, *this);
    Button *set_max_length = create_widget<Button>(btn_init
        .label("Set max length")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,205))
        .show()
        );
    connect<Event, false>(BUTTON_CLICK, set_max_length->get_id()) (&MyApp::set_max_length, *this);

    range_begin = create_widget<EntryBox>(entry_init
        .text("3")
        .position(cpaf::Point(330,100))
        .size(cpaf::Size(50,30))
        .show()
        );
    range_end = create_widget<EntryBox>(entry_init
        .text("5")
        .position(cpaf::Point(390,100))
        .show()
        );

    insert_text = create_widget<EntryBox>(entry_init
        .text("Text to insert")
        .position(cpaf::Point(255, 170))
        .size(cpaf::Size(185,30))
        .show()
        );

    /*
        Create an EntryBox
    */
    entry = create_widget<EntryBox>(EntryBox::Initializer()
        .parent(panel)
        .text("I'm an entry box!")
        .position(cpaf::Point(10,260))
        .size(cpaf::Size(200,30))
        .show()
        );

    /*
        Create a TextBox
    */
    text = create_widget<TextBox>(TextBox::Initializer()
        .parent(panel)
        .text("I'm a multline text box!\nHere's the second line\n\nLorem ipsum dolor sit amet, sed consectetuer adipiscing elit.")
        .position(cpaf::Point(10,300))
        .size(cpaf::Size(300,130))
        .show()
        );

    wnd->show();

    return true;
}

cpaf::TextRange MyApp::get_range()
{
    cpaf::text_range_t begin, end;
    begin = atoi(range_begin->get_text().c_str());
    end = atoi(range_end->get_text().c_str());
    return cpaf::TextRange(begin, end);
}

void MyApp::get_text(Event &event)
{
    std::cout << "entry: " << entry->get_text() << "\n";
    std::cout << "text:\n" << text->get_text() << "\n\n";
}

void MyApp::get_selection_range(Event &event)
{
    cpaf::TextRange e = entry->get_selection_range();
    cpaf::TextRange t = text->get_selection_range();
    std::cout << "entry: " << e.first << " " << e.second << "\n";
    std::cout << "text: " << t.first << " " << t.second << "\n\n";
}

void MyApp::get_selection_bounds(Event &event)
{
    cpaf::TextRange e, t;
    bool e_ret = entry->get_selection_bounds(e);
    bool t_ret = text->get_selection_bounds(t);
    std::cout << "entry: " << e.first << " " << e.second << " return value: "<< e_ret << "\n";
    std::cout << "text: " << t.first << " " << t.second << " return value: " << t_ret << "\n\n";
}

void MyApp::get_insertion_point(Event &event)
{
    std::cout << "entry: " << entry->get_insertion_point() << "\n";
    std::cout << "text: " << text->get_insertion_point() << "\n\n";
}

void MyApp::get_length(Event &event)
{
    std::cout << "entry: " << entry->get_length() << "\n";
    std::cout << "text: " << text->get_length() << "\n\n";
}

void MyApp::toggle_read_only(Event &event)
{
    std::cout << "toggling read only" << "\n\n";
    entry->set_read_only(!entry->is_read_only());
    text->set_read_only(!text->is_read_only());
}

void MyApp::get_text_in_range(Event &event)
{
    std::cout << "entry: " << entry->get_text(get_range()) << "\n";
    std::cout << "text:\n" << text->get_text(get_range()) << "\n\n";
}

void MyApp::set_selection_range(Event &event)
{
    std::cout << "setting selection range" << "\n\n";
    entry->set_selection_range(get_range());
    text->set_selection_range(get_range());
}

void MyApp::set_selection_bounds(Event &event)
{
    std::cout << "setting selection bounds" << "\n\n";
    entry->set_selection_bounds(get_range());
    text->set_selection_bounds(get_range());
}

void MyApp::set_max_length(Event &event)
{
    std::cout << "setting max length" << "\n\n";
    entry->set_max_length(get_range().first);
    text->set_max_length(get_range().first);
}

void MyApp::set_insertion_point(Event &event)
{
    std::cout << "setting insertion point" << "\n\n";
    entry->set_insertion_point(get_range().first);
    text->set_insertion_point(get_range().first);
}

void MyApp::delete_range(Event &event)
{
    std::cout << "deleting range" << "\n\n";
    entry->delete_range(get_range());
    text->delete_range(get_range());
}

void MyApp::insert(Event &event)
{
    std::cout << "inserting text" << "\n\n";
    entry->insert_text(get_range().first, insert_text->get_text());
    text->insert_text(get_range().first, insert_text->get_text());
}



/*
    Entry cpaf::Point for the application which returns an instance of the application object to use
*/
cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
