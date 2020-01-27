#include "cphysics.h"
#include "cvision.h"
#include <stdio.h>

/*
PObject asd;
int osms = 1000;
float g = 9.8f;
int ticks=0;


/*
PObject::PObject()
{
	 x =		0;
	 y =		0;
	 z =		0;
	 xacc =		0;
	 yacc =		0;
	 zacc =		0;
	 xspeed =	0;
	 yspeed =	0;
	 zspeed =	0;
	 mass =		0;
	 time =		0;

};/*//*
FILE *sda; 

void Phy_Gravity(PObject * objs)
{
	if ( (GetTickCount() - ticks) > 100 )
	{
	//v = g * t  // T Snye sora cismin v hizi

	if ( (*objs).y > 0.0f )
	{
		(*objs).yspeed = -g * ((*objs).time / osms);
		ticks = GetTickCount();
		(*objs).time += 100;
	}
	else
	{
		(*objs).time = 0;
		ticks = GetTickCount();
		(*objs).yspeed = 0.0f;
	};

	}
};

void Attach_Obj(PObject * obj,float * x,float * y,float * z)
{
	(*obj).x += ((*obj).xspeed / osms) * (GetTickCount() - ticks);
	(*obj).y += ((*obj).yspeed / osms) * (GetTickCount() - ticks);
	(*obj).z += ((*obj).zspeed / osms) * (GetTickCount() - ticks);
	(*x) = (*obj).x;
	(*y) = (*obj).y;
	(*z) = (*obj).z;
};

void Attach_Camera(PObject * obj,CCamera * came)
{
	(*obj).x += ((*obj).xspeed / osms) * (GetTickCount() - ticks)*0.001f;
	(*obj).y += ((*obj).yspeed / osms) * (GetTickCount() - ticks)*0.001f;
	(*obj).z += ((*obj).zspeed / osms) * (GetTickCount() - ticks)*0.001f;
	(*came).xPos = (*obj).x;
	(*came).yPos = (*obj).y;
	(*came).zPos = (*obj).z;
	(*came).yView += ((*obj).yspeed / osms) * (GetTickCount() - ticks)*0.001f;
};

void tics()
{
	ticks = GetTickCount() - 1;
}*/