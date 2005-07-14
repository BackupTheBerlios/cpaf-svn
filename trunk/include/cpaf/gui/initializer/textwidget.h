/*!
    \file include/cpaf/gui/initializer/textwidget.h
    \brief Initializer classes for cpaf::gui::TextWidget
    \date Created: 2005-07-14
*/

#ifndef CPAF_GUI_INITIALIZER_TEXTWIDGET_H
#define CPAF_GUI_INITIALIZER_TEXTWIDGET_H

#include <string>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Widget creation.
*/
struct TextWidgetData : WidgetData
{
    std::string m_text;
};

/*!
    \brief Initializer class template for TextWidget creation
*/
template<class T> class TextWidget : public Widget<T>
{
public:
    typedef TextWidgetData data_type;

protected:
    data_type *m_data;

    TextWidget(data_type *data)
        : Widget<T>(data),
        m_data(data)
    { }

public:
    T &text(const std::string &s)
    {
        m_data->m_text = s;
        return dynamic_cast<T&>(*this);
    }

    std::string get_text() const { return m_data->m_text; }
};

        } // initializer

/*!
    \brief A concrete initializer class for TextWidget creation.
*/
class TextWidgetInitializer : public cpaf::gui::initializer::TextWidget<TextWidgetInitializer>
{
public:
    TextWidgetInitializer()
        : cpaf::gui::initializer::TextWidget<TextWidgetInitializer>(new cpaf::gui::initializer::TextWidgetData)
    { }

    operator cpaf::gui::initializer::TextWidgetData () const
    {
        return *m_data;
    }
};

    } // gui
} // cpaf

#endif
