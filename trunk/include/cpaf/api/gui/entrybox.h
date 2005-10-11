/*!
    \file include/cpaf/api/gui/entrybox.h
    \brief EntryBox interface declaration
    \date Created: 2005-07-14
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

#ifndef CPAF_API_GUI_ENTRYBOX_H
#define CPAF_API_GUI_ENTRYBOX_H

#include <cpaf/gui/initializer/entrybox.h>
#include <cpaf/api/gui/textwidget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class EntryBox : public virtual TextWidget
{
public:
    typedef cpaf::gui::initializer::EntryBoxData data_type; //!< Initialization data used for EntryBoxes.

    virtual void create(const data_type &init_params) = 0;
    virtual void set_password_mode(bool mode) = 0;
    virtual bool get_password_mode() = 0;
};

        } // gui
    } // api
} // cpaf

#endif
