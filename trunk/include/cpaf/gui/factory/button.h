/*!
    \file include/cpaf/gui/factory.h
    \brief Factory initializer for cpaf::gui::Button
    \date Created: 2005-05-07
*/

#ifndef CPAF_GUI_FACTORY_BUTTON_H
#define CPAF_GUI_FACTORY_BUTTON_H

#include <cpaf/gui/factory/widget.h>

#include <string>

namespace cpaf {
    namespace gui {
        namespace factory {

struct ButtonData : public WidgetData
{
    std::string m_label;
};

template<class T> class Button : public Widget<T>
{
protected:
    ButtonData *m_data;

    Button(ButtonData *data)
        : Widget<T>(data),
        m_data(data)
    { }

public:
    T &label(const std::string &s)
    {
        m_data->m_label = s;
        return *dynamic_cast<T*>(this);
    }

    std::string get_label() const { return m_data->m_label; }
};

        } // factory
    } // gui
} // cpaf

#endif
