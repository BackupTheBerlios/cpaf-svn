/*!
    \file src/cpaf/gtk2/factory.cpp
    \brief Implementation of gtk2 factory
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
#include <cpaf/gtk2/gui/window.h>
#include <cpaf/gtk2/gui/button.h>
#include <cpaf/gtk2/gui/entrybox.h>
#include <cpaf/gtk2/gui/textbox.h>
#include <cpaf/gtk2/gui/panel.h>

IMPLEMENT_WIDGET_FACTORY(Window, gtk2)
IMPLEMENT_WIDGET_FACTORY(Button, gtk2)
IMPLEMENT_WIDGET_FACTORY(EntryBox, gtk2)
IMPLEMENT_WIDGET_FACTORY(TextBox, gtk2)
IMPLEMENT_WIDGET_FACTORY(Panel, gtk2)
