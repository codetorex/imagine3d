#ifndef __EXPORTER_H
#define __EXPORTER_H

#include "stdafx.h"
#include "cs/phyexp.h"
#include "cs/bipexp.h"
#include "cs/keytrack.h"
#include "resource.h"
#include "array.h"
#include <time.h>

#define MYEXP_CLASSID  Class_ID(0x4d6b417b, 0x232417c9)
#define MYEXP_EXT "im3"
#define MYEXP_VER 050

#define DEBUGMODE 3 
/*
	0 = Off
	1 = On list box
	2 = Log output
	3 = Both
*/

TCHAR *GetString(int id);
extern ClassDesc* GetSceneExportDesc();
extern HINSTANCE g_hInstance;

struct IM3Head
{
	int signature;
	int objectcount;
	int entitycount;
	int lightcount;
	int cameracount;
	int texturecount;
	unsigned char alr,alg,alb;// ambient light r g b
	bool vertexlights;
	bool shadowface;
	bool tangentspace; // NEW!
};

struct IMKHeader
{
	int signature;
	int keystart;
	int keyend;
	int framerate;
};

struct IMKKey
{
	int keyno;
	float* chunk; // x1,y1,z1,x2,y2,z...
};

struct IMKObj
{
	int id;
	IMKKey* frms;
};

struct IM3Object
{
	carray<float,0> mx; // vertexs
	carray<float,0> my;
	carray<float,0> mz;

	carray<int,0>	v1; //face
	carray<int,0>	v2;
	carray<int,0>	v3;
	carray<int,0>	mat;

	carray<float,0> tu; // tex cord
	carray<float,0> tv;

	carray<int,0>	t1; // texture face
	carray<int,0>	t2;
	carray<int,0>	t3;

	carray<float,0> hx; //normal
	carray<float,0> hy;
	carray<float,0> hz;

	carray<float,0> sf; // shadow faces

	carray<int,0> abone;
	unsigned char* cr;
	unsigned char* cg;
	unsigned char* cb;

	float cx,cy,cz; // center x y z
	int vertcount;
	int facecount;
	int tvcount;
	int normalcount;
	int sfcount; // shadow face count
	
	float bx,by,bz; // en buyuk x y z
	float kx,ky,kz; // en kucuk x y z
	char namesz[50];
};

struct IM3Light
{
	char namesz[50];
	int lighttype;
	float lmatrix[12]; // lights matrix
	float tmatrix[12]; // targets matrix
	float intensity;
	float atten[4];
	unsigned char r,g,b; // color
};

struct IM3Entity
{
	float matrix[12];
	char nameandparam[100];
};

struct IM3Camera
{
	char names[50];
	float cx,cy,cz; // camera position
	float tx,ty,tz; // target position
};

struct IM3Texture
{
	char names[60];
};


struct IMBHead
{
	int signature;
	int bonecount;
	int keystart;
	int keyend;
	int framerate;
//	int ticksperframe;
};

struct IMBKeyframe
{
	int frameno;
	float xRot,yRot,zRot;
	float xPos,yPos,zPos;
//float m[12]; // MATRIX
};

struct IMBBone
{
	int boneid;
//	int parentid;
//	int childid;

	int framec;
	IMBKeyframe* frames;
};

/*struct Ray
{
	Point3 P0;
	Point3 P1;
};*/

struct Triangle
{
	Point3 V0,V1,V2;

};
class MyExporter : public SceneExport 
{
public:
	// + general				********************
    bool m_exportSelected;
    bool m_suppressPrompts;
	int exportmode;
	int elaptimer;
	char dbuffer[256];
	HWND* DebugDlgs;
    Interface * m_ip;
    ExpInterface * m_expip;
    FILE * m_fileStream;
	void MxToM(Matrix3 mat,float m[12]);
	Matrix3 Mat2GL(const Matrix3& _mat);
	Point3 Ver2GL(const Point3& _p);
	int GenID(char* st); // st is something
	void AddDbg();
	float ReduceRotation(float fl);
	Point3 crossp( const Point3 &v1,  const Point3 &v2 );
	float dotp( const Point3 &v1,  const Point3 &v2 );
	int intersect_RayTriangle( Ray R, Triangle T, Point3* I );
	float RayDistance (Ray R);
	float VecDistance (Point3 v0,Point3 v1);
	Point3 eline(Point3 src,Point3 dest,float mult = 2);
	bool smvlc(float s,float t,float tolerance=0.1f); // small value check
	bool isvusing(Point3 vec); // is vertex using in any object?

	// + im3scene				********************
	int curo; // current object
	int curl;// current light
	int cure;	//current entity
	int curc;	//current camera

	IM3Head		fh;
	IM3Object*	oc;
	IM3Light*	lc;
	IM3Entity*	ec;
	IM3Texture*	tc;
	IM3Camera*	cc;

    void DoHeader();
    void DoNodes();
    void DoTailer();
	void DoAll();
    bool nodeEnum(INode * node);
	Point3 GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);
	Modifier* FindPhysiqueModifier (INode* nodePtr);
    void ExportGeomObject(INode * node); 
    void ExportLightObject(INode * node);
	void ExportEntity(INode * node);
	void ExportCamera(INode * node);
	void ExportPhysiqueData(TimeValue t, ObjectState *os, INode *node);
	void WriteToFile();
	void WriteHeader();
	void WriteTexture(int id);
	void WriteObject(int id);
	void WriteEntity(int id);
	void WriteCamera(int id);
	void WriteLight(int id);
	void LoadTextureInfo();
	void CountLAO();
	void PrepareMem();

	// + im3bone				********************
	IMBHead		bh;
	IMBBone*	bcon;
	int curb;
	void DoSkeletal();
	bool skeletalEnum(INode* node);
	void ExportBone(INode* node,Control* c);
	void WriteBones();
	void WriteIMBHeader();
	void WriteBone(int id);
	void GetBoneCount();
	void BoneCounter(INode* node);

	// + im3keyframe			********************
	int			keyc; // keyframe count
	int			co; // current object

	IMKHeader	kh; // keyframe file header
	IMKObj*		kfob; // keyframed objects
	
	void DoKeyframe();
	bool FrameEnum(INode * node);
	void ExportObj(INode * node);

	// + calculations			********************
	void CalculateVertexLight();
	void CalculateVertexShadows();
	void CalculateTangentSpace();

	// + exporter functions		********************
    MyExporter();
    ~MyExporter();
    int ExtCount();
    const TCHAR * Ext(int n);
    const TCHAR * LongDesc();
    const TCHAR * ShortDesc();
    const TCHAR * AuthorName();
    const TCHAR * CopyrightMessage();
    const TCHAR * OtherMessage1();
    const TCHAR * OtherMessage2();
    unsigned int Version();
    void ShowAbout(HWND hWnd);
    int DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
    BOOL SupportsOptions(int ext, DWORD options);

};

#endif