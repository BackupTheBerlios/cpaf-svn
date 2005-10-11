/*!
    \file include/cpaf/gui/panel.h
    \brief cpaf::gui::Panel declaration
    \date Created: 
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

#ifndef CPAF_GUI_PANEL_H
#define CPAF_GUI_PANEL_H

#include <cpaf/gui/widget.h>
#include <cpaf/gui/initializer/panel.h>

namespace cpaf {
    namespace gui {

class CPAF_API Panel : public Widget
{
public:
    typedef cpaf::api::gui::Panel api_type;
    typedef PanelInitializer Initializer;

    static boost::shared_ptr<Panel> create(const Initializer &initializer);

private:
    api_type *m_impl;

protected:
    Panel();
    Panel(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initializer
    */
    boost::shared_ptr<Panel> initialize(const Initializer &initializer);

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_PANEL_H
