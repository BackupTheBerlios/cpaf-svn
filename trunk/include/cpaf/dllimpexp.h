/*!
    \file include/cpaf/dllimpexp.h
    \brief Contains helper macros for exporting and importing symbols from cpaf dynamic library builds
    \date Created: 2005-04-05
*/

#ifndef CPAF_DLLIMPEXP_H
#define CPAF_DLLIMPEXP_H

#ifdef CPAF_WIN32
#   define CPAF_IMPORT __declspec(dllimport)
#   define CPAF_EXPORT __declspec(dllexport)
#   define CPAF_DLL_LOCAL
#   define CPAF_DLL_PUBLIC
#else
#   define CPAF_IMPORT
#   if __GNUC__ >= 4 // Using GCC which has C++ visibility support
#       define CPAF_EXPORT      __attribute__ ((visibility("default")))
#       define CPAF_DLL_LOCAL   __attribute__ ((visibility("hidden")))
// A macro for default visibility without __declspec(dllexport) on win32.
// Do we ever need this? Also, do we need a macro for __declspec(dllexport)
// only, without default visibility? - class forward declarations?
#       define CPAF_DLL_PUBLIC  __attribute__ ((visibility("default")))
#   else
#       define CPAF_EXPORT
#       define CPAF_DLL_LOCAL
#       define CPAF_DLL_PUBLIC
#   endif
#endif // !CPAF_WIN32

// For every non-templated class definition in the library (both header and
// source files), decide if it is publicially use or internally used:
// * If it's publicially used, mark with CPAF_API like "class CPAF_API PublicClass"
// * If it's only internally used, optionally mark with CPAF_DLL_LOCAL like
//   "class CPAF_DLL_LOCAL PrivateClass". It is probably better to not use
//   CPAF_DLL_LOCAL at all, and instead make sure every API interface is
//   marked with CPAF_API, and enforce the usage of -fvisibility=hidden in
//   our Makefile's CXXFLAGS when the compiler is gcc4 or newer. Some more
//   research required to make the final decision on that.
#ifdef CPAF_DLL
#   ifdef CPAF_BUILDING // Use the more standard CPAF_EXPORTS instead?
#       define CPAF_API CPAF_EXPORT
#   else
#       define CPAF_API CPAF_IMPORT
#   endif
#else
#   define CPAF_API
#endif

// Use CPAF_EXCEPTION_API(CPAF_API) for exceptions that can be thrown
// across a shared object boundary, like this:
// "class CPAF_EXCEPTION_API(CPAF_API) PublicThrowableClass"
// No need to do this for types which are never thrown across the shared
// object bounary. That is, don't use this if the application must not be
// able to catch the exception.
#ifdef CPAF_WIN32
#   define CPAF_EXCEPTION_API(api) api
#elif __GNUC__ >= 4 // Using GCC which has C++ visibility support
#   define CPAF_EXCEPTION_API(api) CPAF_EXPORT
#else
#   define CPAF_EXCEPTION_API(api)
#endif

#endif // CPAF_DLLIMPEXP_H
