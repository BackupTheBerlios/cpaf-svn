/*!
    \file include/cpaf/gui/initializer/widget.h
    \brief Initializer classes for cpaf::gui::Widget
    \date Created: 2005-05-07
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
*/

#ifndef CPAF_GUI_INITIALIZER_WIDGET_H
#define CPAF_GUI_INITIALIZER_WIDGET_H

#include <cpaf/gui/initializer/object.h>

namespace cpaf {
    namespace gui {
        class Panel;
        class Widget;
        namespace initializer {

/*!
    \brief initialization data for Widget creation.
*/
struct CPAF_API WidgetData : public ObjectData
{
protected:
    //! The wrapper for this implementation object
    boost::shared_ptr<Widget> m_wrapper;

    //! The parent of this widget.
    boost::shared_ptr<cpaf::gui::Panel> m_parent;

    //! Specifies if the widget should be initially visible
    bool m_show;

    //! Specifies if the widget should recieve input focus upon creation
    bool m_activate;

    //! Specifies if the widget is enabled or disabled
    bool m_enable;

public:
    WidgetData();

    void set_wrapper(boost::shared_ptr<cpaf::gui::Widget> p);
    boost::shared_ptr<cpaf::gui::Widget> get_wrapper() const;
    void set_parent(boost::shared_ptr<cpaf::gui::Panel> p);
    boost::shared_ptr<cpaf::gui::Panel> get_parent() const;
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
    T &parent(boost::shared_ptr<cpaf::gui::Panel> p)
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

    boost::shared_ptr<cpaf::gui::Panel> get_parent() const { return m_data->get_parent(); }
    bool get_show() const { return m_data->get_show(); }
    bool get_enable() const { return m_data->get_enable(); }
    bool get_activate() const { return m_data->get_activate(); }
};

        } // initializer
    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_WIDGET_H
