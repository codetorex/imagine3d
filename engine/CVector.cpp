#include "cvector.h"

vec3 LI(vec3 src,vec3 dest,float tween) // Linear Interpolation
{
	vec3 tw;
	tw.x = (dest.x * tween) + src.x * (1.0f - tween);
	tw.y = (dest.y * tween) + src.y * (1.0f - tween);
	tw.z = (dest.z * tween) + src.z * (1.0f - tween);
	return tw;
}

vec3 MV(float x,float y,float z)
{
	vec3 tev;
	tev.x = x;
	tev.y = y;
	tev.z = z;
	return tev;
}

vec3 CP(vec3 v1,vec3 v2)
{
	vec3 tw;
	tw.x = (v1.y * v2.z) - (v1.z - v2.y);
	tw.y = (v1.z * v2.x) - (v1.x - v2.z);
	tw.z = (v1.x * v2.y) - (v1.y - v2.x);
	return tw;
}