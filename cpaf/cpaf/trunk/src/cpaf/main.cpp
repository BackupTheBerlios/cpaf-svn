/*
win32 entry function implementation
*/

#include <cpaf/main.h>
//#include <boost/scoped_ptr.hpp>
#include <memory> // for auto_ptr

// \todo Construct the command line vector and pass it to main()

#ifdef CPAF_WIN32

int cpaf::entry(cpaf::main_ptr main, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    cpaf::App::cmd_line cmd;

    // get an application instance
    //boost::scoped_ptr<cpaf::App> app(main(cmd));
    std::auto_ptr<cpaf::App> app(main(cmd));

    app->set_cmd_line(cmd);
    app->init();
    return app->run();
}

#else // !CPAF_WIN32

int cpaf::entry(cpaf::main_ptr main, int argc, char *argv[])
{
#ifdef CPAF_GTK2
    extern void register_argc_argv(int argc, char *argv[]);
    register_argc_argv(argc, argv);
#endif

    cpaf::App::cmd_line cmd;

    // get an application instance
    //boost::scoped_ptr<cpaf::App> app(main(cmd));
    std::auto_ptr<cpaf::App> app(main(cmd));

    app->set_cmd_line(cmd);
    app->init();
    return app->run();
}

#endif
