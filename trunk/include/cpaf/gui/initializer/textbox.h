/*!
    \file include/cpaf/gui/initializer/textbox.h
    \brief Initializer classes for cpaf::gui::TextBox
    \date Created: 2005-07-07
*/

#ifndef CPAF_GUI_INITIALIZER_TEXTBOX_H
#define CPAF_GUI_INITIALIZER_TEXTBOX_H

#include <cpaf/gui/initializer/textwidget.h>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for TextBox creation.
*/
struct CPAF_API TextBoxData : TextWidgetData
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

class TextBox;
/*!
    \brief A concrete initializer class for TextBox creation.
*/
class CPAF_API TextBoxInitializer : public cpaf::gui::initializer::TextBox<TextBoxInitializer>
{
    friend class cpaf::gui::TextBox;

public:
    TextBoxInitializer();

private:
    data_type get_data() const;
};

    } // gui
} // cpaf

#endif
