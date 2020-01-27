#include "psprite.h"
#include <gl/glext.h>
// GL_ARB_point_parameters
PFNGLPOINTPARAMETERFARBPROC  glPointParameterfARB  = NULL;
PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB = NULL;

void PSprite::InitExtension()
{
    char *ext = (char*)glGetString( GL_EXTENSIONS );

    if( strstr( ext, "GL_ARB_point_parameters" ) == NULL )
    {
	// ohh nooooo
    }
    else
    {
		if (glPointParameterfARB == NULL && glPointParameterfvARB == NULL)
		{
			glPointParameterfARB  = (PFNGLPOINTPARAMETERFARBPROC)wglGetProcAddress("glPointParameterfARB");
			glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC)wglGetProcAddress("glPointParameterfvARB");
		}
    }

}

void PSprite::StartSprite()
{
	glBindTexture( GL_TEXTURE_2D, texid );
   glEnable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    float quadratic[] =  { 1.0f, 0.0f, 0.01f };
    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );

	if (maxsize < 0)
	{
		glGetFloatv( GL_POINT_SIZE_MAX_ARB, &maxsize );
	}

    if( maxsize > 100.0f )
        maxsize = 100.0f;

    glPointSize( maxsize );
    glPointParameterfARB( GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f );

    glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, 1.0f );
    glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, maxsize );
    glTexEnvf( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );

    glEnable( GL_POINT_SPRITE_ARB );

	glBegin( GL_POINTS );

}

void PSprite::EndSprite()
{
	glEnd();
	glDisable( GL_POINT_SPRITE_ARB );
    glDepthMask( GL_TRUE );
    glDisable( GL_BLEND );
}

void PSprite::Render()
{
	StartSprite();
	for (int i=0;i<sprc*3;i+=3)
	{
		glVertex3f(sprites[i],sprites[i+1],sprites[i+2]);
	}
	EndSprite();
}

void PSprite::Prepare(int sco)
{
	if (!sprites) delete [] sprites;
	sprites = new float [sco*3];
}

void PSprite::Add(float x,float y,float z)
{
	sprites[usin+0] = x;
	sprites[usin+1] = y;
	sprites[usin+2] = z;
	usin+=3;
}

PSprite::PSprite()
{
	sprc = 0;
	usin = 0;
	maxsize = -1;
}