/*!
    \file include/cpaf/gui/initializer/button.h
    \brief Initializer classes for cpaf::gui::Button
    \date Created: 2005-05-07
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
struct CPAF_API ButtonData : public WidgetData
{
protected:
    std::string m_label;

public:
    void set_label(const std::string &str);
    std::string get_label() const;
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
        m_data->set_label(s);
        return dynamic_cast<T&>(*this);
    }

    std::string get_label() const { return m_data->get_label(); }
};

        } // initializer

class Button;
/*!
    \brief A concrete initializer class for Button creation.
*/
class CPAF_API ButtonInitializer : public cpaf::gui::initializer::Button<ButtonInitializer>
{
    friend class cpaf::gui::Button;
public:
    ButtonInitializer();

private:
    data_type get_data() const;
};

    } // gui
} // cpaf

#endif
