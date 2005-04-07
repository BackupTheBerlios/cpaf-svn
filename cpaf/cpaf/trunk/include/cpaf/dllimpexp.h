/*
Defines for __declspec(dllexport) and __declspec(dllimport)
*/

#ifndef _CPAF_DLLIMPEXP_H_
#define _CPAF_DLLIMPEXP_H_

#ifdef CPAF_WIN32
#   ifdef CPAF_DLL
#       ifdef CPAF_BUILDING
#           define CPAF_EXP __declspec(dllexport)
#       else
#           define CPAF_EXP __declspec(dllimport)
#       endif
#   else
#       define CPAF_EXP
#   endif
#else
#   define CPAF_EXP
#endif

#endif // _CPAF_DLLIMPEXP_H_
