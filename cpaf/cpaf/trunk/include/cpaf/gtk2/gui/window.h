/**
 * \file include/cpaf/gtk2/gui/window.h
 * \brief Gtk2 version of api::Window
 * \date 2005-04-05
 */

#ifndef CPAF_GTK2_GUI_WINDOW_H
#define CPAF_GTK2_GUI_WINDOW_H

#include <cpaf/gtk2/gtk.h>

#include <cpaf/api/gui/window.h>
#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/defs.h>

#include <string>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class Window : public cpaf::gtk2::gui::Widget, cpaf::api::gui::Window
{
public:
    Window();

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

    // Overridden to use gtk_window_set_focus_on_map
    // instead of gtk_widget_grab_focus
    virtual void show(bool show, bool activate);

    // toplevel interface
    virtual void set_title(const std::string&);
    virtual std::string get_title();

    virtual void set_client_size(const cpaf::Size&);
    virtual cpaf::Size get_client_size();
    virtual cpaf::Point get_client_position();
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_WINDOW_H
