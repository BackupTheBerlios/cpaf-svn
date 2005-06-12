/**
 * \file include/cpaf/gtk2/gui/widget.h
 * \brief Gtk2 version of cpaf::api::gui::Widget
 * \date Created: 2005-04-05
 */

#ifndef CPAF_GTK2_GUI_WIDGET_H
#define CPAF_GTK2_GUI_WIDGET_H

#include <cpaf/gtk2/gtk.h>

#include <cpaf/api/gui/widget.h>
#include <cpaf/types.h>

// for initializer factory
#include <cpaf/gui/widget.h>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
public:
    virtual ~Widget();

    // object interface
    virtual void set_size(const cpaf::Size&);
    virtual void set_min_size(const cpaf::Size&) { }
    virtual void set_max_size(const cpaf::Size&) { }
    virtual void set_position(const cpaf::Point&) { }
    virtual cpaf::Size get_size();
    virtual cpaf::Size get_min_size() { return cpaf::Size(); }
    virtual cpaf::Size get_max_size() { return cpaf::Size(); }
    virtual cpaf::Point get_position() { return cpaf::Point(); }

    // widget interface
    virtual void *get_handle() { return (void*)m_widget; }
    virtual void enable(bool sensitive);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled();
    virtual bool is_shown();

protected:
    Widget();
    void create(const cpaf::gui::factory::WidgetData&, GtkWidget *);

    cpaf::gui::Widget *m_wrapper; // wrapper for this impl object
    GtkWidget * m_widget;
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_WIDGET_H
