/*!
    \file include/cpaf/api/gui/window.h
    \brief Window interface declaration
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

#ifndef CPAF_API_GUI_WINDOW_H
#define CPAF_API_GUI_WINDOW_H

#include <cpaf/gui/initializer/window.h>
#include <cpaf/api/gui/toplevel.h>

namespace cpaf {
    namespace gui { class Panel; }
    namespace api {
        namespace gui {

class Panel;

class Window : public virtual TopLevel
{
public:
    typedef cpaf::gui::initializer::WindowData data_type; //!< Initialization data used for Windows

    virtual void create(const data_type &init_params) = 0;

    virtual void set_min_content_size(const cpaf::Size&) = 0;
    virtual void set_max_content_size(const cpaf::Size&) = 0;
    virtual cpaf::Size get_min_content_size() const = 0;
    virtual cpaf::Size get_max_content_size() const = 0;

    virtual void set_content_panel(cpaf::api::gui::Panel *p) = 0;
    virtual boost::shared_ptr<cpaf::gui::Panel> get_content_panel() const = 0;
};

        } // gui
    } // api
} // cpaf

#endif // CPAF_API_GUI_WINDOW_H
