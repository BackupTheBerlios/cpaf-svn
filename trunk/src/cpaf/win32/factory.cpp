/*!
    \file src/cpaf/win32/factory.cpp
    \brief Implementation of win32 widget factories
    \date Created: 2005-04-07
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

    Copyright (C) 2005 Robin McNeill
    http://www.snakesoft.net
    snakechomp (at) snakesoft [dot] net
*/

#include <cpaf/private/factory.h>
#include <cpaf/win32/gui/window.h>
#include <cpaf/win32/gui/button.h>
#include <cpaf/win32/gui/textbox.h>
#include <cpaf/win32/gui/entrybox.h>
#include <cpaf/win32/gui/panel.h>

IMPLEMENT_WIDGET_FACTORY(Window, win32)
IMPLEMENT_WIDGET_FACTORY(Button, win32)
IMPLEMENT_WIDGET_FACTORY(TextBox, win32)
IMPLEMENT_WIDGET_FACTORY(EntryBox, win32)
IMPLEMENT_WIDGET_FACTORY(Panel, win32)
