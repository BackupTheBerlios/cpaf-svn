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

#include <cpaf/dllimpexp.h>
#include <cpaf/gui/api-prototypes.h>
#include <cpaf/types.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace cpaf {
    namespace gui {

class CPAF_API Object
{
public:
    typedef cpaf::api::gui::Object api_type;

public:
    /*!
        \brief Sets the minimum size of the widget. A value of 0 for width or height
        indicates that there is no minimum size in that direction.

        If the Object's current size is less than the newly specified minimum size,
        the object will be resized so that its size is equal to the newly specified
        minimum size.
    */
    void set_min_size(const cpaf::Size &s);

    /*!
        \brief Sets the maximum size of the widget. A value of 0 for width or height
        indicates that there is no maximum size in that direction.

        If the Object's current size is greater than the newly specified maximum size,
        the object will be resized so that its size is equal to the newly specified
        maximum size.
    */
    void set_max_size(const cpaf::Size &s);

    /*!
        \return Absolute size of the widget
    */
    cpaf::Size get_size() const;

    /*!
        \return Minimum size of the widget. A value of 0 for width or height
        indicates that there is no minimum size in that direction.
    */
    cpaf::Size get_min_size() const;

    /*!
        \return Maximum size of the widget. A value of 0 for width or height
        indicates that there is no maximum size in that direction.
    */
    cpaf::Size get_max_size() const;

    /*!
        Sets the natural size for this widget. The natural size is used by layout managers
        to determine how large to make widgets which are not expanded. The default natural size
        has a width and height of 0, which means that an acceptible natural size will be calculated
        for the width and height. You can override the calculated value by specifying your own value
        for the width and or height.
    */
    void set_natural_size(const cpaf::Size &s);

    /*!
        \return Natural size of the widget. The natural size is used by layout managers
        to determine how large to make widgets which are not expanded. Unless a natural
        size is explicitly specified by a call to set_natural_size or through an inintializer,
        this value is a calculated value and can vary from widget to widget and from port to port.
    */
    cpaf::Size get_natural_size() const;

    /*!
        \return Position of the widget. If the widget is a \ref g_tlw TLW, the position is in
        screen coordinates. Otherwise, the position is in client coordinates.
    */
    cpaf::Point get_position() const;

    /*!
        \return Position and Size of this widget as a rectangle.
    */
    cpaf::Rect get_rect() const;

public:
    /*!
        \brief Sets the absolute size of this widget. If the widget is a TopLevel widget,
        the value is in screen coordinates, otherwise it is client coordinates.
    */
    void set_size(const cpaf::Size &s);

    /*!
        \brief Sets the position of a widget. If the widget is a TopLevel widget,
        the position value is in screen coordinates, otherwise it is client coordinates.
    */
    void set_position(const cpaf::Point &p);

    /*!
        \brief Sets both the position and the size of the widget. If the widget
        is a TopLevel widget, the value is in screen coordinates, otherwise
        it is client coordinates.
    */
    void set_rect(const cpaf::Rect &r);

    boost::shared_ptr<api_type> m_impl;

protected:
    Object(api_type *impl);

    template<typename T> T *get_impl() const
    {
        return dynamic_cast<T*>(m_impl.get());
    }

public:
    virtual ~Object();
    api_type *get_impl() const;

    friend class cpaf::api::gui::LayoutManager;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_OBJECT_H
