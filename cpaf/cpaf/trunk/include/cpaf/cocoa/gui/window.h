/**
 * \file include/cpaf/cocoa/gui/window.h
 * \brief Cocoa version of api::Window
 * \date 2005-04-29
 */

#ifndef CPAF_COCOA_GUI_WINDOW_H
#define CPAF_COCOA_GUI_WINDOW_H

#include <cpaf/api/gui/window.h>
#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/types.h>

#include <string>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class Window : public cpaf::cocoa::gui::Widget, cpaf::api::gui::Window
{
public:
    Window(cpaf::api::gui::Window *parent);

    // object interface
    virtual void set_size(const cpaf::Size&);
    virtual void set_min_size(const cpaf::Size&);
    virtual void set_max_size(const cpaf::Size&);
    virtual void set_position(const cpaf::Point&);
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size();
    virtual cpaf::Size get_max_size();
    virtual cpaf::Point get_position();

    // widget interface

    // Do we need to override Widget::Show in Cocoa?
    virtual void show(bool show, bool activate);

    // toplevel interface
    virtual void set_title(const std::string&);
    virtual std::string get_title();

    virtual void set_client_size(const cpaf::Size&);
    virtual cpaf::Size get_client_size();
    virtual cpaf::Point get_client_position();
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_WINDOW_H