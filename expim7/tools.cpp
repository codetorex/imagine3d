#include "stdafx.h"
#include "exporter.h"

int MyExporter::GenID(char* st)
{
	int te=0;
	for (int i=0;i<strlen(st);i++)
	{
		te += st[i];
	}
	return te;
}

void MyExporter::MxToM(Matrix3 mat,float m[12])
{
		Point3 row;
		row = mat.GetRow(0);
		m[0] = row.x;m[1] = row.y;m[2] = row.z;
		row = mat.GetRow(1);
		m[3] = row.x;m[4] = row.y;m[5] = row.z;
		row = mat.GetRow(2);
		m[6] = row.x;m[7] = row.y;m[8] = row.z;
		row = mat.GetRow(3);
		m[9] = row.x;m[10] = row.y;m[11] = row.z;
}

void MyExporter::AddDbg()
{
	if (DEBUGMODE == 1 || DEBUGMODE == 3)
	{
	SendDlgItemMessage(*DebugDlgs,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)dbuffer);
	}
	if (DEBUGMODE == 2 ||DEBUGMODE == 3)
	{
		FILE *logtxt = 0;
		logtxt = fopen("c://im3export.log","a+");
		fprintf(logtxt,"%s\n",dbuffer);
		fclose(logtxt);
	}
}

Matrix3 MyExporter::Mat2GL(const Matrix3& _mat)
{
  //return _mat;

  //T = R x _mat x R-1
  Matrix3 tm,tmogl,tmoglInv;
  tmogl.IdentityMatrix();
  tmogl.RotateX(PI*0.5f);
  tmoglInv=tmogl;
  tmoglInv.Invert();
  tm=tmogl*_mat*tmoglInv;
  return tm;
}


Point3 MyExporter::Ver2GL(const Point3& _p)
{
  //return _p;
  return Point3(_p[0],_p[2],-_p[1]); 

} 

float MyExporter::dotp( const Point3 &v1,  const Point3 &v2 )
{
	return( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z  );
}

Point3 MyExporter::crossp( const Point3 &v1,  const Point3 &v2 )
{
	Point3 vCrossProduct;

	vCrossProduct.x =  v1.y * v2.z - v1.z * v2.y;
	vCrossProduct.y = -v1.x * v2.z + v1.z * v2.x;
	vCrossProduct.z =  v1.x * v2.y - v1.y * v2.x;

	return vCrossProduct;
}

float MyExporter::RayDistance(Ray R)
{	
	float x,y,z;
	x = R.p.x - R.dir.x;
	y = R.p.y - R.dir.y;
	z = R.p.z - R.dir.z;

	return (float)sqrt(x*x + y*y + z*z);
}

float MyExporter::VecDistance(Point3 v0,Point3 v1)
{	
	Ray R;
	R.p = v0;R.dir = v1; // Convert to ray
	return RayDistance(R); // return
}

// Copyright 2001, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.


// Assume that classes are already given for the objects:
//    Point and Vector with
//        coordinates {float x, y, z;}
//        operators for:
//            == to test equality
//            != to test inequality
//            (Vector)0 = (0,0,0)         (null vector)
//            Point  = Point ± Vector
//            Vector = Point - Point
//            Vector = Scalar * Vector    (scalar product)
//            Vector = Vector * Vector    (cross product)
//    Line and Ray and Segment with defining points {Point P0, P1;}
//        (a Line is infinite, Rays and Segments start at P0)
//        (a Ray extends beyond P1, but a Segment ends at P1)
//    Plane with a point and a normal {Point V0; Vector n;}
//    Triangle with defining vertices {Point V0, V1, V2;}
//    Polyline and Polygon with n vertices {int n; Point *V;}
//        (a Polygon has V[n]=V[0])
//===================================================================

#define SMALL_NUM  0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
//#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)




// intersect_RayTriangle(): intersect a ray with a 3D triangle
//    Input:  a ray R, and a triangle T
//    Output: *I = intersection point (when it exists)
//    Return: -1 = triangle is degenerate (a segment or point)
//             0 = disjoint (no intersect)
//             1 = intersect in unique point I1
//             2 = are in the same plane
int MyExporter::intersect_RayTriangle( Ray R, Triangle T, Point3* I )
{
    Point3    u, v, n;             // triangle vectors
    Point3    dir, w0, w;          // ray vectors
    float     r, a, b;             // params to calc ray-plane intersect

//	sprintf(dbuffer,"bp 1");AddDbg();
    // get triangle edge vectors and plane normal
	u = T.V1 - T.V0;
	v = T.V2 - T.V0;

    n = crossp(u,v);             // cross product
	if ( (n.x == 0) && (n.y == 0) && (n.z == 0) ) return -1;

    dir = R.dir - R.p;             // ray direction vector
    w0 = R.p - T.V0;
    a = -dotp(n,w0);
    b = dotp(n,dir);
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

	Point3 tr,tz;
	tr.x = dir.x * r;
	tr.y = dir.y * r;
	tr.z = dir.z * r;
	tz = R.p + tr;

    I->x = tz.x; 
	I->y = tz.y; 
	I->z = tz.z; 
//	sprintf(dbuffer,"bp 4");AddDbg();
    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = dotp(u,u);
    uv = dotp(u,v);
    vv = dotp(v,v);
	w.x = I->x - T.V0.x;
	w.y = I->y - T.V0.y;
	w.z = I->z - T.V0.z;
    wu = dotp(w,u);
    wv = dotp(w,v);
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

Point3 MyExporter::eline(Point3 src,Point3 dest,float mult)
{
	Point3 resul;
	resul.x = (mult * dest.x) - src.x;
	resul.y = (mult * dest.y) - src.y;
	resul.z = (mult * dest.z) - src.z;
	return resul;
}

bool MyExporter::smvlc(float s,float t,float tolerance)
{
	if ( (s > (t-tolerance) && s < (t+tolerance)) || s == t ) return true;
	return false;
}

bool MyExporter::isvusing(Point3 vec)// is vertex using in any object?
{
	int j,m;
	int f1,f2,f3;
	Point3 v1,v2,v3;

		for (j=0;j<fh.objectcount;j++)
		{					
			for (m=0;m<oc[j].facecount;m++)
			{
				f1 = oc[j].v1[m];f2 = oc[j].v2[m];f3 = oc[j].v3[m];
				v1.x = oc[j].mx[f1]; v1.y = oc[j].my[f1];v1.z = oc[j].mz[f1];
				v2.x = oc[j].mx[f2]; v2.y = oc[j].my[f2];v2.z = oc[j].mz[f2];
				v3.x = oc[j].mx[f3]; v3.y = oc[j].my[f3];v3.z = oc[j].mz[f3];
				if (smvlc(vec.x,v1.x) && smvlc(vec.y,v1.y) && smvlc(vec.z,v1.z)) return true;
				if (smvlc(vec.x,v2.x) && smvlc(vec.y,v2.y) && smvlc(vec.z,v2.z)) return true;
				if (smvlc(vec.x,v3.x) && smvlc(vec.y,v3.y) && smvlc(vec.z,v3.z)) return true;
			}
		}
	return false;
}
