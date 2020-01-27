#ifndef CPHY_H
#define CPHY_H
#include "ccamera.h"

class PTime
{
private:
	float TimeSpeed; // Speed Of Time
public:

};

class PGravity
{
private:
	float ga; // gravity acceleration
public:

};

struct PObject
{
	float x;
	float y;
	float z;
	float xacc;
	float yacc;
	float zacc;
	float xspeed;
	float yspeed;
	float zspeed;
	float mass;
	int time;
};

void Phy_Gravity(PObject * obj);
void Attach_Obj(PObject * obj,float * x,float * y,float * z);
void Timer(PObject obj);
void Attach_Camera(PObject * obj,CCamera * came);
void tics();
#endif