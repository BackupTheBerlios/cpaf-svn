# Microsoft Developer Studio Project File - Name="cpaf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cpaf - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cpaf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cpaf.mak" CFG="cpaf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cpaf - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cpaf - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build"
# PROP Intermediate_Dir "build\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Za /W3 /GR /GX /O2 /D "NDEBUG" /D "CPAF_BUILDING" /D "_LIB" /D "CPAF_WIN32" /D "WIN32" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"build\cpaf-gui-win32.lib"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build"
# PROP Intermediate_Dir "build\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "CPAF_BUILDING" /D "_LIB" /D "CPAF_WIN32" /D "WIN32" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"build\cpaf-gui-win32d.lib"

!ENDIF 

# Begin Target

# Name "cpaf - Win32 Release"
# Name "cpaf - Win32 Debug"
# Begin Group "include"

# PROP Default_Filter ""
# Begin Group "api"

# PROP Default_Filter ""
# Begin Group "gui."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\cpaf\api\gui\button.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\api\gui\object.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\api\gui\sizer.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\api\gui\toplevel.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\api\gui\widget.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\api\gui\window.h
# End Source File
# End Group
# End Group
# Begin Group "gui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\cpaf\gui\app.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gui\button.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\private\factory.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gui\object.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gui\toplevel.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gui\widget.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gui\window.h
# End Source File
# End Group
# Begin Group "gtk2"

# PROP Default_Filter ""
# Begin Group "gui.."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\cpaf\gtk2\gui\button.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gtk2\gui\widget.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gtk2\gui\window.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\cpaf\gtk2\factory.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gtk2\gtk.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gtk2\utils.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "win32"

# PROP Default_Filter ""
# Begin Group "gui..."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\cpaf\win32\gui\button.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\win32\gui\widget.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\win32\gui\window.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\cpaf\win32\exception.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\win32\factory.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\win32\win.h
# End Source File
# End Group
# Begin Source File

SOURCE=".\include\cpaf\gui\api-prototypes.h"
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\app.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\dllimpexp.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\exception.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\macros.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\main.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\types.h
# End Source File
# End Group
# Begin Group "source"

# PROP Default_Filter ""
# Begin Group "gtk2."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cpaf\gtk2\app.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\button.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\factory.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\utils.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\widget.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\window.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "gui,"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cpaf\gui\app.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\gui\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\gui\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\button.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\gui\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\gui\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\factory.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\gui\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\gui\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\object.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\gui\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\gui\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\toplevel.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\gui\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\gui\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\widget.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\gui\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\gui\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\window.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\gui\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\gui\Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "win32."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cpaf\win32\app.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\win32\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\win32\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\button.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\win32\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\win32\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\exception.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\win32\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\factory.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\win32\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\win32\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\widget.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\win32\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\win32\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\win.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\win32\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\win32\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\window.cpp

!IF  "$(CFG)" == "cpaf - Win32 Release"

# PROP Intermediate_Dir "build\win32\Release"

!ELSEIF  "$(CFG)" == "cpaf - Win32 Debug"

# PROP Intermediate_Dir "build\win32\Debug"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\src\cpaf\api.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\app.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\exception.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\main.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cpaf\types.cpp
# End Source File
# End Group
# End Target
# End Project
