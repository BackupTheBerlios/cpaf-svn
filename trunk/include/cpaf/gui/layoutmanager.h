/*!
    \file include/cpaf/gui/layoutmanager.h
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

#include <cpaf/gui/object.h>

namespace cpaf{
    namespace gui {
        class Widget;

/*!
    Base class for layout managers
*/
class CPAF_API LayoutManager : public Object
{
public:
    typedef cpaf::api::gui::LayoutManager api_type;

    /*!
        Updates the position and size of all managed widgets
    */
    void do_layout(const cpaf::Size &size);

    /*!
        Removes an object from this layout manager.
    */
    void remove(boost::weak_ptr<Widget> widget);

protected:
    LayoutManager(api_type *impl);

private:
    api_type *m_impl;

protected:
    template<typename T> T* get_impl()
    {
        return dynamic_cast<T*>(m_impl);
    }

public:
    virtual ~LayoutManager();
};

    } // gui
} // cpaf

#endif
