/*!
    \file include/cpaf/api/gui/toplevel.h
    \brief TopLevel interface declaration
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

#ifndef CPAF_API_GUI_TOPLEVEL_H
#define CPAF_API_GUI_TOPLEVEL_H

#include <cpaf/api/gui/widget.h>

#include <string>

namespace cpaf {
    namespace api {
        namespace gui {

class TopLevel : public virtual Widget
{
public:

    virtual void set_title(const std::string &t) = 0;
    virtual std::string get_title() = 0;
    virtual void set_client_size(const cpaf::Size &s) = 0;
    virtual cpaf::Size get_client_size() = 0;
    virtual cpaf::Point get_client_position() = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_TOPLEVEL_H
