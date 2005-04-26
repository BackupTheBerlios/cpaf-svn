/*
win32 entry function implementation
*/

#include <cpaf/main.h>
//#include <boost/scoped_ptr.hpp>
#include <memory> // for auto_ptr
#include <cpaf/exception.h>
#include <exception>

#ifdef CPAF_WIN32
//! \todo What does this do? Do we need the set_terminate for other ports?
void term_handler()
{
    ::MessageBox(0, "term_handler", 0, 0);
}

//! \todo Construct the command line vector and pass it to main()
//! \todo Find some way to prevent common code duplication between functions

int cpaf::entry(cpaf::main_ptr main, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    std::set_terminate(term_handler);

    // the end-all exception handling block
    try
    {
        cpaf::App::cmd_line cmd;

        // get an application instance
        std::auto_ptr<cpaf::App> app(main(cmd));

        app->set_cmd_line(cmd);
        app->init();
        return app->run();
    }
    catch(cpaf::Exception &e)
    {
        ::MessageBoxA(0, e.get_message(), e.get_file(), MB_ICONERROR);
        return 1;
    }
    catch(...)
    {
        ::MessageBoxA(0, "An unknown exception has been encountered.", 0, MB_ICONERROR);
        return 1; // errornous termination
    }
}

#else // !CPAF_WIN32

int cpaf::entry(cpaf::main_ptr main, int argc, char *argv[])
{
#ifdef CPAF_GTK2
    extern void register_argc_argv(int argc, char *argv[]);
    register_argc_argv(argc, argv);
#endif

    // the end-all exception handling block
    try
    {
        cpaf::App::cmd_line cmd;

        // get an application instance
        std::auto_ptr<cpaf::App> app(main(cmd));

        app->set_cmd_line(cmd);
        app->init();
        return app->run();
    }
    catch(...)
    {
        return 1; // erroneous termination
    }
}

#endif
