/**
 * \file include/cpaf/macros.h
 * \brief Various macros
 * \date 2005-04-07
 */

#ifndef CPAF_MACROS_H
#define CPAF_MACROS_H

// http://www.ohse.de/uwe/articles/gcc-attributes.html seems a good overview
// of when a certain attribute was introduced to gcc

#if __GNUC__
#   define GCC_VERSION (__GNUC__ * 10000 \
                      + __GNUC_MINOR__ * 100 \
                      + __GNUC_PATCH_LEVEL)
#else
#   define GCC_VERSION 0
#endif

/*
    Microsoft Visual C++ 7.1:   _MSC_VER = 1310
    Microsoft Visual C++ 7.0:   _MSC_VER = 1300
    Microsoft Visual C++ 6.0:   _MSC_VER = 1200
    Microsoft Visual C++ 5.0:   _MSC_VER = 1100
*/

#if GCC_VERSION >= 30100
/*!
    \brief Used to mark functions, types and variables as deprecated.
    The compiler might generate a warning when the deprecated interface is used.
    Deprecated interfaces should not be used in newly-written code, and in old
    code they should be replaced with non-deprecated counterparts.
 */
#   define CPAF_DEPRECATED(x) x __attribute__((__deprecated__))
#elif _MSC_VER >= 1300
#   define CPAF_DEPRECATED(x) __declspec(deprecated) x
#else
#   define CPAF_DEPRECATED(x) x
#endif

#endif // CPAF_MACROS_H
