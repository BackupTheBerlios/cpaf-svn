/*!
    \file src/cpaf/gtk2/app.cpp
    \brief Implementation of cpaf::gui::App::run() for gtk2
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

#include <gtk/gtk.h>

namespace {
    int s_argc;
    char **s_argv;
}

void register_argc_argv(int argc, char *argv[])
{
    s_argc = argc;
    s_argv = argv;
}


void cpaf::gui::App::gui_init()
{
    if (!gtk_init_check(&s_argc, &s_argv))
    {
        //! \todo throw exception
    }
}

int cpaf::gui::App::run()
{
    gtk_main();

    //! \todo return the exit code value instead of 0
    return 0;
}

void cpaf::gui::App::_quit()
{

}
