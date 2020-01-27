/*

  Tangent Space *
--------------
Addendum:

I have received several requests for code to calculate the tangent space basis for a general polygon. I will rename our TORUS_VERTEX class "TANGENT_VERTEX" since we are no longer dealing with tori. So, we have:

class TANGENT_VERTEX
{
public:
VECTOR3D position;
float s, t;
VECTOR3D sTangent, tTangent;
VECTOR3D normal;
VECTOR3D tangentSpaceLight;
};


This function will calculate the tangent space for a general polygon.You need to pass it three vertices of your polygon and three VECTOR3Ds in which to store the resulting normal, s tangent and t tangent.
If you want to find the tangent space basis for a single polygon, you can call this function, passing in the first three vertices of the polygon, and then assign the resulting tangents and normal to each vertex of the polygon.
To calculate the tangent space bases for a mesh, for example a Quake model, in which vertices are shared between polygons, loop through all of the vertices and zero their tangents and normals. Then, loop through all of the polygons, calculate the tangent space basis and ADD (rather than replace) the values to each vertex for that polygon. Then, loop through all of the vertices again and normalize the tangents and normals. This will take the average at each vertex. While it is not the best way of calculating the basis for a mesh, it is the way most people do it. Its shortcoming appears when you have two triangles sharing a vertex, one with s tangent (1, 0, 0) and one with s tangent (-1, 0, 0). The vertex will then have a zero tangent.

void CalculateTSB( const TANGENT_VERTEX & v0, const TANGENT_VERTEX & v1, const TANGENT_VERTEX & v2,
VECTOR3D & normal, VECTOR3D & sTangent, VECTOR3D & tTangent)
{

side0 is the vector along one side of the triangle of vertices passed in, and side1 is the vector along another side. Taking the cross product of these returns the normal.

VECTOR3D side0=v0.position-v1.position;
VECTOR3D side1=v2.position-v1.position;

//Calculate normal
normal=side1.CrossProduct(side0);
normal.Normalize();

Now we use a formula to calculate the s tangent . We then use the same formula for the t tangent.

float deltaT0=v0.texCoords.y-v1.texCoords.y;
float deltaT1=v2.texCoords.y-v1.texCoords.y;
sTangent=deltaT1*side0-deltaT0*side1;
sTangent.Normalize();

//Calculate t tangent
float deltaS0=v0.texCoords.x-v1.texCoords.x;
float deltaS1=v2.texCoords.x-v1.texCoords.x;
tTangent=deltaS1*side0-deltaS0*side1;
tTangent.Normalize();

Now, we take the cross product of the tangents to get a vector which should point in the same direction as our normal calculated above. If it points in the opposite direction (the dot product between the normals is less than zero), then we need to reverse the s and t tangents. This is because the triangle has been mirrored when going from tangent space to object space.

//reverse tangents if necessary
VECTOR3D tangentCross=sTangent.CrossProduct(tTangent);
if(tangentCross.DotProduct(normal)<0.0f)
{
sTangent=-sTangent;
tTangent=-tTangent;
}
}

I hope this small addendum helps people to use bump mapping on more than tori. Bump-mapped tori have been done to death!

  */

#include "stdafx.h"