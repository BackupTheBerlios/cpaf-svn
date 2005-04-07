/*
Header file which declares the cpaf::main() entry function.

This file also declares the platform specific entry function. This function
is implemented within the library.
*/

#ifndef CPAF_MAIN_H
#define CPAF_MAIN_H

#include <boost/scoped_ptr.hpp>
#include <cpaf/app.h>
#include <cpaf/dllimpexp.h>

namespace cpaf {

/*!
    Called by the library, implemented by an application. The purpose of this function is to 
    return a cpaf::App derived object which will be used to run the application.
*/
cpaf::App *main();
int CPAF_EXP cpaf_entry(cpaf::App *app);

} // cpaf

// platform specific entry function
// only include this part in user applications
#if !defined(CPAF_ENTRY_IMPLEMENTED) && !defined(CPAF_BUILDING)
#define CPAF_ENTRY_IMPLEMENTED

#ifdef CPAF_WIN32
    #include <windows.h>
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else // !CPAF_WIN32
    int main(int argc, char *argv[])
#endif
    {
        boost::scoped_ptr<cpaf::App> app(cpaf::main());
        return cpaf::cpaf_entry(app.get());
    }

#endif // CPAF_ENTRY_IMPLEMENTED

#endif // CPAF_MAIN_H
