/*!
    \file src/cpaf/main.cpp
    \brief Implementation of the entry function
    \date Created: 2005-04-05
*/

#include <cpaf/main.h>
//#include <boost/scoped_ptr.hpp>
#include <memory> // for auto_ptr
#include <cpaf/exception.h>
#include <exception>

namespace {
    cpaf::App *the_app; // pointer to the application instance
}

#ifdef CPAF_WIN32
#include <crtdbg.h>
#include <cpaf/win32/exception.h>

//! \todo Construct the command line vector and pass it to main()
//! \todo Find some way to prevent common code duplication between functions

int cpaf::entry(cpaf::main_ptr main, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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
        return app->run();
    }
    catch(cpaf::win32::Exception &e)
    {
        ::_CrtDbgReport(_CRT_ERROR, e.get_file(), e.get_line(), 0, "Exception: %s, Win32 code: %d", e.get_message(), e.get_win32_error());
        return 1;
    }
    catch(cpaf::Exception &e)
    {
        ::MessageBoxA(0, e.get_message(), e.get_file(), MB_ICONERROR);
        return 1;
    }
    catch(bad_cast e)
    {
        ::MessageBoxA(0, e.what(), "A bad cast was encountered", MB_ICONERROR);
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
        return app->run();
    }
    catch(cpaf::Exception &e)
    {
        printf("%s: %s\n", e.get_file(), e.get_message());
        return 1;
    }
    catch(std::exception &e)
    {
        printf("Exception: %s\n", e.what());
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
