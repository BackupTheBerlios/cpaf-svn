/*!
    \file src/cpaf/gui/initializer/$(NAME_LOWER).cpp
    \brief cpaf::gui::$(NAME) initializer implementation
    \date Created: $(DATE)
*/

#include <cpaf/gui/initializer/$(NAME_LOWER).h>

cpaf::gui::$(NAME)Initializer::$(NAME)Initializer()
    : cpaf::gui::initializer::$(NAME)<$(NAME)Initializer>(new data_type)
{ }

cpaf::gui::$(NAME)Initializer::data_type cpaf::gui::$(NAME)Initializer::get_data() const
{
    return *m_data;
}
