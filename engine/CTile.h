#ifndef TILE_H
#define TILE_H

#include "array.h"
#include "cvector3f.h"
#include "cmatrix4x4f.h"
#include <windows.h>		
#include <gl\gl.h>		
#include <gl\glu.h>		
#include <gl\glaux.h>
		
#include "ctexture.h"
#include "cpak.h"
#include "tools.h"
#include "cmodel.h"

class CTile
{
public:
	IModel ti;
	void Generate(int width,int height,float scale);
}

#endif