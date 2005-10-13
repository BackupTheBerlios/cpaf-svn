/*!
    \file include/cpaf/gui/initializer/textwidget.h
    \brief Initializer classes for cpaf::gui::TextWidget
    \date Created: 2005-07-14
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
