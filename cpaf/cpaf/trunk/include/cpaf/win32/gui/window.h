/*
win32 version of api::Window
*/

#ifndef _CPAF_WIN32_GUI_WINDOW_H_
#define _CPAF_WIN32_GUI_WINDOW_H_

#include <cpaf/win32/win.h>

#include <cpaf/api/gui/window.h>
#include <cpaf/defs.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Window : public cpaf::api::gui::Window
{
    friend LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    HWND m_hwnd;
    cpaf::Size m_min_size, m_max_size;

public:
    Window();

    // sizeable interface
    virtual void set_size(cpaf::Size s);
    virtual void set_min_size(cpaf::Size s);
    virtual void set_max_size(cpaf::Size s);
    virtual void set_position(cpaf::Point p);
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size();
    virtual cpaf::Size get_max_size();
    virtual cpaf::Point get_position();

    // widget interface
    virtual int get_handle() { return 0; }
    virtual void enable(bool e);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled();
    virtual bool is_shown();

    // toplevel interface
    virtual void set_title(const std::string &t){ }
    virtual std::string get_title();

    virtual void set_client_size(cpaf::Size s) { }
    virtual cpaf::Size get_client_size() { return cpaf::Size(); }
    virtual cpaf::Point get_client_position() { return cpaf::Point(); }
};

        } // gui
    } // win32
} // cpaf

#endif // _CPAF_WIN32_GUI_WINDOW_H_
