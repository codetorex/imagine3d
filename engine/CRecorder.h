#ifndef CREC_H
#define CREC_H

#include "cvector3f.h"
#include "cvision.h"

class CRecord
{
vector3f * rec;
int cot;
public:
	CRecord();
	~CRecord();
	void Insert_Waypoint (float x, float y,float z);
	void Render_Waypoint ();
	void Write_File (char * filename);

};

#endif