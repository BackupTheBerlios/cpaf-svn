/*!
    \file src/cpaf/gui/app.cpp
    \brief Implementation of cpaf::gui::App
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
*/

#include <cpaf/gui/app.h>
#include <cpaf/gui/toplevel.h>
#include <cpaf/api/gui/EventLoop.h>

using namespace cpaf::gui;

namespace {
    TopLevelList top_level_widgets;
}

App::App()
: m_event_loop(new cpaf::gui::EventLoop)
{
    // implementation specific gui initialization
    gui_init();
}

void App::run()
{
    // run the event loop
    m_event_loop->run();
}

void App::quit()
{
    //! \todo send APP_QUIT

    // close all top levels
    for( TopLevelList::const_iterator i = get_top_level_widgets().begin(), end = get_top_level_widgets().end(); i != end; )
    {
        TopLevel *t = *i;

        // increment the iterator before we close the TopLevel
        // the act of closing the TopLevel could invalidate the iterator if we didnt.
        ++i;

        //! \todo call close() instead of destroy()
        t->destroy();
    }

    // tell the implementation to terminate the application
    _quit();
}

const TopLevelList &App::get_top_level_widgets()
{
    return top_level_widgets;
}

void App::add_top_level(TopLevel *t)
{
    top_level_widgets.push_back(t);
}

void App::remove_top_level(TopLevel *t)
{
    top_level_widgets.remove(t);
}
