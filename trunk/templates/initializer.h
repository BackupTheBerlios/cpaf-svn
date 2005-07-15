/*!
    \file include/cpaf/gui/initializer/$(NAME_LOWER).h
    \brief Initializer classes for cpaf::gui::$(NAME)
    \date Created: 2005-07-07
*/

#ifndef CPAF_GUI_INITIALIZER_$(NAME_UPPER)_H
#define CPAF_GUI_INITIALIZER_$(NAME_UPPER)_H

#include <cpaf/gui/initializer/$(NAME_LOWER).h>

namespace cpaf {
    namespace gui {
        namespace initializer {

/*!
    \brief initialization data for $(NAME) creation.
*/
struct $(NAME)Data : $(BASE)Data
{

};

/*!
    \brief Initializer class template for $(NAME) creation
*/
template<class T> class $(NAME) : public $(BASE)<T>
{
public:
    typedef $(NAME)Data data_type;

protected:
    data_type *m_data;

    $(NAME)(data_type *data)
        : $(BASE)<T>(data),
        m_data(data)
    { }
};

        } // initializer
$(IF CONSTRUCTABLE)

/*!
    \brief A concrete initializer class for $(NAME) creation.
*/
class $(NAME)Initializer : public cpaf::gui::initializer::$(NAME)<$(NAME)Initializer>
{
public:
    $(NAME)Initializer()
        : cpaf::gui::initializer::$(NAME)<$(NAME)Initializer>(new cpaf::gui::initializer::$(NAME)Data)
    { }

    operator cpaf::gui::initializer::$(NAME)Data () const
    {
        return *m_data;
    }
};

$(END)
    } // gui
} // cpaf

#endif
