#include "cvector3f.h"

vector3f linIp(const vector3f vsrc,const vector3f vdest,float tween)
{
	vector3f tw;
	tw.x = (vdest.x * tween) + vsrc.x * (1.0f - tween);
	tw.y = (vdest.y * tween) + vsrc.y * (1.0f - tween);
	tw.z = (vdest.z * tween) + vsrc.z * (1.0f - tween);
	return tw;
}
float distance( const vector3f &v1,  const vector3f &v2  )
{
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	float dz = v1.z - v2.z;

	return (float)sqrt( dx * dx + dy * dy + dz * dz );
}
float dot( const vector3f &v1,  const vector3f &v2 )
{
	return( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z  );
}

vector3f cross( const vector3f &v1,  const vector3f &v2 )
{
	vector3f vCrossProduct;

	vCrossProduct.x =  v1.y * v2.z - v1.z * v2.y;
	vCrossProduct.y = -v1.x * v2.z + v1.z * v2.x;
	vCrossProduct.z =  v1.x * v2.y - v1.y * v2.x;

	return vCrossProduct;
}

vector3f::vector3f( float x_, float y_, float z_ )
{
    x = x_;
    y = y_;
    z = z_;
}

void vector3f::set( float x_, float y_, float z_ )
{
    x = x_;
    y = y_;
    z = z_;
}

float vector3f::length( void )
{
    return( (float)sqrt( x * x + y * y + z * z ) );
}

void vector3f::normalize( void )
{
	float fLength = length();

	x = x / fLength;
	y = y / fLength;
	z = z / fLength;
}

// Static utility methods...



// Operators...

vector3f vector3f::operator + ( const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x + other.x;
    vResult.y = y + other.y;
    vResult.z = z + other.z;

    return vResult;
}

vector3f vector3f::operator + ( void ) const
{
    return *this;
}

vector3f vector3f::operator - ( const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x - other.x;
    vResult.y = y - other.y;
    vResult.z = z - other.z;

    return vResult;
}

vector3f vector3f::operator - ( void ) const
{
    vector3f vResult(-x, -y, -z);

    return vResult;
}

vector3f vector3f::operator * ( const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x * other.x;
    vResult.y = y * other.y;
    vResult.z = z * other.z;

    return vResult;
}

vector3f vector3f::operator * ( const float scalar )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x * scalar;
    vResult.y = y * scalar;
    vResult.z = z * scalar;

    return vResult;
}

vector3f operator * ( const float scalar, const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = other.x * scalar;
    vResult.y = other.y * scalar;
    vResult.z = other.z * scalar;

    return vResult;
}

/*
D3DXINLINE D3DXVECTOR3 operator * ( FLOAT f, CONST struct D3DXVECTOR3& v )
{
    return D3DXVECTOR3(f * v.x, f * v.y, f * v.z);
}
*/

vector3f vector3f::operator / ( const vector3f &other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x / other.x;
    vResult.y = y / other.y;
    vResult.z = z / other.z;

    return vResult;
}

vector3f& vector3f::operator = ( const vector3f &other )
{
	x = other.x;
	y = other.y;
	z = other.z;

    return *this;
}

vector3f& vector3f::operator += ( const vector3f &other )
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

vector3f& vector3f::operator -= ( const vector3f &other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}
vector3f mv3f(float x,float y,float z)
{
	vector3f temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
};

vector3f eline(vector3f src,vector3f dest,float mult)
{
	vector3f resul;
	resul.x = (mult * dest.x) - src.x;
	resul.y = (mult * dest.y) - src.y;
	resul.z = (mult * dest.z) - src.z;
	return resul;
}

void glVector3f(vector3f vec)
{
	glVertex3f(vec.x,vec.y,vec.z);
}

void ray::extend(float mult)
{
	d = eline(p,d,mult);
}

float ray::dist()
{	
	float x,y,z;
	x = p.x - d.x;
	y = p.y - d.y;
	z = p.z - d.z;

	return (float)sqrt(x*x + y*y + z*z);
}

float vecdist(vector3f v0,vector3f v1)
{	
	ray r;
	r.p = v0;r.d = v1; // Convert to ray
	return r.dist(); // return
}




#define SMALL_NUM  0.00000001 // anything that avoids division overflow
// intersect_RayTriangle(): intersect a ray with a 3D triangle
//    Input:  a ray R, and a triangle T
//    Output: *I = intersection point (when it exists)
//    Return: -1 = triangle is degenerate (a segment or point)
//             0 = disjoint (no intersect)
//             1 = intersect in unique point I1
//             2 = are in the same plane
int intersect_RayTriangle( ray R, triangle T, vector3f* I )
{
    vector3f    u, v, n;             // triangle vectors
    vector3f    dir, w0, w;          // ray vectors
    float     r, a, b;             // params to calc ray-plane intersect

//	sprintf(dbuffer,"bp 1");AddDbg();
    // get triangle edge vectors and plane normal
	u = T.v1 - T.v0;
	v = T.v2 - T.v0;


    n = cross(u,v);             // cross product
	if ( (n.x == 0) && (n.y == 0) && (n.z == 0) ) return -1;

	dir = R.d - R.p;
	w0 = R.p - T.v0;

    a = -dot(n,w0);
    b = dot(n,dir);
    if (fabs(b) < SMALL_NUM) {     // ray is parallel to triangle plane
        if (a == 0)                // ray lies in triangle plane
            return 2;
        else return 0;             // ray disjoint from plane
    }

//	sprintf(dbuffer,"bp 2");AddDbg();
    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                   // ray goes away from triangle
        return 0;                  // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

	vector3f tr,tz;
	tr =dir * r;
//	sprintf(dbuffer,"bp 3");AddDbg();
	tz = R.p + tr;
    I->x = tz.x; 
	I->y = tz.y; 
	I->z = tz.z; 
//	sprintf(dbuffer,"bp 4");AddDbg();
    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = dot(u,u);
    uv = dot(u,v);
    vv = dot(v,v);
	w.x = I->x - T.v0.x;
	w.y = I->y - T.v0.y;
	w.z = I->z - T.v0.z;
    wu = dot(w,u);
    wv = dot(w,v);
    D = uv * uv - uu * vv;
//	sprintf(dbuffer,"bp 5");AddDbg();
    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)        // I is outside T
        return 0;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return 0;

    return 1;                      // I is in T
}