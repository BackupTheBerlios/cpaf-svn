/*
win32 entry function implementation
*/

#include <cpaf/main.h>
#include <boost/scoped_ptr.hpp>

// \todo Construct the command line vector and pass it to main_ptr()

#ifdef CPAF_WIN32

int cpaf::cpaf_entry(main_ptr main, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // get an application instance
    boost::scoped_ptr<cpaf::App> app(main());

    app->init();
    return app->run();
}

#else // !CPAF_WIN32

// LEIO: you should store argc and argv somewhere for use via gui gtk2 projects
int cpaf::cpaf_entry(main_ptr main, int argc, char *argv[])
{
    // get an application instance
    boost::scoped_ptr<cpaf::App> app(main());

    app->init();
    return app->run();
}

#endif
