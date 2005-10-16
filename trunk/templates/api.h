/*!
    \file include/cpaf/api/gui/$(NAME_LOWER).$(H_EXT)
    \brief $(NAME) interface declaration
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

#ifndef CPAF_API_GUI_$(NAME_UPPER)_H
#define CPAF_API_GUI_$(NAME_UPPER)_H

#include <cpaf/gui/initializer/$(NAME_LOWER).h>
#include <cpaf/api/gui/$(BASE_LOWER).h>

namespace cpaf {
    namespace api {
        namespace gui {

class $(NAME) : public virtual $(BASE)
{
public:
    typedef cpaf::gui::initializer::$(NAME)Data data_type; //!< Initialization data used for $(NAME).

    virtual void create(const data_type &init_params) = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_$(NAME_UPPER)_H
