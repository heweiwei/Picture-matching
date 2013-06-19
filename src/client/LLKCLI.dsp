# Microsoft Developer Studio Project File - Name="LLKCLI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LLKCLI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LLKCLI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LLKCLI.mak" CFG="LLKCLI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LLKCLI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LLKCLI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LLKCLI - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "LLKCLI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LLKCLI - Win32 Release"
# Name "LLKCLI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\GifAnimation.cpp
# End Source File
# Begin Source File

SOURCE=.\LLKBgReady.cpp
# End Source File
# Begin Source File

SOURCE=.\LLKChangePwd.cpp
# End Source File
# Begin Source File

SOURCE=.\LLKCLI.cpp
# End Source File
# Begin Source File

SOURCE=.\LLKCLI.rc
# End Source File
# Begin Source File

SOURCE=.\LLKCLIDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LLKGame.cpp
# End Source File
# Begin Source File

SOURCE=.\LLKHome.cpp
# End Source File
# Begin Source File

SOURCE=.\LLKReg.cpp
# End Source File
# Begin Source File

SOURCE=.\Scorelist.cpp
# End Source File
# Begin Source File

SOURCE=.\SockThd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\winimage.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\GifAnimation.h
# End Source File
# Begin Source File

SOURCE=.\LLKBgReady.h
# End Source File
# Begin Source File

SOURCE=.\LLKChangePwd.h
# End Source File
# Begin Source File

SOURCE=.\LLKCLI.h
# End Source File
# Begin Source File

SOURCE=.\LLKCLIDlg.h
# End Source File
# Begin Source File

SOURCE=.\LLKGame.h
# End Source File
# Begin Source File

SOURCE=.\LLKHome.h
# End Source File
# Begin Source File

SOURCE=.\LLKReg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Scorelist.h
# End Source File
# Begin Source File

SOURCE=.\SockThd.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\winimage.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bkimage.bmp
# End Source File
# Begin Source File

SOURCE=.\res\boom33x38.bmp
# End Source File
# Begin Source File

SOURCE=.\res\botton_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\botton_Focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\changePwd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\changePwd_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\expand.bmp
# End Source File
# Begin Source File

SOURCE=.\res\expand_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gamebox2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\home.bmp
# End Source File
# Begin Source File

SOURCE=.\res\lighting.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LLKCLI.ico
# End Source File
# Begin Source File

SOURCE=.\res\LLKCLI.rc2
# End Source File
# Begin Source File

SOURCE=.\res\mousedown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mousemove.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PICer2012571038.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ReadyInterface1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ReadyInterface2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Score_list.bmp
# End Source File
# Begin Source File

SOURCE=.\res\start.bmp
# End Source File
# Begin Source File

SOURCE=.\res\start_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\table.bmp
# End Source File
# Begin Source File

SOURCE=.\res\table_ON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tablen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\test.bmp
# End Source File
# Begin Source File

SOURCE=.\res\test_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
