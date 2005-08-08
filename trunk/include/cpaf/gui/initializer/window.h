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
struct CPAF_API WindowData : public WidgetData
{
protected:
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

    //! The content panel for the window
    cpaf::gui::Panel *m_content_panel;

public:
    WindowData();

    void set_title(const std::string &str);
    std::string get_title() const;
    void set_client_size(const cpaf::Size &s);
    cpaf::Size get_client_size() const;
    void set_content_panel(cpaf::gui::Panel *p);
    cpaf::gui::Panel *get_content_panel() const;
    
    bool use_client_size() const;
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

    T &client_size(const cpaf::Size &s)
    {
        m_data->set_client_size(s);
        return dynamic_cast<T&>(*this);
    }

    T &content_panel(cpaf::gui::Panel *p)
    {
        m_data->set_content_panel(p);
        return dynamic_cast<T&>(*this);
    }

    std::string get_title() const { return m_data->get_title(); }
    cpaf::Size get_client_size() const { return m_data->get_client_size(); }
    cpaf::gui::Panel *get_content_panel() const { return m_data->get_content_panel(); }
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
