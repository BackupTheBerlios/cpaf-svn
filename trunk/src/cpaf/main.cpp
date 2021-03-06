/*!
    \file src/cpaf/main.cpp
    \brief Implementation of the entry function
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

#include <cpaf/main.h>
//#include <boost/scoped_ptr.hpp>
#include <memory> // for auto_ptr
#include <cpaf/exception.h>
#include <exception>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#endif

#include <cpaf/debug.h>

namespace {
    cpaf::App *the_app; // pointer to the application instance
}

#ifdef CPAF_WIN32
#include <cpaf/win32/exception.h>

//! \todo Construct the command line vector and pass it to main()
//! \todo Find some way to prevent common code duplication between functions

int cpaf::entry(cpaf::main_ptr main, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _MSC_VER
    // enable memory leak detection
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // the end-all exception handling block
    try
    {
        cpaf::App::cmd_line cmd;

        // get an application instance
        std::auto_ptr<cpaf::App> app(main(cmd));

        // store the application instance
        the_app = app.get();

        app->set_cmd_line(cmd);
        app->init();
        app->run();

        //! \todo Provide proper return code facility
        return 0;
    }
    catch(cpaf::win32::Exception &e)
    {
        cpaf::DebugReport(cpaf::DebugReport::ERROR, e.get_file(), e.get_line()) << "Exception: " << e.what() << "\nWin32 code: " << e.get_win32_error();
        return 1;
    }
    catch(cpaf::Exception &e)
    {
        cpaf::DebugReport(cpaf::DebugReport::ERROR, e.get_file(), e.get_line()) << "Exception: " << e.what();
        return 1;
    }
    catch(std::exception &e)
    {
        cpaf::DebugReport(cpaf::DebugReport::ERROR) << "Exception: " << e.what();
        return 1;
    }
    /*catch(...)
    {
        ::MessageBoxA(0, "An unknown exception has been encountered.", 0, MB_ICONERROR);
        return 1; // errornous termination
    }*/
}

#else // !CPAF_WIN32

int cpaf::entry(cpaf::main_ptr main, int argc, char *argv[])
{
    extern void register_argc_argv(int argc, char *argv[]);
    register_argc_argv(argc, argv);

    // the end-all exception handling block
    try
    {
        cpaf::App::cmd_line cmd;

        // get an application instance
        std::auto_ptr<cpaf::App> app(main(cmd));

        // store the application instance
        the_app = app.get();

        app->set_cmd_line(cmd);
        app->init();
        app->run();

        //! \todo Provide proper return code facility
        return 0;
    }
    catch(cpaf::Exception &e)
    {
        cpaf::DebugReport(cpaf::DebugReport::ERROR, e.get_file(), e.get_line()) << "Exception: " << e.what();
        return 1;
    }
    catch(std::exception &e)
    {
        // the second argument is 0 to work around a bug in Apple's g++ 3.3
        cpaf::DebugReport(cpaf::DebugReport::ERROR, 0) << "Exception: " << e.what();
        return 1;
    }
    catch(...)
    {
        printf("An unknown exception has been encountered.\n");
        return 1; // errornous termination
    }
}

#endif

cpaf::App &cpaf::get_app()
{
    return *the_app;
}
