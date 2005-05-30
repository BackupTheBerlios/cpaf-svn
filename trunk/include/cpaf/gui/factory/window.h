/*
Window initializer factory
*/

#ifndef CPAF_GUI_FACTORY_WINDOW_H
#define CPAF_GUI_FACTORY_WINDOW_H

#include <cpaf/gui/factory/widget.h>

#include <string>

namespace cpaf {
    namespace gui {
        namespace factory {

struct WindowData : public WidgetData
{
    std::string m_title;

    WindowData()
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

    std::string get_title() const { return m_data->m_title; }
};

        } // factory
    } // gui
} // cpaf

#endif

