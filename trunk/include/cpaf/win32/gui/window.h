/*!
    \file include/cpaf/win32/window.h
    \brief win32 version of cpaf::api::gui::Window
    \date Created: 2005-04-05
*/

#ifndef CPAF_WIN32_GUI_WINDOW_H
#define CPAF_WIN32_GUI_WINDOW_H

#include <cpaf/win32/gui/widget.h>
#include <cpaf/api/gui/window.h>
#include <cpaf/gui/window.h>

#include <string>

namespace cpaf {
    namespace win32 {
        namespace gui {

class Window : public virtual cpaf::win32::gui::Widget, public virtual cpaf::api::gui::Window
{
    friend LRESULT CALLBACK window_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    Window() { }
    
    void create(const cpaf::gui::factory::WindowData &params);

    // toplevel interface
    virtual void set_title(const std::string &t);
    virtual std::string get_title();

    virtual void set_client_size(const cpaf::Size &s);
    virtual cpaf::Size get_client_size() { return cpaf::Size(); }
    virtual cpaf::Point get_client_position() { return cpaf::Point(); }
};

        } // gui
    } // win32
} // cpaf

#endif // CPAF_WIN32_GUI_WINDOW_H
