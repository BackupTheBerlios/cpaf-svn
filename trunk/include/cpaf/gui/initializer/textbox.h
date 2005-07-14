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
struct TextBoxData : TextWidgetData
{
};

/*!
    \brief Initializer class template for TextBox creation
*/
template<class T> class TextBox : public TextWidget<T>
{
public:
    typedef TextBoxData data_type;

protected:
    data_type *m_data;

    TextBox(data_type *data)
        : TextWidget<T>(data),
        m_data(data)
    { }
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
