# Microsoft Developer Studio Project File - Name="Imagine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Imagine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Imagine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Imagine.mak" CFG="Imagine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Imagine - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Imagine - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Imagine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41f /d "NDEBUG"
# ADD RSC /l 0x41f /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 fmodvc.lib OpenGL32.lib GLu32.Lib GLaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Imagine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41f /d "_DEBUG"
# ADD RSC /l 0x41f /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 fmodvc.lib OpenGL32.lib GLu32.Lib GLaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Imagine - Win32 Release"
# Name "Imagine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Group "Entitys"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "InTools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TileEditor.h
# End Source File
# End Group
# Begin Group "CDP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CDP\CDPMain.cpp
# End Source File
# Begin Source File

SOURCE=.\CDP\Cursors.txt
# End Source File
# Begin Source File

SOURCE=.\CDP\OSGui.cpp
# End Source File
# Begin Source File

SOURCE=.\CDP\OSGui.h
# End Source File
# End Group

SOURCE=.\main.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\imagine.ico
# End Source File
# Begin Source File

SOURCE=.\myres.rc
# End Source File

# Begin Group "ENGINE"

# PROP Default_Filter ""
# Begin Group "MATH"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CMatrix4x4f.cpp
# End Source File
# Begin Source File

SOURCE=.\CMatrix4x4f.h
# End Source File
# Begin Source File

SOURCE=.\CVector3f.cpp
# End Source File
# Begin Source File

SOURCE=.\CVector3f.h
# End Source File
# End Group
# Begin Group "PHYSICS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\CEntity.h
# End Source File
# Begin Source File

SOURCE=.\CPhysics.cpp
# End Source File
# Begin Source File

SOURCE=.\CPhysics.h
# End Source File
# End Group
# Begin Group "VISION"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBillboard.cpp
# End Source File
# Begin Source File

SOURCE=.\CBillboard.h
# End Source File
# Begin Source File

SOURCE=.\CCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\CCamera.h
# End Source File
# Begin Source File

SOURCE=.\CPAK.H
# End Source File
# Begin Source File

SOURCE=.\CTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\CTexture.h
# End Source File
# Begin Source File

SOURCE=.\CVision.cpp
# End Source File
# Begin Source File

SOURCE=.\CVision.h
# End Source File
# Begin Source File

SOURCE=.\gui.cpp
# End Source File
# Begin Source File

SOURCE=.\gui.h
# End Source File
# Begin Source File

SOURCE=.\psprite.cpp
# End Source File
# Begin Source File

SOURCE=.\psprite.h
# End Source File
# End Group
# Begin Group "MODEL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CModel.cpp
# End Source File
# Begin Source File

SOURCE=.\CModel.h
# End Source File
# Begin Source File

SOURCE=.\MDLModel.cpp
# End Source File
# Begin Source File

SOURCE=.\MDLModel.h
# End Source File
# End Group
# Begin Group "GEN"

# PROP Default_Filter ""
# Begin Group "cbitmap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\b_c24b.cpp
# End Source File
# Begin Source File

SOURCE=.\b_cellular.cpp
# End Source File
# Begin Source File

SOURCE=.\b_draw.cpp
# End Source File
# Begin Source File

SOURCE=.\b_file.cpp
# End Source File
# Begin Source File

SOURCE=.\b_func.cpp
# End Source File
# Begin Source File

SOURCE=.\b_matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\b_plasma.cpp
# End Source File
# Begin Source File

SOURCE=.\b_pnoise.cpp
# End Source File
# Begin Source File

SOURCE=.\b_simple.cpp
# End Source File
# Begin Source File

SOURCE=.\c24b.h
# End Source File
# Begin Source File

SOURCE=.\cbitmap.h
# End Source File
# End Group
# Begin Group "cobject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cobject.h
# End Source File
# Begin Source File

SOURCE=.\obj_sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\obj_terrain.cpp
# End Source File
# End Group
# Begin Group "cmodify"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cmodify.h
# End Source File
# Begin Source File

SOURCE=.\m_light.cpp
# End Source File
# Begin Source File

SOURCE=.\m_normal.cpp
# End Source File
# Begin Source File

SOURCE=.\m_tangent.cpp
# End Source File
# Begin Source File

SOURCE=.\m_uvwmap.cpp
# End Source File
# End Group
# End Group
# Begin Group "TOOLS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Array.h
# End Source File
# Begin Source File

SOURCE=.\resmem.cpp
# End Source File
# Begin Source File

SOURCE=.\resmem.h
# End Source File
# Begin Source File

SOURCE=.\Stack.h
# End Source File
# Begin Source File

SOURCE=.\texfile.cpp
# End Source File
# Begin Source File

SOURCE=.\texfile.h
# End Source File
# Begin Source File

SOURCE=.\Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Tools.h
# End Source File
# Begin Source File

SOURCE=.\Tree.h
# End Source File
# End Group
# Begin Group "SOUND"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CMusic.cpp
# End Source File
# Begin Source File

SOURCE=.\CMusic.h
# End Source File
# End Group
# Begin Group "FX"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bumptex.cpp
# End Source File
# Begin Source File

SOURCE=.\bumptex.h
# End Source File
# Begin Source File

SOURCE=.\parallax.cpp
# End Source File
# Begin Source File

SOURCE=.\parallax.h
# End Source File
# End Group
# Begin Group "EXT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GL_ARB_multitexture.cpp
# End Source File
# Begin Source File

SOURCE=.\GL_ARB_multitexture.h
# End Source File
# Begin Source File

SOURCE=.\GL_ARB_vertex_program.cpp
# End Source File
# Begin Source File

SOURCE=.\GL_ARB_vertex_program.h
# End Source File
# End Group
# Begin Group "SHADER"

# PROP Default_Filter "vp;fp"
# Begin Source File

SOURCE=.\programs\bump.fp
# End Source File
# Begin Source File

SOURCE=.\programs\bump.vp
# End Source File
# Begin Source File

SOURCE=.\programs\bump_and_parallax.fp
# End Source File
# Begin Source File

SOURCE=.\programs\bump_and_parallax.vp
# End Source File
# Begin Source File

SOURCE=.\programs\parallax.fp
# End Source File
# End Group
# Begin Source File

SOURCE=.\constant.h
# End Source File
# Begin Source File

SOURCE=.\PUSH.TXT
# End Source File
# End Group
# Begin Group "IDEAS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\specular.txt
# End Source File
# Begin Source File

SOURCE=.\tangent.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\IDEA.TXT
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Target
# End Project
