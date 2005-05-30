/*
Widget initializer factory
*/

#ifndef CPAF_GUI_FACTORY_WIDGET_H
#define CPAF_GUI_FACTORY_WIDGET_H

#include <cpaf/gui/factory/object.h>

namespace cpaf {
    namespace gui {
        class Widget; // prototype
        namespace factory {

struct WidgetData : public ObjectData
{
    cpaf::gui::Widget *m_parent;
    bool m_show, m_activate, m_enable;

    WidgetData()
        : m_parent(NULL),
        m_show(false),
        m_activate(false),
        m_enable(true)
    { }
};

template<class T> class Widget : public Object<T>
{
protected:
    WidgetData *m_data;

    Widget(WidgetData *data)
        : Object<T>(data),
        m_data(data)
    { }

public:
    T &parent(cpaf::gui::Widget *p)
    {
        m_data->m_parent = p;
        return *dynamic_cast<T*>(this);
    }

    T &show(bool s = true)
    {
        m_data->m_show = s;
        return *dynamic_cast<T*>(this);
    }

    T &activate(bool a = true)
    {
        m_data->m_activate = a;
        return *dynamic_cast<T*>(this);
    }

    T &hide()
    {
        m_data->m_show = false;
        return *dynamic_cast<T*>(this);
    }

    T &enable(bool s = true)
    {
        m_data->m_enable = s;
        return *dynamic_cast<T*>(this);
    }

    T &disable()
    {
        m_data->m_enable = false;
        return *dynamic_cast<T*>(this);
    }

    cpaf::gui::Widget *get_parent() const { return m_data->m_parent; }
    bool get_show() const { return m_data->m_show; }
    bool get_enable() const { return m_data->m_enable; }
};

        } // factory
    } // gui
} // cpaf

#endif
