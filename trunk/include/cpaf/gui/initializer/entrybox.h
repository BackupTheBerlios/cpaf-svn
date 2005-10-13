/*!
    \file include/cpaf/gui/initializer/entrybox.h
    \brief Initializer classes for cpaf::gui::EntryBox
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

#ifndef CPAF_GUI_INITIALIZER_ENTRYBOX_H
#define CPAF_GUI_INITIALIZER_ENTRYBOX_H

#include <cpaf/gui/initializer/textwidget.h>
#include <string>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Widget creation.
*/
struct CPAF_API EntryBoxData : TextWidgetData
{
protected:
    bool m_password_mode;
    
public:
    EntryBoxData();

    void set_password_mode(bool b);
    bool get_password_mode() const;
};

/*!
    \brief Initializer class template for EntryBox creation
*/
template<class T> class EntryBox : public TextWidget<T>
{
public:
    typedef EntryBoxData data_type;

protected:
    data_type *m_data;

    EntryBox(data_type *data)
        : TextWidget<T>(data),
        m_data(data)
    { }

public:
    T &password_mode(bool mode = true)
    {
        m_data->set_password_mode(mode);
        return dynamic_cast<T&>(*this);
    }

    bool get_password_mode() const { return m_data->get_password_mode(); }
};

        } // initializer

class EntryBox;
/*!
    \brief A concrete initializer class for EntryBox creation.
*/
class CPAF_API EntryBoxInitializer : public cpaf::gui::initializer::EntryBox<EntryBoxInitializer>
{
    friend class cpaf::gui::EntryBox;

public:
    EntryBoxInitializer();

private:
    data_type get_data() const;
};

    } // gui
} // cpaf

#endif
