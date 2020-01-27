//-----------------------------------------------------------------------------
//           Name: vector3f.h
//         Author: Kevin Harris
//  Last Modified: 04/25/02
//    Description: OpenGL compatible utility class for a 3D vector of floats
//                 NOTE: This class has been left unoptimized for readability.
//-----------------------------------------------------------------------------

#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_

#include <cmath>
#include <windows.h>	
#include <gl\gl.h>			
#include <gl\glu.h>			

class vector3f
{
public:

    float x;
    float y;
    float z;

    vector3f(void)
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    vector3f(float x_, float y_, float z_);
    void set(float x_, float y_, float z_);
    float length(void);
    void normalize(void);

    // Static utility methods


    // Operators...
    vector3f operator + (const vector3f &other);
    vector3f operator - (const vector3f &other);
    vector3f operator * (const vector3f &other);
	vector3f operator / (const vector3f &other);

    vector3f operator * (const float scalar);
    friend vector3f operator * (const float scalar, const vector3f &other);
    
	vector3f& operator = (const vector3f &other);
    vector3f& operator += (const vector3f &other);
    vector3f& operator -= (const vector3f &other);

	vector3f operator + (void) const;
	vector3f operator - (void) const;
};
float distance(const vector3f &v1, const vector3f &v2);
float dot(const vector3f &v1,  const vector3f &v2 );
vector3f cross(const vector3f &v1, const vector3f &v2);
vector3f linIp(const vector3f vsrc,const vector3f vdest,float tween);
vector3f mv3f(float x,float y,float z);
vector3f eline(vector3f src,vector3f dest,float mult = 2);
void glVector3f(vector3f vec);

class ray
{
public:
	vector3f p; // point
	vector3f d; // direction
	void extend(float mult); // extend it
	float dist(); // distance
};

class triangle
{
public:
	vector3f v0,v1,v2;
};

float vecdist(vector3f v0,vector3f v1);
int intersect_RayTriangle( ray r, triangle T, vector3f* I );

#endif // _VECTOR3F_H_
