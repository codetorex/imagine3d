#ifndef BBOARD_H
#define BBOARD_H

#include "cvector3f.h"


class CBBoard
{
public:
	CBBoard();
	int texid;
	vector3f color;
	vector3f camPos;
	bool autogetcampos;
	void matrixset(vector3f pos,vector3f axis);
	void render(vector3f pos,float scale,vector3f axis = mv3f(0,1,0));
};

#endif