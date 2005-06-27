/*!
    \file include/cpaf/gui/initializer/widget.h
    \brief Initializer classes for cpaf::gui::Widget
    \date Created: 2005-05-07
*/

#ifndef CPAF_GUI_INITIALIZER_WIDGET_H
#define CPAF_GUI_INITIALIZER_WIDGET_H

#include <cpaf/gui/initializer/object.h>

namespace cpaf {
    namespace gui {
        class Widget;
        namespace initializer {

/*!
    \brief initialization data for Widget creation.
*/
struct WidgetData : public ObjectData
{
    //! The wrapper for this implementation object
    cpaf::gui::Widget *m_wrapper;

    //! The parent of this widget.
    cpaf::gui::Widget *m_parent;

    //! Specifies if the widget should be initially visible
    bool m_show;

    //! Specifies if the widget should recieve input focus upon creation
    bool m_activate;

    //! Specifies if the widget is enabled or disabled
    bool m_enable;

    WidgetData()
        : m_wrapper(NULL),
        m_parent(NULL),
        m_show(false),
        m_activate(false),
        m_enable(true)
    { }
};

/*!
    \brief Initializer class for Widget creation.
*/
template<class T> class Widget : public Object<T>
{
public:
    typedef WidgetData data_type;

protected:
    data_type *m_data;

    Widget(data_type *data)
        : Object<T>(data),
        m_data(data)
    { }

public:
    T &parent(cpaf::gui::Widget *p)
    {
        m_data->m_parent = p;
        return dynamic_cast<T&>(*this);
    }

    T &show(bool s = true)
    {
        m_data->m_show = s;
        return dynamic_cast<T&>(*this);
    }

    T &activate(bool a = true)
    {
        m_data->m_activate = a;
        return dynamic_cast<T&>(*this);
    }

    T &hide()
    {
        m_data->m_show = false;
        return dynamic_cast<T&>(*this);
    }

    T &enable(bool s = true)
    {
        m_data->m_enable = s;
        return dynamic_cast<T&>(*this);
    }

    T &disable()
    {
        m_data->m_enable = false;
        return dynamic_cast<T&>(*this);
    }

    void set_wrapper(cpaf::gui::Widget *w) { m_data->m_wrapper = w; }

    cpaf::gui::Widget *get_parent() const { return m_data->m_parent; }
    bool get_show() const { return m_data->m_show; }
    bool get_enable() const { return m_data->m_enable; }
};

        } // initializer
    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_WIDGET_H
