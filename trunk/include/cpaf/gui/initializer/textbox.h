/*!
    \file include/cpaf/gui/initializer/textbox.h
    \brief Initializer classes for cpaf::gui::TextBox
    \date Created: 2005-07-07
*/

#ifndef CPAF_GUI_INITIALIZER_TEXTBOX_H
#define CPAF_GUI_INITIALIZER_TEXTBOX_H

#include <string>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Widget creation.
*/
struct TextBoxData : WidgetData
{
    std::string m_text;
};

/*!
    \brief Initializer class template for TextBox creation
*/
template<class T> class TextBox : public Widget<T>
{
public:
    typedef TextBoxData data_type;

protected:
    data_type *m_data;

    TextBox(data_type *data)
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
    \brief A concrete initializer class for TextBox creation.
*/
class TextBoxInitializer : public cpaf::gui::initializer::TextBox<TextBoxInitializer>
{
public:
    TextBoxInitializer()
        : cpaf::gui::initializer::TextBox<TextBoxInitializer>(new cpaf::gui::initializer::TextBoxData)
    { }

    operator cpaf::gui::initializer::TextBoxData () const
    {
        return *m_data;
    }
};

    } // gui
} // cpaf

#endif
