/*!
    \file include/cpaf/gui/initializer/button.h
    \brief Initializer classes for cpaf::gui::Button
    \date Created: 2005-05-07
*/

#ifndef CPAF_GUI_INITIALIZER_BUTTON_H
#define CPAF_GUI_INITIALIZER_BUTTON_H

#include <cpaf/gui/initializer/widget.h>

#include <string>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief Initialization data for Button creation.
*/
struct ButtonData : public WidgetData
{
    std::string m_label;
};

/*!
    \brief Initializer class template for Button creation
*/
template<class T> class Button : public Widget<T>
{
public:
    typedef ButtonData data_type;

protected:
    data_type *m_data;

    Button(data_type *data)
        : Widget<T>(data),
        m_data(data)
    { }

public:
    T &label(const std::string &s)
    {
        m_data->m_label = s;
        return dynamic_cast<T&>(*this);
    }

    std::string get_label() const { return m_data->m_label; }
};

        } // initializer

/*!
    \brief A concrete initializer class for Button creation.
*/
class ButtonInitializer : public cpaf::gui::initializer::Button<ButtonInitializer>
{
public:
    ButtonInitializer()
        : cpaf::gui::initializer::Button<ButtonInitializer>(new cpaf::gui::initializer::ButtonData)
    { }

    operator cpaf::gui::initializer::ButtonData () const
    {
        return *m_data;
    }
};

    } // gui
} // cpaf

#endif
