/*!
    \file include/cpaf/gui/initializer/textbox.h
    \brief Initializer classes for cpaf::gui::TextBox
    \date Created: 2005-07-07
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
