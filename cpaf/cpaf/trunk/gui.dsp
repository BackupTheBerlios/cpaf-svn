# Microsoft Developer Studio Project File - Name="gui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=gui - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gui.mak" CFG="gui - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gui - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gui - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build/Release"
# PROP Intermediate_Dir "build/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GUI_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "CPAF_WIN32" /D "CPAF_DLL" /D "CPAF_BUILDING" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GUI_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"build/cpaf-gui-win32.dll" /implib:"build/cpaf-gui-win32.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build/Debug"
# PROP Intermediate_Dir "build/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GUI_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "CPAF_WIN32" /D "CPAF_DLL" /D "CPAF_BUILDING" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GUI_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"build/cpaf-gui-win32d.dll" /implib:"build/cpaf-gui-win32d.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "gui - Win32 Release"
# Name "gui - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "cpaf_s"

# PROP Default_Filter ""
# Begin Group ".gui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cpaf\gui\app.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/gui/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\button.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/gui/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\factory.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/gui/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\object.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/gui/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\toplevel.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/gui/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\widget.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/gui/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gui\window.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/gui/Debug"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\src\cpaf\api.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\app.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\main.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "win32_s"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cpaf\win32\app.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/win32/Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/win32/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\button.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/win32/Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/win32/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\factory.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/win32/Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/win32/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\widget.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/win32/Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/win32/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\win.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/win32/Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/win32/Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\win32\window.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/win32/Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/win32/Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "gtk2_s"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cpaf\gtk2\app.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\factory.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\utils.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\widget.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cpaf\gtk2\window.cpp

!IF  "$(CFG)" == "gui - Win32 Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "cpaf_h"

# PROP Default_Filter ""
# Begin Group "private"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\cpaf\private\factory.h

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/Debug"

!ENDIF 

# End Source File
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

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP Intermediate_Dir "build/Release"

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP Intermediate_Dir "build/Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "api"

# PROP Default_Filter ""
# Begin Group "_gui"

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
# Begin Source File

SOURCE=.\include\cpaf\app.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\defs.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\dllimpexp.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\main.h
# End Source File
# End Group
# Begin Group "win32_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\cpaf\win32\gui\button.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\win32\factory.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\win32\gui\widget.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\win32\win.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\win32\gui\window.h
# End Source File
# End Group
# Begin Group "gtk2_h"

# PROP Default_Filter ""
# Begin Group "..gui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\cpaf\gtk2\gui\widget.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gtk2\gui\window.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\cpaf\gtk2\factory.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gtk2\gtk.h
# End Source File
# Begin Source File

SOURCE=.\include\cpaf\gtk2\utils.h
# End Source File
# End Group
# Begin Source File

SOURCE=".\include\cpaf\gui\api-prototypes.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\doxygen\glossary.dox
# End Source File
# End Group
# End Target
# End Project
