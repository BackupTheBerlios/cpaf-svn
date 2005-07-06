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

#import <Cocoa/Cocoa.h>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
protected:
    cpaf::gui::Widget *m_wrapper; // wrapper for this impl object
    id m_view;
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
    virtual cpaf::Size get_min_size() { return cpaf::Size(); }
    virtual cpaf::Size get_max_size() { return cpaf::Size(); }
    virtual cpaf::Point get_position() { return cpaf::Point(); }

    // widget interface
    virtual void destroy();
    virtual void *get_handle() { return m_view; }
    virtual void enable(bool sensitive);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled();
    virtual bool is_shown();
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_WIDGET_H
