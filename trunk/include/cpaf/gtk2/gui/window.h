/*!
    \file include/cpaf/gtk2/gui/window.h
    \brief Gtk2 version of cpaf::api::gui::Window
    \date Created: 2005-04-05
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CPAF_GTK2_GUI_WINDOW_H
#define CPAF_GTK2_GUI_WINDOW_H

#include <cpaf/gtk2/gtk.h>

#include <cpaf/api/gui/window.h>
#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/types.h>
#include <cpaf/gui/window.h>

#include <string>

namespace cpaf {
    namespace gui { class Panel; }
    namespace gtk2 {
        namespace gui {

class Window : public virtual cpaf::gtk2::gui::Widget, public virtual cpaf::api::gui::Window
{
public:
    Window();

    void create(const cpaf::gui::initializer::WindowData &params);

    // object interface
    virtual void set_size(const cpaf::Size&);
    virtual void set_min_size(const cpaf::Size&);
    virtual void set_max_size(const cpaf::Size&);
    virtual void set_position(const cpaf::Point&);
    virtual cpaf::Size get_size() const;
    virtual cpaf::Size get_min_size() const;
    virtual cpaf::Size get_max_size() const;
    virtual cpaf::Point get_position() const;

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

    virtual void set_content_panel(cpaf::api::gui::Panel *p);
    virtual boost::shared_ptr<cpaf::gui::Panel> get_content_panel() const;
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_WINDOW_H
