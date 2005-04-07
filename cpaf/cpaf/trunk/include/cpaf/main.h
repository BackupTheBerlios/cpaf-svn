/*
Header file which declares the cpaf::main() entry function.

This file also declares the platform specific entry function. This function
is implemented within the library.
*/

#ifndef CPAF_MAIN_H
#define CPAF_MAIN_H

#include <cpaf/app.h>
#include <cpaf/dllimpexp.h>

#ifdef CPAF_WIN32
#include <windows.h>
#endif

namespace cpaf {

/*!
    Called by the library, implemented by an application. The purpose of this function is to 
    return a cpaf::App derived object which will be used to run the application.
*/
cpaf::App *main();
typedef cpaf::App *(main_ptr)();

// win32 has a different entry function, and cpaf_entry function than other ports
#ifdef CPAF_WIN32
    int CPAF_EXP cpaf_entry(main_ptr, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else // !CPAF_WIN32
    int CPAF_EXP cpaf_entry(main_ptr, int argc, char *argv[]);
#endif // CPAF_WIN32

} // cpaf

// platform specific entry function
// only include this part in user applications

/*
Explanation for the following code:

  The plan is to avoid requiring an IMPLEMENT_APP macro which declares the entry functions 
  and all of that wx nonesense. Instead of the macro, cpaf uses cpaf::main() as an applications
  first entry point. cpaf::main() is expected to create a cpaf::App derivative and give that
  object to cpaf. This cpaf::App object is the actual application, and all further code execution
  is routed through this class.

  Because win32 dll's are not capable of calling a function defined in an application dll and prototyped
  in the dll headers, I cannot put the entry functions into the cpaf library itself. To work around this
  restriction, I declare and implement them here, heavily if guarded. I realize this file could be included
  in two different source files, which causes multiply defined sybmols, but that is the fault of the programmer
  as this file is only required to be included once.

  The purpose of cpaf::cpaf_entry is to avoid implementing more code than is neccessary in this header file,
  allowing for at least slight binary compatability between changes so long as this header file is not modified.
  cpaf_entry will call app->init(), and app->run() to actually run the application.

  I realize that the code for non win32 systems prevents access to the command line. Once cpaf provides
  command line facilities, I will update this entry function to reflect that.

  cpef_entry is given a pointer to the cpaf::main() function, as well as 
*/
#if !defined(CPAF_ENTRY_IMPLEMENTED) && !defined(CPAF_BUILDING)
#define CPAF_ENTRY_IMPLEMENTED

#ifdef CPAF_WIN32
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
        return cpaf::cpaf_entry(cpaf::main, hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    }
#else // !CPAF_WIN32
    int main(int argc, char *argv[])
    {
        return cpaf::cpaf_entry(cpaf::main, argc, argv);
    }
#endif // CPAF_WIN32

#endif // CPAF_ENTRY_IMPLEMENTED

#endif // CPAF_MAIN_H
