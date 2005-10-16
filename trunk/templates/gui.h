/*!
    \file include/cpaf/gui/$(NAME_LOWER).$(H_EXT)
    \brief cpaf::gui::$(NAME) declaration
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

#ifndef CPAF_GUI_$(NAME_UPPER)_H
#define CPAF_GUI_$(NAME_UPPER)_H

#include <cpaf/gui/$(BASE_LOWER).h>
#include <cpaf/gui/initializer/$(NAME_LOWER).h>

namespace cpaf {
    namespace gui {

class CPAF_API $(NAME) : public $(BASE)
{
public:
    typedef cpaf::api::gui::$(NAME) api_type;
    typedef $(NAME)Initializer Initializer;

$(IF CONSTRUCTABLE)
    static boost::shared_ptr<$(NAME)> create(const Initializer &initializer);
$(END)

private:
    api_type *m_impl;

protected:
$(IF CONSTRUCTABLE)
    $(NAME)();
$(END)
    $(NAME)(api_type *impl);

$(IF CONSTRUCTABLE)
    /*!
        \brief Constructs the native widget using the given initializer
    */
    boost::shared_ptr<$(NAME)> initialize(const Initializer &initializer);
$(END)

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_$(NAME_UPPER)_H
