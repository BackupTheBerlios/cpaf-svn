/*!
    \file include/cpaf/gui/object.h
    \brief cpaf::gui::Object declaration
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

#ifndef CPAF_GUI_OBJECT_H
#define CPAF_GUI_OBJECT_H
/*
#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/types.h>

namespace cpaf {
    namespace gui {

class CPAF_API Object
{
public:
    typedef cpaf::api::gui::Object api_type;

public:
    virtual ~Object();

    void set_size(const cpaf::Size &s);
    void set_min_size(const cpaf::Size &s);
    void set_max_size(const cpaf::Size &s);
    void set_position(const cpaf::Point &p);
    cpaf::Size get_size();
    cpaf::Size get_min_size();
    cpaf::Size get_max_size();
    cpaf::Point get_position();

private:
    cpaf::api::gui::Object *m_impl;

protected:
    Object(cpaf::api::gui::Object *impl);

public:
    api_type *get_impl() const;
};
*/
    } // gui
} // cpaf

#endif // CPAF_GUI_OBJECT_H
