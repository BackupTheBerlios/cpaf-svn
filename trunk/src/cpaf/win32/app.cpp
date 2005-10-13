/*!
    \file src/cpaf/win32/app.cpp
    \brief Implementation of the parts of cpaf::gui::App which are implementation specific.
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

#include <cpaf/win32/win.h>
#include <cpaf/gui/app.h>
#include <cpaf/win32/exception.h>

#include <commctrl.h>

using namespace cpaf::win32::gui;

void cpaf::gui::App::gui_init()
{
    // initialize common controls
    ::InitCommonControls();
}

void cpaf::gui::App::_quit()
{
    ::PostQuitMessage(0);
}
