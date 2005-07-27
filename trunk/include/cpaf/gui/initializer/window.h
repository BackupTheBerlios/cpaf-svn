/*!
    \file include/cpaf/gui/initializer/window.h
    \brief Initializer classes for cpaf::gui::Window
    \date Created: 2005-05-07
*/

#ifndef CPAF_GUI_INITIALIZER_WINDOW_H
#define CPAF_GUI_INITIALIZER_WINDOW_H

#include <cpaf/gui/initializer/widget.h>
#include <string>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief Initialization data for Window creation.
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

/*!
    \brief Initializer class for Window creation.
*/
template <typename T> class Window : public Widget<T>
{
public:
    typedef WindowData data_type;

protected:
    data_type *m_data;

    Window(data_type *data)
        : Widget<T>(data),
        m_data(data)
    { }

public:
    T &title(const std::string &s)
    {
        m_data->m_title = s;
         return dynamic_cast<T&>(*this);
    }

    T &client_size(const cpaf::Size &s)
    {
        m_data->m_client_size = s;
        m_data->m_use_client_size = true;
        m_data->m_default_size = false;
         return dynamic_cast<T&>(*this);
    }

    std::string get_title() const { return m_data->m_title; }
    cpaf::Size get_client_size() const { return m_data->m_client_size; }
};

        } // initializer

/*!
    \brief A concrete initializer class for Window creation
*/
class WindowInitializer : public cpaf::gui::initializer::Window<WindowInitializer>
{
public:
    WindowInitializer()
        : cpaf::gui::initializer::Window<WindowInitializer>(new cpaf::gui::initializer::WindowData)
    { }

    operator cpaf::gui::initializer::WindowData () const
    {
        return *m_data;
    }
};

    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_WINDOW_H
