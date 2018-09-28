# Microsoft Developer Studio Project File - Name="BitZam" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BitZam - Win32 Static_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BitZam.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BitZam.mak" CFG="BitZam - Win32 Static_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BitZam - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BitZam - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BitZam - Win32 Static_Debug" (based on "Win32 (x86) Application")
!MESSAGE "BitZam - Win32 Static_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BitZam - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../FTKernel_API/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 FTKernelAPI.lib FTKTCPxAPI.lib FTKUDPxAPI.lib /nologo /subsystem:windows /machine:I386 /out:"../FTKernel_API/BitZam.exe" /libpath:"../FTKernel_API/"

!ELSEIF  "$(CFG)" == "BitZam - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../FTKernel_API/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 FTKernelAPId.lib FTKTCPxAPId.lib FTKUDPxAPId.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../FTKernel_API/BitZamd.exe" /pdbtype:sept /libpath:"../FTKernel_API/"

!ELSEIF  "$(CFG)" == "BitZam - Win32 Static_Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BitZam___Win32_Static_Debug"
# PROP BASE Intermediate_Dir "BitZam___Win32_Static_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "StaticDebug"
# PROP Intermediate_Dir "StaticDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../FTKernel_API/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../FTKernel_API/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FTKernelAPId.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../FTKernel_API/BitZamd.exe" /pdbtype:sept /libpath:"../FTKernel_API/"
# ADD LINK32 FTKernelAPIsd.lib zlib.lib FTKerneld.lib HFC3000d.lib EncryptLibd.lib cryptlib.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../FTKernel_API/BitZamd_s.exe" /pdbtype:sept /libpath:"../FTKernel_API/" /libpath:"../Lib"

!ELSEIF  "$(CFG)" == "BitZam - Win32 Static_Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BitZam___Win32_Static_Release"
# PROP BASE Intermediate_Dir "BitZam___Win32_Static_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "StaticRelease"
# PROP Intermediate_Dir "StaticRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "../FTKernel_API/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../FTKernel_API/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FTKernelAPI.lib /nologo /subsystem:windows /machine:I386 /out:"../FTKernel_API/BitZam.exe" /libpath:"../FTKernel_API/"
# ADD LINK32 FTKernelAPIs.lib zlib.lib FTKernel.lib HFC3000.lib EncryptLib.lib cryptlib.lib FTKTCPxAPI.lib FTKUDPxAPI.lib  Version.lib /nologo /subsystem:windows /machine:I386 /out:"../FTKernel_API/BitZam_s.exe" /libpath:"../FTKernel_API/" /libpath:"../Lib"

!ENDIF 

# Begin Target

# Name "BitZam - Win32 Release"
# Name "BitZam - Win32 Debug"
# Name "BitZam - Win32 Static_Debug"
# Name "BitZam - Win32 Static_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BitZam.cpp
# End Source File
# Begin Source File

SOURCE=.\BitZam.rc
# End Source File
# Begin Source File

SOURCE=.\BitZamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BROWSEFORFOLDER.CPP
# End Source File
# Begin Source File

SOURCE=.\DlgAddExtAnnounce.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddPeer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDownByLink.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLinkURL.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMakeTorrent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMTProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOpenTorrentFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProxySettings.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\hyperlink.cpp
# End Source File
# Begin Source File

SOURCE=.\MemDC.cpp
# End Source File
# Begin Source File

SOURCE=.\SBDESTINATION.CPP
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextProgressCtr.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BitZam.h
# End Source File
# Begin Source File

SOURCE=.\BitZamDlg.h
# End Source File
# Begin Source File

SOURCE=.\BROWSEFORFOLDER.H
# End Source File
# Begin Source File

SOURCE=.\DlgAddExtAnnounce.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddPeer.h
# End Source File
# Begin Source File

SOURCE=.\DlgDownByLink.h
# End Source File
# Begin Source File

SOURCE=.\DlgLinkURL.h
# End Source File
# Begin Source File

SOURCE=.\DlgMakeTorrent.h
# End Source File
# Begin Source File

SOURCE=.\DlgMTProgress.h
# End Source File
# Begin Source File

SOURCE=.\DlgOpenTorrentFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgProxySettings.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelFiles.h
# End Source File
# Begin Source File

SOURCE=.\hyperlink.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SBDESTINATION.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TextProgressCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BitZam.ico
# End Source File
# Begin Source File

SOURCE=.\res\BitZam.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Uuid.Lib
# End Source File
# End Target
# End Project
