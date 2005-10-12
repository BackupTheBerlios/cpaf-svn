/*!
    \file include/cpaf/cocoa/gui/widget.h
    \brief Cocoa version of api::Widget
    \date Created: 2005-04-29
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

    Copyright (C) 2005 Thomas Steinacher
    http://www.eggdrop.ch/
    tom (at) eggdrop [dot] ch
*/

#ifndef CPAF_COCOA_GUI_WIDGET_H
#define CPAF_COCOA_GUI_WIDGET_H

#include <cpaf/api/gui/widget.h>
#include <cpaf/gui/widget.h>
#include <cpaf/types.h>
#include <cpaf/private/factory.h>
#include <cpaf/event/event.h>

#import <Cocoa/Cocoa.h>

// Two macros which create a subclass of a widget, so we
// can store the implementation object in the widget

#define CPAF_COCOA_INTERFACE(type) \
  @interface Cpaf ## type : NS ## type \
  { \
    cpaf::cocoa::gui::Widget *m_cpaf_widget; \
  } \
  - (void)setCpafWidget:(cpaf::cocoa::gui::Widget *)widget; \
  - (cpaf::cocoa::gui::Widget *)cpafWidget; \
  - (void)cpafSendEvent:(cpaf::event::event_id)event_id; \
  @end

#define CPAF_COCOA_IMPLEMENTATION(type) \
  @implementation Cpaf ## type \
  - (void)setCpafWidget:(cpaf::cocoa::gui::Widget *)widget \
  { \
    m_cpaf_widget = widget; \
  } \
  - (cpaf::cocoa::gui::Widget *)cpafWidget { return m_cpaf_widget; } \
  - (void)cpafSendEvent:(cpaf::event::event_id)event_id \
  { \
    if (m_cpaf_widget) \
    { \
      cpaf::event::Event event(event_id, m_cpaf_widget->get_wrapper_id()); \
      cpaf::event::get_manager().send_event(event); \
    } \
  } \
  @end

namespace cpaf {
    namespace cocoa {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
protected:
    cpaf::object_id m_wrapper_id;

    boost::weak_ptr<cpaf::gui::Widget> m_wrapper; // wrapper for this impl object
    id m_object;

    void send_event(cpaf::event::event_id event_id); // cocoa specific
    void create(const cpaf::gui::initializer::WidgetData &params, id widget);

    cpaf::Size m_min_size, m_max_size, m_natural_size;

    Widget() { }

public:
    virtual ~Widget();

    // object interface
    virtual void set_size(const cpaf::Size&);
    virtual void set_min_size(const cpaf::Size&);
    virtual void set_max_size(const cpaf::Size&);
    virtual void set_natural_size(const cpaf::Size&);
    virtual void set_position(const cpaf::Point&);
    virtual cpaf::Size get_size() const;
    virtual cpaf::Size get_min_size() const;
    virtual cpaf::Size get_max_size() const;
    virtual cpaf::Size get_natural_size() const;
    virtual cpaf::Point get_position() const;
    virtual void set_rect(const cpaf::Rect&);
    virtual cpaf::Rect get_rect() const;

    // widget interface
    virtual void destroy();
    virtual void *get_handle() const { return m_object; }
    virtual void enable(bool sensitive);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled() const;
    virtual bool is_shown() const;

    virtual boost::shared_ptr<cpaf::gui::Panel> get_parent() const;
    virtual boost::shared_ptr<cpaf::gui::Window> get_parent_window() const;

    // implementation specific
    cpaf::object_id get_wrapper_id() { return m_wrapper_id; }
    template<typename T> boost::shared_ptr<T> get_wrapper() const { return boost::dynamic_pointer_cast<T>(m_wrapper.lock()); }
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_WIDGET_H
