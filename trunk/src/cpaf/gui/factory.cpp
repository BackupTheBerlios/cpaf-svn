/*!
    \file src/cpaf/gui/factory.cpp
    \brief Implementation for things in the cpaf::gui::factory namespace
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

#include <cpaf/private/factory.h>

int cpaf::gui::factory::get_unique_object_id()
{
    static int next;
    return ++next;
}

/*
// include this because a full declaration of api::gui::Widget is required
// to call the proper destructors by delete_widget_implementation
#include <cpaf/api/gui/widget.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/api/gui/window.h>

namespace {
    cpaf::gui::factory::WidgetImplementationWrapperMap widget_impl_map;
}

// adds a wrappper implementation pair to the map
void cpaf::gui::factory::add_implementation_wrapper(cpaf::api::gui::Widget *impl, cpaf::gui::Widget* wrapper)
{
    widget_impl_map[impl] = wrapper;
}

void cpaf::gui::factory::remove_implementation_wrapper(cpaf::api::gui::Widget *impl)
{
    WidgetImplementationWrapperMap::iterator i = widget_impl_map.find(impl);

    if( i != widget_impl_map.end() )
        widget_impl_map.erase(i);
    //! \todo I should throw here
}

// called by gui::Foo destructors to delete their implementations only if the impl pointer is
// in the map
void cpaf::gui::factory::delete_widget_implementation(cpaf::api::gui::Widget *impl)
{
    WidgetImplementationWrapperMap::iterator i = widget_impl_map.find(impl);

    // if we found it...
    if( i != widget_impl_map.end() )
    {
        // remove it
        widget_impl_map.erase(i);

        // and delete the implementation
        delete impl;
    }
}

// called by implementation destructors to delete their gui wrappers only if the implementation
// pointer is in the map
void cpaf::gui::factory::delete_implementation_wrapper(cpaf::api::gui::Widget *impl)
{
    WidgetImplementationWrapperMap::iterator i = widget_impl_map.find(impl);

    // if we found it...
    if( i != widget_impl_map.end() )
    {
        // store the thing to delete later
        cpaf::gui::Widget *wrapper = i->second;

        // remove it
        widget_impl_map.erase(i);

        // and delete the wrapper
        delete wrapper;
    }
}
*/
