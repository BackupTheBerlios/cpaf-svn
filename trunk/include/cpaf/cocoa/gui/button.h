/*!
    \file include/cpaf/cocoa/gui/button.h
    \brief Cocoa version of api::Button
    \date Created: 2005-04-29
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

    Copyright (C) 2005 Thomas Steinacher
    http://www.eggdrop.ch/
    tom (at) eggdrop [dot] ch
*/

#ifndef CPAF_COCOA_GUI_BUTTON_H
#define CPAF_COCOA_GUI_BUTTON_H

#include <cpaf/cocoa/gui/widget.h>
#include <cpaf/api/gui/button.h>
#include <cpaf/private/factory.h>

namespace cpaf {
    namespace cocoa {
        namespace gui {

class Button : public virtual cpaf::cocoa::gui::Widget, public virtual cpaf::api::gui::Button
{
public:
    Button() { };
    void create(const cpaf::gui::initializer::ButtonData &params);

    virtual void set_label(const std::string &label);
    virtual std::string get_label();

protected:
};

        } // gui
    } // cocoa
} // cpaf

#endif // CPAF_COCOA_GUI_BUTTON_H
