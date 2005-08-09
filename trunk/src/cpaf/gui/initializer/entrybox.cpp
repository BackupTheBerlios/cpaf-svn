/*!
    \file src/cpaf/gui/initializer/entrybox.cpp
    \brief cpaf::gui::EntryBox initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/entrybox.h>

using namespace cpaf::gui::initializer;

EntryBoxData::EntryBoxData()
    : m_password_mode(false)
{ }

void EntryBoxData::set_password_mode(bool b)
{
    m_password_mode = b;
}

bool EntryBoxData::get_password_mode() const
{
    return m_password_mode;
}

cpaf::gui::EntryBoxInitializer::EntryBoxInitializer()
    : cpaf::gui::initializer::EntryBox<EntryBoxInitializer>(new data_type)
{ }

cpaf::gui::EntryBoxInitializer::data_type cpaf::gui::EntryBoxInitializer::get_data() const
{
    return *m_data;
}
