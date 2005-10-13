/*!
    \file include/cpaf/gui/initializer/window.h
    \brief Initializer classes for cpaf::gui::Window
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
struct CPAF_API WindowData : public WidgetData
{
protected:
    //! The title of the window. This will appear on the Windows caption
    std::string m_title;

    //! The size of the client area of the window.
    cpaf::Size m_client_size;

    //! The position in screen coordinates of the window
    cpaf::Point m_position;

    /*!
        If this member is true, an acceptible value for this windows
        position should be calculated and used. If it is false,
        the value of m_pos must be used.
    */
    bool m_default_position;

    //! The content panel for the window
    boost::shared_ptr<cpaf::gui::Panel> m_content_panel;

public:
    WindowData();

    void set_title(const std::string &str);
    std::string get_title() const;
    void set_position(const cpaf::Point &p);
    cpaf::Point get_position() const;
    void set_client_size(const cpaf::Size &s);
    cpaf::Size get_client_size() const;
    void set_content_panel(boost::shared_ptr<cpaf::gui::Panel> p);
    boost::shared_ptr<cpaf::gui::Panel> get_content_panel() const;
    
    bool default_position() const;
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
        m_data->set_title(s);
        return dynamic_cast<T&>(*this);
    }

    T &position(const cpaf::Point &p)
    {
        m_data->set_position(p);
        return dynamic_cast<T&>(*this);
    }

    T &client_size(const cpaf::Size &s)
    {
        m_data->set_client_size(s);
        return dynamic_cast<T&>(*this);
    }

    T &content_panel(boost::shared_ptr<cpaf::gui::Panel> p)
    {
        m_data->set_content_panel(p);
        return dynamic_cast<T&>(*this);
    }

    std::string get_title() const { return m_data->get_title(); }
    cpaf::Point get_position() const { return m_data->get_position(); }
    cpaf::Size get_client_size() const { return m_data->get_client_size(); }
    boost::shared_ptr<cpaf::gui::Panel> get_content_panel() const { return m_data->get_content_panel(); }
};

        } // initializer

class Window;
/*!
    \brief A concrete initializer class for Window creation
*/
class CPAF_API WindowInitializer : public cpaf::gui::initializer::Window<WindowInitializer>
{
    friend class cpaf::gui::Window;

public:
    WindowInitializer();

private:
    data_type get_data() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_WINDOW_H
