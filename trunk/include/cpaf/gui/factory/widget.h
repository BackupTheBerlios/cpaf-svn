/*!
    \file include/cpaf/gui/factory/widget.h
    \brief Factory initializer for cpaf::gui::Widget
    \date Created: 2005-05-07
*/

#ifndef CPAF_GUI_FACTORY_WIDGET_H
#define CPAF_GUI_FACTORY_WIDGET_H

#include <cpaf/gui/factory/object.h>

namespace cpaf {
    namespace gui {
        class Widget; // prototype
        namespace factory {

/*!
    \brief Data objcet for Widget creation. This class contains the
    initialization parameters which are passed from the widget factories
    to the object being created. This allows you to specify the objects
    initial state during creation time without needing to call set_foo()
    methods after creation.
*/
struct WidgetData : public ObjectData
{
    //! The parent of this widget.
    cpaf::gui::Widget *m_parent;

    //! Specifies if the widget should be initially visible
    bool m_show;

    //! Specifies if the widget should recieve input focus upon creation
    bool m_activate;

    //! Specifies if the widget is enabled or disabled
    bool m_enable;

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
