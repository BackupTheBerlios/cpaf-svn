/*!
    \file include/cpaf/gtk2/gui/button.h
    \brief Gtk2 version of cpaf::api::gui::Button
    \date Created: 2005-04-14
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

    Copyright (C) 2005 Mart Raudsepp
    leio (at) dustbite [dot] net
*/

#ifndef CPAF_GTK2_GUI_BUTTON_H
#define CPAF_GTK2_GUI_BUTTON_H

#include <cpaf/gtk2/gui/widget.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/gui/button.h>

namespace cpaf {
    namespace gtk2 {
        namespace gui {

class Button : public virtual cpaf::gtk2::gui::Widget, public virtual cpaf::api::gui::Button
{
public:
    Button();

    void create(const cpaf::gui::initializer::ButtonData &params);

    virtual void set_label(const std::string &label);
    virtual std::string get_label();

protected:
    GtkWidget * m_label;
};

        } // gui
    } // gtk2
} // cpaf

#endif // CPAF_GTK2_GUI_BUTTON_H
