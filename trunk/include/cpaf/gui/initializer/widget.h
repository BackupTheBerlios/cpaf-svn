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
struct CPAF_API WidgetData : public ObjectData
{
protected:
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

public:
    WidgetData();

    void set_wrapper(cpaf::gui::Widget *w);
    cpaf::gui::Widget *get_wrapper() const;
    void set_parent(cpaf::gui::Widget *w);
    cpaf::gui::Widget *get_parent() const;
    void set_show(bool b);
    bool get_show() const;
    void set_activate(bool b);
    bool get_activate() const;
    void set_enable(bool b);
    bool get_enable() const;
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
        m_data->set_parent(p);
        return dynamic_cast<T&>(*this);
    }

    T &show(bool s = true)
    {
        m_data->set_show(s);
        return dynamic_cast<T&>(*this);
    }

    T &activate(bool a = true)
    {
        m_data->set_activate(a);
        return dynamic_cast<T&>(*this);
    }

    T &hide()
    {
        m_data->set_show(false);
        return dynamic_cast<T&>(*this);
    }

    T &enable(bool s = true)
    {
        m_data->set_enable(s);
        return dynamic_cast<T&>(*this);
    }

    T &disable()
    {
        m_data->set_enable(false);
        return dynamic_cast<T&>(*this);
    }

    cpaf::gui::Widget *get_parent() const { return m_data->get_parent(); }
    bool get_show() const { return m_data->get_show(); }
    bool get_enable() const { return m_data->get_enable(); }
    bool get_activate() const { return m_data->get_activate(); }
};

        } // initializer
    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_WIDGET_H
