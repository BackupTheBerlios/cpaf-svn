/**
 * \file include/cpaf/cocoa/gui/widget.h
 * \brief Cocoa version of api::Widget
 * \date Created: 2005-04-29
 */

#ifndef CPAF_COCOA_GUI_WIDGET_H
#define CPAF_COCOA_GUI_WIDGET_H

#include <cpaf/api/gui/widget.h>
#include <cpaf/types.h>
#include <cpaf/private/factory.h>
#include <cpaf/event/event.h>
#include <cpaf/event/id.h>

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
      cpaf::event::Event event(event_id, m_cpaf_widget->m_wrapper->get_id()); \
      cpaf::event::get_manager().send_event(event); \
    } \
  } \
  @end

namespace cpaf {
    namespace cocoa {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
public:
    // Those are public, because we need to access them from the native object
    cpaf::gui::Widget *m_wrapper; // wrapper for this impl object
    id m_object;

protected:
    void send_event(cpaf::event::event_id event_id); // cocoa specific
    void create(const cpaf::gui::initializer::WidgetData &params, id widget);
    Widget() : m_wrapper(NULL) { }

public:
    virtual ~Widget();

    // object interface
    virtual void set_size(const cpaf::Size&);
    virtual void set_min_size(const cpaf::Size&) { }
    virtual void set_max_size(const cpaf::Size&) { }
    virtual void set_position(const cpaf::Point&);
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size() { return cpaf::Size(); } //! \todo
    virtual cpaf::Size get_max_size() { return cpaf::Size(); } //! \todo
    virtual cpaf::Point get_position() { return cpaf::Point(); } //! \todo

    // widget interface
    virtual void destroy();
    virtual void *get_handle() { return m_object; }
    virtual void enable(bool sensitive);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled();
    virtual bool is_shown();
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_WIDGET_H
