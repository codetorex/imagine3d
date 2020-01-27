#ifndef CTYPES_H
#define CTYPES_H

/*struct vec2
{
	float x;
	float y;
};*/

/*struct vec3
{
	float x;
	float y;
	float z;
};*/

struct vertex8
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	float tu;
	float tv;
};

struct fcolor3
{
	float r;
	float g;
	float b;
};

#endif