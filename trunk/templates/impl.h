/*!
    \file include/cpaf/$(PORT_LOWER)/$(NAME_LOWER).$(H_EXT)
    \brief $(PORT) version of cpaf::api::gui::$(NAME)
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

#ifndef CPAF_$(PORT_UPPER)_GUI_$(NAME_UPPER)_H
#define CPAF_$(PORT_UPPER)_GUI_$(NAME_UPPER)_H

#include <cpaf/$(PORT_LOWER)/gui/$(BASE_LOWER).h>
#include <cpaf/api/gui/$(NAME_LOWER).h>
#include <cpaf/gui/$(NAME_LOWER).h>

namespace cpaf {
    namespace $(PORT_LOWER) {
        namespace gui {

class $(NAME) : public virtual cpaf::$(PORT_LOWER)::gui::$(BASE), public virtual cpaf::api::gui::$(NAME)
{
public:
$(IF CONSTRUCTABLE)
    void create(const cpaf::gui::initializer::$(NAME)Data &params);
$(END)
};

        } // gui
    } // $(PORT_LOWER)
} // cpaf

#endif // CPAF_$(PORT_UPPER)_GUI_$(NAME_UPPER)_H
