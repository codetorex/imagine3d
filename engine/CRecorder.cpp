#include "crecorder.h"

CRecord::CRecord()
{
	rec = new vector3f [100];
	cot = -1;
};

void CRecord::Insert_Waypoint(float x,float y,float z)
{

cot += 1;
rec[cot].x = x;
rec[cot].y = y;
rec[cot].z = z;

};

void CRecord::Render_Waypoint ()
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f,1.0f,1.0f);
	for (int i = 0;i<cot;i++)
	{
		glVertex3f(rec[i].x,rec[i].y,rec[i].z);
	}
	glEnd();

};

CRecord::~CRecord ()
{
	delete rec;
}