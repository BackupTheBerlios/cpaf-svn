/*!
    \file include/cpaf/gtk2/panel.h
    \brief gtk2 version of cpaf::api::gui::Panel
    \date Created: 2005-08-08
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

#ifndef CPAF_GTK2_GUI_PANEL_H
#define CPAF_GTK2_GUI_PANEL_H

#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/api/gui/panel.h>
#include <cpaf/gui/panel.h>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class Panel : public virtual cpaf::gtk2::gui::Widget, public virtual cpaf::api::gui::Panel
{
public:
    Panel();
    ~Panel();

    void create(const cpaf::gui::initializer::PanelData &params);

    // Implementation specific
    boost::shared_ptr<LayoutManager> m_layout_manager;
    int m_last_width;
    int m_last_height;
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_PANEL_H
