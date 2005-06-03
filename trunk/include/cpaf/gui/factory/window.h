/*!
    \file include/cpaf/gui/factory/window.h
    \brief Factory initializer for cpaf::gui::Window
    \date Created: 2005-05-07
*/

#ifndef CPAF_GUI_FACTORY_WINDOW_H
#define CPAF_GUI_FACTORY_WINDOW_H

#include <cpaf/gui/factory/widget.h>

#include <string>

namespace cpaf {
    namespace gui {
        namespace factory {

/*!
    \brief Data objcet for Window creation. This class contains the
    initialization parameters which are passed from the widget factories
    to the object being created. This allows you to specify the objects
    initial state during creation time without needing to call set_foo()
    methods after creation.
*/
struct WindowData : public WidgetData
{
    //! The title of the window. This will appear on the Windows caption
    std::string m_title;

    //! The size of the client area of the window.
    cpaf::Size m_client_size;

    /*!
        If this member is true, you must ignore the value specified by
        ObjectData::m_size and ObjectData::m_default_size, and use the
        size provided by m_client_size instead. If this member is false,
        you must consider ObjectData::m_default_size and ObjectData::m_size
        as you normally would.
    */
    bool m_use_client_size;

    WindowData()
        : m_use_client_size(false)
    {
        // windows should be activated when shown by default
        WidgetData::m_activate = true;
    }
};

template <typename T> class Window : public Widget<T>
{
protected:
    WindowData *m_data;

    Window(WindowData *data)
        : Widget<T>(data),
        m_data(data)
    { }

public:
    T &title(const std::string &s)
    {
        m_data->m_title = s;
         return *dynamic_cast<T*>(this);
    }

    T &client_size(const cpaf::Size &s)
    {
        m_data->m_client_size = s;
        m_data->m_use_client_size = true;
         return *dynamic_cast<T*>(this);
    }

    std::string get_title() const { return m_data->m_title; }
    cpaf::Size get_client_size() const { return m_data->m_client_size; }
};

        } // factory
    } // gui
} // cpaf

#endif

