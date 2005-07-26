// \todo Include some test cases. This is just a stub.

#include <cpaf/main.h>
#include <cpaf/gui/app.h>
#include <cpaf/gui/window.h>
#include <cpaf/gui/button.h>
#include <cpaf/gui/entrybox.h>
#include <cpaf/gui/textbox.h>

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
    bool init();
};

/*
    Initialization function for our application class
*/
bool MyApp::init()
{
   Window *wnd = create_widget<Window>(
       Window::Initializer()
        .title("Cpaf")
        .client_size(cpaf::Size(450,450))
        );

    Button::Initializer btn_init;
    EntryBox::Initializer entry_init;
    btn_init.parent(wnd);
    entry_init.parent(wnd);

    Button *get_text = create_widget<Button>(btn_init
        .label("Get text")
        .size(cpaf::Size(100,30))
        .position(cpaf::Point(10,10))
        .show()
        );
    Button *get_selection_range = create_widget<Button>(btn_init
        .label("Get selection range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(120,10))
        .show()
        );
    Button *get_selection_bounds = create_widget<Button>(btn_init
        .label("Get selection bounds")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(280,10))
        .show()
        );

    Button *get_insertion_point = create_widget<Button>(btn_init
        .label("Get insertion point")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,45))
        .show()
        );
    Button *get_length = create_widget<Button>(btn_init
        .label("Get length")
        .size(cpaf::Size(100,30))
        .position(cpaf::Point(170,45))
        .show()
        );
    Button *toggle_read_only = create_widget<Button>(btn_init
        .label("Toggle read only")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(280,45))
        .show()
        );


    Button *get_text_in_range = create_widget<Button>(btn_init
        .label("Get text in range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,100))
        .show()
        );
    Button *set_selection_range = create_widget<Button>(btn_init
        .label("Set selection range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,135))
        .show()
        );
    Button *set_selection_bounds = create_widget<Button>(btn_init
        .label("Set selection bounds")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,170))
        .show()
        );
    Button *set_insertion_point = create_widget<Button>(btn_init
        .label("Set insertion point")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(170,100))
        .show()
        );
    Button *delete_range = create_widget<Button>(btn_init
        .label("Delete range")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(170,135))
        .show()
        );
    Button *insert = create_widget<Button>(btn_init
        .label("Insert")
        .size(cpaf::Size(75,30))
        .position(cpaf::Point(170,170))
        .show()
        );
    Button *set_max_length = create_widget<Button>(btn_init
        .label("Set max length")
        .size(cpaf::Size(150,30))
        .position(cpaf::Point(10,205))
        .show()
        );

    EntryBox *range_begin = create_widget<EntryBox>(entry_init
        .text("3")
        .position(cpaf::Point(330,100))
        .size(cpaf::Size(50,30))
        .show()
        );
    EntryBox *range_end = create_widget<EntryBox>(entry_init
        .text("5")
        .position(cpaf::Point(390,100))
        .show()
        );

    EntryBox *insert_text = create_widget<EntryBox>(entry_init
        .text("Text to insert")
        .position(cpaf::Point(255, 170))
        .size(cpaf::Size(185,30))
        .show()
        );

    /*
        Create an EntryBox
    */
    EntryBox *entry = create_widget<EntryBox>(EntryBox::Initializer()
        .parent(wnd)
        .text("I'm an entry box!")
        .position(cpaf::Point(10,260))
        .size(cpaf::Size(200,30))
        .show()
        );

    /*
        Create a TextBox
    */
    TextBox *text = create_widget<TextBox>(TextBox::Initializer()
        .parent(wnd)
        .text("I'm a multline text box!\nHere's the second line\n\nLorem ipsum dolor sit amet, sed consectetuer adipiscing elit.")
        .position(cpaf::Point(10,300))
        .size(cpaf::Size(300,130))
        .show()
        );

    // Show the window last for proper visual appearance
    wnd->show();

    return true;
}

/*
    Entry point for the application which returns an instance of the application object to use
*/
cpaf::App *cpaf::main(const cpaf::App::cmd_line &cmd)
{
    return new MyApp;
}
