/*!
    \file src\cpaf\layout_manager.h
    \brief Layout Manager declarations
    \date Created: 2005-08-24
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

#ifndef CPAF_GUI_LAYOUTMANAGER_H
#define CPAF_GUI_LAYOUTMANAGER_H

#include <cpaf/dllimpexp.h>
#include <cpaf/types.h>
#include <boost/shared_ptr.hpp>

namespace cpaf{
    namespace gui {

        class Widget;

/*!
    Base class for layout managers
    \todo pimpl
*/
class CPAF_API LayoutManager
{
public:
    /*!
        Updates the position and size of all managed widgets
    */
    virtual void do_layout(const cpaf::Size &size) = 0;

    /*!
        Removes an object from this layout manager.
    */
    virtual void remove(boost::shared_ptr<Widget> widget) = 0;

protected:
    /*!
        Sets the position for a given widget
    */
    void set_widget_pos(Widget *widget, const cpaf::Point &pos);

    /*!
        Sets the size for a given widget
    */
    void set_widget_size(Widget *widget, const cpaf::Size &size);

    /*!
        Sets the rect for a given widget
    */
    void set_widget_rect(Widget *widget, const cpaf::Rect &rect);

public:
    virtual ~LayoutManager();
};

    } // gui
} // cpaf

#endif
