#ifndef CEFFECT_H
#define CEFFECT_H
                             
#include "ctexture.h"
#include "ccamera.h"

class CEffect
{
private:
	float vexs[12];
	CTexture* mats;
public:
	void LoadFX();
	void LoadBMP(char* bmppath,float sfac,int poss = 0);
	int fspeed;
	void Render(float x,float y,float z,CCamera cam);
};

#endif