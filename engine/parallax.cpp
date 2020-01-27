#include "parallax.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\wglext.h>
#include "gl_arb_vertex_program.h"
#include "gl_arb_multitexture.h"

void plxmap::AttachProgram()
{
		glEnable(GL_VERTEX_PROGRAM_ARB);
		glBindProgramARB(GL_VERTEX_PROGRAM_ARB, vertexp);
		glEnable(GL_FRAGMENT_PROGRAM_ARB);
		glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, fragmep);
}

void plxmap::AttachTexture()
{
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, basemap);
	glActiveTexture(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, normmap);
	glActiveTexture(GL_TEXTURE2_ARB);
	glBindTexture(GL_TEXTURE_2D, heigmap);
}

void plxmap::Attach()
{
	AttachProgram();
	AttachTexture();
}
void plxmap::Detach()
{	
	glActiveTexture(GL_TEXTURE0_ARB);  // why?
	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_VERTEX_PROGRAM_ARB);
	glDisable(GL_FRAGMENT_PROGRAM_ARB);
	/*
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/

}
