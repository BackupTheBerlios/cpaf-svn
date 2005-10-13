/*!
    \file include/cpaf/api/gui/button.h
    \brief Button interface declaration
    \date Created: 2005-04-05
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

#ifndef CPAF_API_GUI_BUTTON_H
#define CPAF_API_GUI_BUTTON_H

#include <cpaf/gui/initializer/button.h>
#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class Button : public virtual Widget
{
    //! \todo "Controls" need a common base (checkboxes, radio, ...)
public:
    typedef cpaf::gui::initializer::ButtonData data_type; //!< Initialization data used for Buttons

    virtual void create(const data_type &init_params) = 0;
    virtual void set_label(const std::string &label) = 0;
    virtual std::string get_label() = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_BUTTON_H
