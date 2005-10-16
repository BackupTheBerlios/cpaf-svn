/*!
    \file include/cpaf/gui/initializer/$(NAME_LOWER).$(H_EXT)
    \brief Initializer classes for cpaf::gui::$(NAME)
    \date Created: $(DATE)
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

#ifndef CPAF_GUI_INITIALIZER_$(NAME_UPPER)_H
#define CPAF_GUI_INITIALIZER_$(NAME_UPPER)_H

#include <cpaf/gui/initializer/$(BASE_LOWER).h>

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

class $(NAME);
/*!
    \brief A concrete initializer class for $(NAME) creation.
*/
class CPAF_API $(NAME)Initializer : public cpaf::gui::initializer::$(NAME)<$(NAME)Initializer>
{
    friend class cpaf::gui::$(NAME);
public:
    $(NAME)Initializer();

private:
    data_type get_data() const;
};

$(END)
    } // gui
} // cpaf

#endif // CPAF_GUI_INITIALIZER_$(NAME_UPPER)_H
