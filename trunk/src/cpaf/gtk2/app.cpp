/**
 * \file src/cpaf/gtk2/app.cpp
 * \brief Implementation of cpaf::gui::App::run() for gtk2
 * \date 2005-04-07
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
