/*
Defines for __declspec(dllexport) and __declspec(dllimport)
*/

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
