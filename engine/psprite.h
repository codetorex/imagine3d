#ifndef psprite_h
#define psprite_h

#include <windows.h>	
#include <gl\gl.h>			
#include <gl\glu.h>			
#include <gl\glaux.h>

#include "array.h"



class PSprite
{
	int sprc;
	int usin;
public:
	PSprite();
	float	maxsize;
	float* sprites;
	int		texid;
	void	InitExtension();
	void	StartSprite();
	void	EndSprite();
	void	Render();
	void	Prepare(int sco);
	void	Add(float x,float y,float z);
};

#endif