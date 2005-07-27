/*!
    \file include/cpaf/gui/initializer/textwidget.h
    \brief Initializer classes for cpaf::gui::TextWidget
    \date Created: 2005-07-14
*/

#ifndef CPAF_GUI_INITIALIZER_TEXTWIDGET_H
#define CPAF_GUI_INITIALIZER_TEXTWIDGET_H

#include <cpaf/gui/initializer/widget.h>
#include <string>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Widget creation.
*/
struct CPAF_API TextWidgetData : WidgetData
{
protected:
    std::string m_text;

public:
    void set_text(const std::string &str);
    std::string get_text() const;
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
        m_data->set_text(s);
        return dynamic_cast<T&>(*this);
    }

    std::string get_text() const { return m_data->get_text(); }
};

        } // initializer
    } // gui
} // cpaf

#endif
