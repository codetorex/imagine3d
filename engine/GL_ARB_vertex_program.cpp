#include "gl_arb_vertex_program.h"
#include <stdio.h>

PFNGLVERTEXATTRIB1DARBPROC glVertexAttrib1dARB 							= NULL;
PFNGLVERTEXATTRIB1DVARBPROC glVertexAttrib1dvARB 						= NULL;
PFNGLVERTEXATTRIB1FARBPROC glVertexAttrib1fARB 							= NULL;
PFNGLVERTEXATTRIB1FVARBPROC glVertexAttrib1fvARB 						= NULL;
PFNGLVERTEXATTRIB1SARBPROC glVertexAttrib1sARB 							= NULL;
PFNGLVERTEXATTRIB1SVARBPROC glVertexAttrib1svARB 						= NULL;
PFNGLVERTEXATTRIB2DARBPROC glVertexAttrib2dARB 							= NULL;
PFNGLVERTEXATTRIB2DVARBPROC glVertexAttrib2dvARB 						= NULL;
PFNGLVERTEXATTRIB2FARBPROC glVertexAttrib2fARB 							= NULL;
PFNGLVERTEXATTRIB2FVARBPROC glVertexAttrib2fvARB 						= NULL;
PFNGLVERTEXATTRIB2SARBPROC glVertexAttrib2sARB 							= NULL;
PFNGLVERTEXATTRIB2SVARBPROC glVertexAttrib2svARB 						= NULL;
PFNGLVERTEXATTRIB3DARBPROC glVertexAttrib3dARB 							= NULL;
PFNGLVERTEXATTRIB3DVARBPROC glVertexAttrib3dvARB 						= NULL;
PFNGLVERTEXATTRIB3FARBPROC glVertexAttrib3fARB 							= NULL;
PFNGLVERTEXATTRIB3FVARBPROC glVertexAttrib3fvARB 						= NULL;
PFNGLVERTEXATTRIB3SARBPROC glVertexAttrib3sARB 							= NULL;
PFNGLVERTEXATTRIB3SVARBPROC glVertexAttrib3svARB 						= NULL;
PFNGLVERTEXATTRIB4NBVARBPROC glVertexAttrib4NbvARB 						= NULL;
PFNGLVERTEXATTRIB4NIVARBPROC glVertexAttrib4NivARB 						= NULL;
PFNGLVERTEXATTRIB4NSVARBPROC glVertexAttrib4NsvARB 						= NULL;
PFNGLVERTEXATTRIB4NUBARBPROC glVertexAttrib4NubARB 						= NULL;
PFNGLVERTEXATTRIB4NUBVARBPROC glVertexAttrib4NubvARB 					= NULL;
PFNGLVERTEXATTRIB4NUIVARBPROC glVertexAttrib4NuivARB 					= NULL;
PFNGLVERTEXATTRIB4NUSVARBPROC glVertexAttrib4NusvARB 					= NULL;
PFNGLVERTEXATTRIB4BVARBPROC glVertexAttrib4bvARB 						= NULL;
PFNGLVERTEXATTRIB4DARBPROC glVertexAttrib4dARB 							= NULL;
PFNGLVERTEXATTRIB4DVARBPROC glVertexAttrib4dvARB 						= NULL;
PFNGLVERTEXATTRIB4FARBPROC glVertexAttrib4fARB 							= NULL;
PFNGLVERTEXATTRIB4FVARBPROC glVertexAttrib4fvARB 						= NULL;
PFNGLVERTEXATTRIB4IVARBPROC glVertexAttrib4ivARB 						= NULL;
PFNGLVERTEXATTRIB4SARBPROC glVertexAttrib4sARB 							= NULL;
PFNGLVERTEXATTRIB4SVARBPROC glVertexAttrib4svARB 						= NULL;
PFNGLVERTEXATTRIB4UBVARBPROC glVertexAttrib4ubvARB						= NULL;
PFNGLVERTEXATTRIB4UIVARBPROC glVertexAttrib4uivARB 						= NULL;
PFNGLVERTEXATTRIB4USVARBPROC glVertexAttrib4usvARB 						= NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB 				= NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB		= NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB		= NULL;
PFNGLPROGRAMSTRINGARBPROC glProgramStringARB 							= NULL;
PFNGLBINDPROGRAMARBPROC glBindProgramARB 								= NULL;
PFNGLDELETEPROGRAMSARBPROC glDeleteProgramsARB 							= NULL;
PFNGLGENPROGRAMSARBPROC glGenProgramsARB 								= NULL;
PFNGLPROGRAMENVPARAMETER4DARBPROC glProgramEnvParameter4dARB 			= NULL;
PFNGLPROGRAMENVPARAMETER4DVARBPROC glProgramEnvParameter4dvARB 			= NULL;
PFNGLPROGRAMENVPARAMETER4FARBPROC glProgramEnvParameter4fARB 			= NULL;
PFNGLPROGRAMENVPARAMETER4FVARBPROC glProgramEnvParameter4fvARB 			= NULL;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC glProgramLocalParameter4dARB 		= NULL;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC glProgramLocalParameter4dvARB 		= NULL;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC glProgramLocalParameter4fARB 		= NULL;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC glProgramLocalParameter4fvARB 		= NULL;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC glGetProgramEnvParameterdvARB 		= NULL;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC glGetProgramEnvParameterfvARB 		= NULL;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC glGetProgramLocalParameterdvARB	= NULL;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC glGetProgramLocalParameterfvARB	= NULL;
PFNGLGETPROGRAMIVARBPROC glGetProgramivARB 								= NULL;
PFNGLGETPROGRAMSTRINGARBPROC glGetProgramStringARB 						= NULL;
PFNGLGETVERTEXATTRIBDVARBPROC glGetVertexAttribdvARB 					= NULL;
PFNGLGETVERTEXATTRIBFVARBPROC glGetVertexAttribfvARB 					= NULL;
PFNGLGETVERTEXATTRIBIVARBPROC glGetVertexAttribivARB 					= NULL;
PFNGLGETVERTEXATTRIBPOINTERVARBPROC glGetVertexAttribPointervARB 		= NULL;
PFNGLISPROGRAMARBPROC glIsProgramARB 									= NULL;

void SetUp_GL_ARB_vertex_program()
{
	glVertexAttrib1dARB = (PFNGLVERTEXATTRIB1DARBPROC)wglGetProcAddress("glVertexAttrib1dARB");
	glVertexAttrib1dvARB = (PFNGLVERTEXATTRIB1DVARBPROC)wglGetProcAddress("glVertexAttrib1dvARB");
	glVertexAttrib1fARB = (PFNGLVERTEXATTRIB1FARBPROC)wglGetProcAddress("glVertexAttrib1fARB");
	glVertexAttrib1fvARB = (PFNGLVERTEXATTRIB1FVARBPROC)wglGetProcAddress("glVertexAttrib1fvARB");
	glVertexAttrib1sARB = (PFNGLVERTEXATTRIB1SARBPROC)wglGetProcAddress("glVertexAttrib1sARB");
	glVertexAttrib1svARB = (PFNGLVERTEXATTRIB1SVARBPROC)wglGetProcAddress("glVertexAttrib1svARB");
	glVertexAttrib2dARB = (PFNGLVERTEXATTRIB2DARBPROC)wglGetProcAddress("glVertexAttrib2dARB");
	glVertexAttrib2dvARB = (PFNGLVERTEXATTRIB2DVARBPROC)wglGetProcAddress("glVertexAttrib2dvARB");
	glVertexAttrib2fARB = (PFNGLVERTEXATTRIB2FARBPROC)wglGetProcAddress("glVertexAttrib2fARB");
	glVertexAttrib2fvARB = (PFNGLVERTEXATTRIB2FVARBPROC)wglGetProcAddress("glVertexAttrib2fvARB");
	glVertexAttrib2sARB = (PFNGLVERTEXATTRIB2SARBPROC)wglGetProcAddress("glVertexAttrib2sARB");
	glVertexAttrib2svARB = (PFNGLVERTEXATTRIB2SVARBPROC)wglGetProcAddress("glVertexAttrib2svARB");
	glVertexAttrib3dARB = (PFNGLVERTEXATTRIB3DARBPROC)wglGetProcAddress("glVertexAttrib3dARB");
	glVertexAttrib3dvARB = (PFNGLVERTEXATTRIB3DVARBPROC)wglGetProcAddress("glVertexAttrib3dvARB");
	glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC)wglGetProcAddress("glVertexAttrib3fARB");
	glVertexAttrib3fvARB = (PFNGLVERTEXATTRIB3FVARBPROC)wglGetProcAddress("glVertexAttrib3fvARB");
	glVertexAttrib3sARB = (PFNGLVERTEXATTRIB3SARBPROC)wglGetProcAddress("glVertexAttrib3sARB");
	glVertexAttrib3svARB = (PFNGLVERTEXATTRIB3SVARBPROC)wglGetProcAddress("glVertexAttrib3svARB");
	glVertexAttrib4NbvARB = (PFNGLVERTEXATTRIB4NBVARBPROC)wglGetProcAddress("glVertexAttrib4NbvARB");
	glVertexAttrib4NivARB = (PFNGLVERTEXATTRIB4NIVARBPROC)wglGetProcAddress("glVertexAttrib4NivARB");
	glVertexAttrib4NsvARB = (PFNGLVERTEXATTRIB4NSVARBPROC)wglGetProcAddress("glVertexAttrib4NsvARB");
	glVertexAttrib4NubARB = (PFNGLVERTEXATTRIB4NUBARBPROC)wglGetProcAddress("glVertexAttrib4NubARB");
	glVertexAttrib4NubvARB = (PFNGLVERTEXATTRIB4NUBVARBPROC)wglGetProcAddress("glVertexAttrib4NubvARB");
	glVertexAttrib4NuivARB = (PFNGLVERTEXATTRIB4NUIVARBPROC)wglGetProcAddress("glVertexAttrib4NuivARB");
	glVertexAttrib4NusvARB = (PFNGLVERTEXATTRIB4NUSVARBPROC)wglGetProcAddress("glVertexAttrib4NusvARB");
	glVertexAttrib4bvARB = (PFNGLVERTEXATTRIB4BVARBPROC)wglGetProcAddress("glVertexAttrib4bvARB");
	glVertexAttrib4dARB = (PFNGLVERTEXATTRIB4DARBPROC)wglGetProcAddress("glVertexAttrib4dARB");
	glVertexAttrib4dvARB = (PFNGLVERTEXATTRIB4DVARBPROC)wglGetProcAddress("glVertexAttrib4dvARB");
	glVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC)wglGetProcAddress("glVertexAttrib4fARB");
	glVertexAttrib4fvARB = (PFNGLVERTEXATTRIB4FVARBPROC)wglGetProcAddress("glVertexAttrib4fvARB");
	glVertexAttrib4ivARB = (PFNGLVERTEXATTRIB4IVARBPROC)wglGetProcAddress("glVertexAttrib4ivARB");
	glVertexAttrib4sARB = (PFNGLVERTEXATTRIB4SARBPROC)wglGetProcAddress("glVertexAttrib4sARB");
	glVertexAttrib4svARB = (PFNGLVERTEXATTRIB4SVARBPROC)wglGetProcAddress("glVertexAttrib4svARB");
	glVertexAttrib4ubvARB = (PFNGLVERTEXATTRIB4UBVARBPROC)wglGetProcAddress("glVertexAttrib4ubvARB");
	glVertexAttrib4uivARB = (PFNGLVERTEXATTRIB4UIVARBPROC)wglGetProcAddress("glVertexAttrib4uivARB");
	glVertexAttrib4usvARB = (PFNGLVERTEXATTRIB4USVARBPROC)wglGetProcAddress("glVertexAttrib4usvARB");
	glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)wglGetProcAddress("glVertexAttribPointerARB");
	glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)wglGetProcAddress("glEnableVertexAttribArrayARB");
	glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)wglGetProcAddress("glDisableVertexAttribArrayARB");
	glProgramStringARB = (PFNGLPROGRAMSTRINGARBPROC)wglGetProcAddress("glProgramStringARB");
	glBindProgramARB = (PFNGLBINDPROGRAMARBPROC)wglGetProcAddress("glBindProgramARB");
	glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC)wglGetProcAddress("glDeleteProgramsARB");
	glGenProgramsARB = (PFNGLGENPROGRAMSARBPROC)wglGetProcAddress("glGenProgramsARB");
	glProgramEnvParameter4dARB = (PFNGLPROGRAMENVPARAMETER4DARBPROC)wglGetProcAddress("glProgramEnvParameter4dARB");
	glProgramEnvParameter4dvARB = (PFNGLPROGRAMENVPARAMETER4DVARBPROC)wglGetProcAddress("glProgramEnvParameter4dvARB");
	glProgramEnvParameter4fARB = (PFNGLPROGRAMENVPARAMETER4FARBPROC)wglGetProcAddress("glProgramEnvParameter4fARB");
	glProgramEnvParameter4fvARB = (PFNGLPROGRAMENVPARAMETER4FVARBPROC)wglGetProcAddress("glProgramEnvParameter4fvARB");
	glProgramLocalParameter4dARB = (PFNGLPROGRAMLOCALPARAMETER4DARBPROC)wglGetProcAddress("glProgramLocalParameter4dARB");
	glProgramLocalParameter4dvARB = (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)wglGetProcAddress("glProgramLocalParameter4dvARB");
	glProgramLocalParameter4fARB = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC)wglGetProcAddress("glProgramLocalParameter4fARB");
	glProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)wglGetProcAddress("glProgramLocalParameter4fvARB");
	glGetProgramEnvParameterdvARB = (PFNGLGETPROGRAMENVPARAMETERDVARBPROC)wglGetProcAddress("glGetProgramEnvParameterdvARB");
	glGetProgramEnvParameterfvARB = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC)wglGetProcAddress("glGetProgramEnvParameterfvARB");
	glGetProgramLocalParameterdvARB = (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)wglGetProcAddress("glGetProgramLocalParameterdvARB");
	glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)wglGetProcAddress("glGetProgramLocalParameterfvARB");
	glGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC)wglGetProcAddress("glGetProgramivARB");
	glGetProgramStringARB = (PFNGLGETPROGRAMSTRINGARBPROC)wglGetProcAddress("glGetProgramStringARB");
	glGetVertexAttribdvARB = (PFNGLGETVERTEXATTRIBDVARBPROC)wglGetProcAddress("glGetVertexAttribdvARB");
	glGetVertexAttribfvARB = (PFNGLGETVERTEXATTRIBFVARBPROC)wglGetProcAddress("glGetVertexAttribfvARB");
	glGetVertexAttribivARB = (PFNGLGETVERTEXATTRIBIVARBPROC)wglGetProcAddress("glGetVertexAttribivARB");
	glGetVertexAttribPointervARB = (PFNGLGETVERTEXATTRIBPOINTERVARBPROC)wglGetProcAddress("glGetVertexAttribPointervARB");
	glIsProgramARB = (PFNGLISPROGRAMARBPROC)wglGetProcAddress("glIsProgramARB");
}	

char* readProgram(const char* name)
{
	FILE *kina = fopen(name, "r");
   
	if (!kina)
		return 0;
 
	char *buffer = 0;
   
	// get file size
	long size = 0, curpos;
	curpos = ftell(kina);
	fseek(kina, 0L, SEEK_END);
	size = ftell(kina);
	fseek(kina, curpos, SEEK_SET);
   
	if (!size)
		return 0;   
	if (!(buffer = new char[size + 1]))
		return 0;

	memset(buffer, '\0', size + 1);
	if (!buffer)
		return 0;
	fread(buffer, 1, size, kina); // check return with size?
	fclose(kina);

	return buffer;
}

unsigned int lfprogram(char* name)
{
	unsigned int res;
	char* lp; // loaded program
	lp = readProgram(name);
	glGenProgramsARB(1, &res);
	glBindProgramARB(GL_VERTEX_PROGRAM_ARB, res);
	glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,strlen(lp), lp);
	return res;
}