/*!
    \file include/cpaf/api/gui/object.h
    \brief Object interface declaration
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

#ifndef CPAF_API_GUI_OBJECT_H
#define CPAF_API_GUI_OBJECT_H

#include <cpaf/gui/initializer/object.h>
#include <cpaf/types.h>

namespace cpaf {
    namespace api {
        namespace gui {

/*!
    \brief The Object interface represents an object that can be positioned and sized. It does
        not neccesarily represent a widget which has a presence at the system level.
*/
class Object
{
public:
    typedef cpaf::gui::initializer::ObjectData data_Type; //!< initialization data used for Objects

    // virtual dtor ensuring that all gui objects are properly destructed
    virtual ~Object();
    virtual void set_size(const cpaf::Size&) = 0;
    virtual void set_min_size(const cpaf::Size&) = 0;
    virtual void set_max_size(const cpaf::Size&) = 0;
    virtual void set_natural_size(const cpaf::Size&) = 0;
    virtual void set_position(const cpaf::Point&) = 0;
    virtual void set_rect(const cpaf::Rect&) = 0;
    virtual cpaf::Size get_size() const = 0;
    virtual cpaf::Size get_min_size() const = 0;
    virtual cpaf::Size get_max_size() const = 0;
    virtual cpaf::Size get_natural_size() const = 0;
    virtual cpaf::Point get_position() const = 0;
    virtual cpaf::Rect get_rect() const = 0;

};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_OBJECT_H
