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

namespace cpaf {
    namespace win32 {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
    friend LRESULT CALLBACK widget_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    bool m_delete;

protected:
    // i need a flag saying wether or not the dtor should call DestroyWindow(m_hwnd);
    // flag is true by default. Whe dtor is called, DestroyWindow is called if the flag is true.
    // the flag is set to false before calling this. When the window procedure recieves WM_DESTROY,
    // it will delete the window object only if this flag is true. It will set it to false before the delete.

    HWND m_hwnd;
    cpaf::Size m_min_size, m_max_size;

    Widget();

    /*
        Instead of subclassing window procedures to simulate inheritance, there is only
        one window procedure, which is widget_wndproc. This function calls process_message
        which does all message processing. process_message is responsible for knowing wether or
        not to call DefWindowProc, or some other window procedure.
    */
    virtual int process_message(HWND hwnd, MSG msg, WPARAM w_param, LPARAM l_param);

public:
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
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_WIDGET_H
