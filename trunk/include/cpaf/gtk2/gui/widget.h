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
    virtual void set_position(const cpaf::Point&);
    virtual cpaf::Size get_size() const;
    virtual cpaf::Size get_min_size() const { return cpaf::Size(); }
    virtual cpaf::Size get_max_size() const { return cpaf::Size(); }
    virtual cpaf::Point get_position() const { return cpaf::Point(); }
    virtual void set_rect(const cpaf::Rect&) { }
    virtual cpaf::Rect get_rect() const { return cpaf::Rect(); }

    // widget interface
    virtual void destroy();
    virtual void *get_handle() const { return (void*)m_widget; }
    virtual void enable(bool sensitive);
    virtual void show(bool show, bool activate);
    virtual bool is_enabled() const;
    virtual bool is_shown() const;

    virtual cpaf::gui::Panel *get_parent() const;
    virtual cpaf::gui::Window *get_parent_window() const;
    template<typename T> T *get_wrapper() const { return dynamic_cast<T*>(m_wrapper); }

protected:
    Widget();
    void create(const cpaf::gui::initializer::WidgetData&, GtkWidget *);

    cpaf::gui::Widget *m_wrapper; // wrapper for this impl object
    GtkWidget * m_widget;
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_WIDGET_H
