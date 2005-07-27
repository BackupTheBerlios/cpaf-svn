/*!
    \file src/cpaf/gui/initializer/textbox.cpp
    \brief cpaf::gui::TextBox initializer implementation
    \date Created: 2005-07-27
*/

#include <cpaf/gui/initializer/textbox.h>

cpaf::gui::TextBoxInitializer::TextBoxInitializer()
    : cpaf::gui::initializer::TextBox<TextBoxInitializer>(new cpaf::gui::initializer::TextBoxData)
{ }

cpaf::gui::TextBoxInitializer::data_type cpaf::gui::TextBoxInitializer::get_data() const
{
    return *m_data;
}
