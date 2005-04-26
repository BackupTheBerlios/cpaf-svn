/*
win32 version of api::Widget
*/

#ifndef CPAF_WIN32_GUI_WIDGET_H
#define CPAF_WIN32_GUI_WIDGET_H

#ifdef _MSC_VER
#pragma warning(disable: 4250) // warning C4250: 'Foo' : inherits 'Foo::foo' via dominance
#endif

#include <cpaf/win32/win.h>
#include <cpaf/defs.h>
#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
private:
    bool m_delete;

protected:
    int m_id; // widget identifier, will never change after construction
    HWND m_hwnd; // native window handle
    WNDPROC m_old_proc; // old window procedure

    cpaf::Size m_min_size, m_max_size;

    Widget(int id);

public:
    void set_old_proc(WNDPROC proc) { m_old_proc = proc; }

    /*
        Instead of subclassing window procedures to simulate inheritance, there is only
        one window procedure, which is widget_wndproc. This function calls process_message
        which does all message processing. process_message is responsible for knowing wether or
        not to call DefWindowProc, or some other window procedure.
    */
    virtual int process_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

    virtual ~Widget();

    // object interface
    virtual void set_size(const cpaf::Size &s);
    virtual void set_min_size(const cpaf::Size &s);
    virtual void set_max_size(const cpaf::Size &s);
    virtual void set_position(const cpaf::Point &p);
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size();
    virtual cpaf::Size get_max_size();
    virtual cpaf::Point get_position();

    // widget interface
    virtual void *get_handle() { return m_hwnd; }
    virtual void enable(bool e);
    virtual void show(bool show, bool focus);
    virtual bool is_enabled();
    virtual bool is_shown();
    int get_id();

protected:
    // implementation specific functions

    /*!
        Sets the text of this widget using SetWindowText
    */
    void set_window_text(const std::string &str);
    std::string get_window_text();
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_WIDGET_H
