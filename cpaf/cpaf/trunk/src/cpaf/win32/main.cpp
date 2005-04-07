/*
win32 entry function implementation
*/

#include <cpaf/main.h>

int cpaf::cpaf_entry(cpaf::App *app)
{
    // call the application defined entry function
    app->init();
    return app->run();
}
