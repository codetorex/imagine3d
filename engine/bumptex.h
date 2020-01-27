#ifndef bumpy
#define	bumpy

#include "cvector3f.h"

class BumpTex
{

public:
	unsigned int	basemap;
	unsigned int	bumpmap;
	unsigned int	cubemap;

	int GenNormalizationCubeMap(unsigned int size);
	void AttachTexture();
	vector3f light_pos;
	void glBumpedVertex(vector3f vertex,float u,float v,vector3f tang,vector3f bino,vector3f norm);
	vector3f vertex_to_light;
};

//void SetUp_GL_ARB_multitexture();
void DisableBumpMap();

#endif