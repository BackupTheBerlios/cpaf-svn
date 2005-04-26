/**
 * \file include/cpaf/gtk2/gui/widget.h
 * \brief Gtk2 version of api::Widget
 * \date 2005-04-05
 */

#ifndef CPAF_GTK2_GUI_WIDGET_H
#define CPAF_GTK2_GUI_WIDGET_H

#include <cpaf/gtk2/gtk.h>

#include <cpaf/api/gui/widget.h>
#include <cpaf/defs.h>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class Widget : public virtual cpaf::api::gui::Widget
{
protected:
    GtkWidget * m_widget;
    Widget(GtkWidget *);

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
    virtual int get_id() { return 0; } //! \todo No unique id's for gtk+ port yet. Why do we need them?
    virtual void enable(bool sensitive);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled();
    virtual bool is_shown();
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_WIDGET_H
