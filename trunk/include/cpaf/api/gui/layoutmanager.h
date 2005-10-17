/*!
    \file include/cpaf/api/gui/layoutmanager.h
    \brief Layout Manager declarations
    \date Created: 2005-10-16
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

#ifndef CPAF_API_GUI_LAYOUTMANAGER_H
#define CPAF_API_GUI_LAYOUTMANAGER_H

#include <cpaf/api/gui/object.h>
#include <boost/weak_ptr.hpp>

namespace cpaf {
    namespace gui { class Object; class Panel; }
    namespace api {
        namespace gui {

class LayoutManager : public virtual Object
{
public:
    virtual void assign(boost::weak_ptr<cpaf::gui::Panel>) = 0;
    virtual void remove(boost::weak_ptr<cpaf::gui::Object>) = 0;
    virtual void invalidate() = 0;
};

        } // gui
    } // api 
} // cpaf

#endif // CPAF_API_GUI_LAYOUTMANAGER_H
