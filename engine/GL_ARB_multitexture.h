#ifndef arb_multi
#define arb_multi
#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glext.h>
#include <gl\wglext.h>

extern PFNGLACTIVETEXTUREPROC			glActiveTexture;
extern PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture;
extern PFNGLMULTITEXCOORD1DPROC			glMultiTexCoord1d;
extern PFNGLMULTITEXCOORD1DVPROC			glMultiTexCoord1dv;
extern PFNGLMULTITEXCOORD1FPROC			glMultiTexCoord1f;
extern PFNGLMULTITEXCOORD1FVPROC			glMultiTexCoord1fv;
extern PFNGLMULTITEXCOORD1IPROC			glMultiTexCoord1i;
extern PFNGLMULTITEXCOORD1IVPROC			glMultiTexCoord1iv;
extern PFNGLMULTITEXCOORD1SPROC			glMultiTexCoord1s;
extern PFNGLMULTITEXCOORD1SVPROC			glMultiTexCoord1sv;
extern PFNGLMULTITEXCOORD2DPROC			glMultiTexCoord2d;
extern PFNGLMULTITEXCOORD2DVPROC			glMultiTexCoord2dv;
extern PFNGLMULTITEXCOORD2FPROC			glMultiTexCoord2f;
extern PFNGLMULTITEXCOORD2FVPROC			glMultiTexCoord2fv;
extern PFNGLMULTITEXCOORD2IPROC			glMultiTexCoord2i;
extern PFNGLMULTITEXCOORD2IVPROC			glMultiTexCoord2iv;
extern PFNGLMULTITEXCOORD2SPROC			glMultiTexCoord2s;
extern PFNGLMULTITEXCOORD2SVPROC			glMultiTexCoord2sv;
extern PFNGLMULTITEXCOORD3DPROC			glMultiTexCoord3d;
extern PFNGLMULTITEXCOORD3DVPROC			glMultiTexCoord3dv;
extern PFNGLMULTITEXCOORD3FPROC			glMultiTexCoord3f;
extern PFNGLMULTITEXCOORD3FVPROC			glMultiTexCoord3fv;
extern PFNGLMULTITEXCOORD3IPROC			glMultiTexCoord3i;
extern PFNGLMULTITEXCOORD3IVPROC			glMultiTexCoord3iv;
extern PFNGLMULTITEXCOORD3SPROC			glMultiTexCoord3s;
extern PFNGLMULTITEXCOORD3SVPROC			glMultiTexCoord3sv;
extern PFNGLMULTITEXCOORD4DPROC			glMultiTexCoord4d;
extern PFNGLMULTITEXCOORD4DVPROC			glMultiTexCoord4dv;
extern PFNGLMULTITEXCOORD4FPROC			glMultiTexCoord4f;
extern PFNGLMULTITEXCOORD4FVPROC			glMultiTexCoord4fv;
extern PFNGLMULTITEXCOORD4IPROC			glMultiTexCoord4i;
extern PFNGLMULTITEXCOORD4IVPROC			glMultiTexCoord4iv;
extern PFNGLMULTITEXCOORD4SPROC			glMultiTexCoord4s;
extern PFNGLMULTITEXCOORD4SVPROC			glMultiTexCoord4sv;

void SetUp_GL_ARB_multitexture();

#endif