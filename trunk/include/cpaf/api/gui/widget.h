/*!
    \file include/cpaf/api/gui/widget.h
    \brief Widget interface declaration
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

#ifndef CPAF_API_GUI_WIDGET_H
#define CPAF_API_GUI_WIDGET_H

#include <cpaf/gui/initializer/widget.h>
#include <cpaf/api/gui/object.h>

namespace cpaf {
    namespace gui { class Panel; class Window; }
    namespace api {
        namespace gui {

class Widget : public virtual Object
{
public:
    typedef cpaf::gui::initializer::WidgetData data_type; //!< Initialization data used for Widgets.

    virtual void *get_handle() const = 0;
    virtual void enable(bool e) = 0;
    virtual void show(bool show, bool focus) = 0;
    virtual bool is_enabled() const = 0;
    virtual bool is_shown() const = 0;
    virtual void destroy() = 0;

    virtual boost::shared_ptr<cpaf::gui::Panel> get_parent() const = 0;
    virtual boost::shared_ptr<cpaf::gui::Window> get_parent_window() const = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_WIDGET_H
