/*
win32 version of api::Window
*/

#include <cpaf/win32/win.h>

#include <cpaf/api/gui/window.h>
#include <cpaf/defs.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Window : public cpaf::api::gui::Window
{
private:
    HWND m_hwnd;

public:
    Window();

    // sizeable interface
    virtual void set_size(cpaf::Size s);
    virtual void set_min_size(cpaf::Size s) { }
    virtual void set_max_size(cpaf::Size s) { }
    virtual void set_position(cpaf::Point p) { }
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size() { return cpaf::Size(); }
    virtual cpaf::Size get_max_size() { return cpaf::Size(); }
    virtual cpaf::Point get_position() { return cpaf::Point(); }

    // widget interface
    virtual int get_handle() { return 0; }
    virtual void enable(bool e) { }
    virtual void show(bool s) { }
    virtual bool is_enabled() { return 0; }
    virtual bool is_shown() { return 0; }

    // toplevel interface
    virtual void set_title(const std::string &t){ }
    virtual std::string get_title();
};

        } // gui
    } // win32
} // cpaf
