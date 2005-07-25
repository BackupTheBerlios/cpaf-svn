/*!
    \file include/cpaf/gui/initializer/entrybox.h
    \brief Initializer classes for cpaf::gui::EntryBox
    \date Created: 2005-07-14
*/

#ifndef CPAF_GUI_INITIALIZER_ENTRYBOX_H
#define CPAF_GUI_INITIALIZER_ENTRYBOX_H

#include <string>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for Widget creation.
*/
struct EntryBoxData : TextWidgetData
{
    bool m_get_password_mode;
    
    EntryBoxData()
        : m_get_password_mode(false)
    { }
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
        m_data->m_get_password_mode = mode;
        return dynamic_cast<T&>(*this);
    }

    bool get_password_mode() const { return m_data->m_get_password_mode; }
};

        } // initializer

/*!
    \brief A concrete initializer class for EntryBox creation.
*/
class EntryBoxInitializer : public cpaf::gui::initializer::EntryBox<EntryBoxInitializer>
{
public:
    EntryBoxInitializer()
        : cpaf::gui::initializer::EntryBox<EntryBoxInitializer>(new cpaf::gui::initializer::EntryBoxData)
    { }

    operator cpaf::gui::initializer::EntryBoxData () const
    {
        return *m_data;
    }
};

    } // gui
} // cpaf

#endif
