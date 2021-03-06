/**
 * \file include/cpaf/gtk2/gui/widget.h
 * \brief Gtk2 version of cpaf::api::gui::Widget
 * \date Created: 2005-04-05
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

    Copyright (C) 2005 Mart Raudsepp
    leio (at) dustbite [dot] net
*/

#ifndef CPAF_GTK2_GUI_WIDGET_H
#define CPAF_GTK2_GUI_WIDGET_H

#include <cpaf/gtk2/gtk.h>

#include <cpaf/api/gui/widget.h>
#include <cpaf/types.h>

// for initializer factory
#include <cpaf/gui/widget.h>

namespace cpaf {
    namespace event {
        typedef int event_id;
    }

    namespace gtk2 {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
public:
    virtual ~Widget();

    // object interface
    virtual void set_size(const cpaf::Size&);
    virtual void set_min_size(const cpaf::Size&);
    virtual void set_max_size(const cpaf::Size&) { }
    virtual void set_natural_size(const cpaf::Size&) { }
    virtual void set_position(const cpaf::Point&);
    virtual cpaf::Size get_size() const;
    virtual cpaf::Size get_min_size() const;
    virtual cpaf::Size get_max_size() const { return cpaf::Size(); }
    virtual cpaf::Size get_natural_size() const { return cpaf::Size(); }
    virtual cpaf::Point get_position() const { return cpaf::Point(); }
    virtual void set_rect(const cpaf::Rect&);
    virtual cpaf::Rect get_rect() const;

    // widget interface
    virtual void destroy();
    virtual void *get_handle() const { return (void*)m_widget; }
    virtual void enable(bool sensitive);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled() const;
    virtual bool is_shown() const;

    virtual boost::shared_ptr<cpaf::gui::Panel> get_parent() const;
    virtual boost::shared_ptr<cpaf::gui::Window> get_parent_window() const;
    template<typename T> boost::shared_ptr<T> get_wrapper() const { return boost::dynamic_pointer_cast<T>(m_wrapper.lock()); }

    // implementation specific
    void send_event(cpaf::event::event_id);

    cpaf::object_id get_wrapper_id() { return m_wrapper_id; }

protected:
    Widget();
    void create(const cpaf::gui::initializer::WidgetData&, GtkWidget *);

    boost::weak_ptr<cpaf::gui::Widget> m_wrapper; // wrapper for this impl object
    cpaf::object_id m_wrapper_id;
    GtkWidget * m_widget;
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_WIDGET_H
