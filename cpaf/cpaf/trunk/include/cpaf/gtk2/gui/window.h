/**
 * \file include/cpaf/gtk2/gui/window.h
 * \brief Gtk2 version of api::Window
 * \date 2005-04-05
 */

#include <cpaf/gtk2/gtk.h>

#include <cpaf/api/gui/window.h>
#include <cpaf/defs.h>

#include <string>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class Window : public cpaf::api::gui::Window
{
private:
    GtkWidget * m_widget;

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
    virtual int get_handle() { return (int)(void*)m_widget; }
    virtual void enable(bool sensitive);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled();
    virtual bool is_shown();

    // toplevel interface
    virtual void set_title(const std::string &t);
    virtual std::string get_title();

    virtual void set_client_size(cpaf::Size s);
    virtual cpaf::Size get_client_size();
    virtual cpaf::Point get_client_position();
};

        } // gui
    } // gtk2
} // cpaf
