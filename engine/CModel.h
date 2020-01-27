#ifndef MODEL_H
#define MODEL_H

#include "array.h"
#include "cvector3f.h"
#include "cmatrix4x4f.h"

#include <windows.h>		
#include <gl\gl.h>		
#include <gl\glu.h>		
#include <gl\glaux.h>
		
#include "ctexture.h"
#include "cpak.h"
#include "tools.h"
#include "bumptex.h"


// IM3 BONE				***********************************
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
	matrix4x4f mat;
	//float m[12]; // MATRIX
	
};

struct IMBBone
{
	int boneid;
//	int parentid;
//	int childid;
	int framec;
	int curframe;
	IMBKeyframe* frames;
};

// IM3 SCENE			***********************************
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
	carray<unsigned char,0> cr;
	carray<unsigned char,0> cg;
	carray<unsigned char,0> cb;

	vector3f *TBN_Tangent;
	vector3f *TBN_Binormal;
	vector3f *TBN_Normal;



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

struct vcont
{
	int vertcount;
	carray<float,0> mx; // vertexs
	carray<float,0> my;
	carray<float,0> mz;
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


// SKELETAL SYSTEM
class IBone
{

public:
	//IBone();
	int animationid;

	void LoadIMB(char* impath,int fstart);
	
	IMBHead		IMBHeader;
	IMBBone*	IMBBones;
};

// MESH SYSTEM
class IModel
{
public:
	carray<float,0> zx;
	carray<float,0> zy;
	carray<float,0> zz;

	long tco;

	IModel();
	bool hitboxrender;
	bool bumptexs;

	void LoadIM3(char* impath, int fstart);
	void RescIM3(char* imname);
	
	void Render();	
	void RenderFaces();
	void RenderPoints();
	void RenderList();
	void CopyRender(vector3f cords);
	void RenderHitBox(); // Render Hit Box
	void Wireframe();
	void RenderLights();

	void Scale(vector3f nscal);
	void Normalize();
	
	void PrepareTexture(int tcount);
	void LoadTexturesFromPAK(CPak paque);
	void LoadTexturesA();	

	void Axis();
	void Shadow();
	void Shadow2(float lx,float ly,float lz);
	bool check(vector3f ne);
	bool smvl(float s,float t);
	
	void CalculateNormals();
	void CalculateTangentSpace();
	void CalculateLightMaps(long size=8);


	// Containers
	CTexture*		TextureCache;
	IM3Camera*		IM3Cameras; //  
	IM3Texture*		IM3TexPath; //  |
	IM3Entity*		IM3Entitys; //  | These Are
	IM3Light*		IM3Lights;  //  | Static
	IM3Object*		IM3Mesh;	//  |
	IM3Head			IM3Header;	//  
	BumpTex*		BumpCache;

//	IBone			BoneSystem;

	carray<vector3f,0> rlist;

	bool IsInBox(vector3f v);
};

// SKELETAL + MESH
class SModel: public IModel // skeletal model based on imodel
{
public:
	int timer;
	int mpf; // millisecond per frame
	int cf;  // current frame
	void ipav(float tween);// interpolate all vertices
	void CalculateNextframe();
	int FindBoneAnim(int bn);
	float mtw;
	int tim2;
	bool ileri;



	SModel();
	void PrepareAnim(int animcount);
	void LoadAnimsA();
	void AttachBones();
	void LoadAnimsFromPAK(CPak paque);
	void RenderA();

	int animid;
	int loadedanims;
	

	IBone*			IM3Anims;
	vcont*			IM3Base;
	vcont*			IM3NextFrame;
	vcont*			IM3Curframe;
};

/*
class STest: public IModel
{
public:

};
*/
/*
class AModel
{
private:
	IModel *keys;
public:
	float tfac;
	int ca;
	int kc;

	AModel();
	IModel mainmodel;
	float animspeed;
	void setkeycount(int kcount);
	void loadkey(int no,char* fname,int fstart);
	void loadkeya(char* fname);
	void updateanimation();
	void autorender();
}*/
/*
class AModel // animated model (key frame and linear interpolation based
{
private:
	FModel *keys;
public:
	float tfac; // tween factor
	int ca; // current animation
	int kc;

	AModel(); // constructor
	FModel mainmodel;
	float animspeed;
	void setkeycount(int kcount);
	void loadkey(int no,char* fname,int fstart);
	void updateanimation();
	void autorender();

};

  class FModel // file model
{
private:
	bool isinlist(int what);
public:

	int vertcount;
	int facecount;
	int tvcount;
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

	carray <float,0> px;
	carray <float,0> py;
	carray <float,0> pz;
	carray <float,0> rx;

	carray <int,0> atlist; // alphalý texture list

	carray<float,0> hx; //normal
	carray<float,0> hy;
	carray<float,0> hz;


	// Draw List
	int listcount; // object count
	void SetTextures(int tcount);
	//void LoadTexture(int tno,char* tpath,int st);
	void LoadIMO(char* impath,int st);
	void Render(bool hitbox = false);
	CTexture* ct1;
	vector3f HitBoxV[2]; // 0 Kucuk 1 Buyuk
	void RenderHitbox();
	bool IsHit(vector3f v); // Is In Box?
	void RenderC(vector3f c,float xrot=0,bool hitbox = false);
	void AddL(vector3f c,float xrot=0);
	void RenderL(bool hitbox = false);
	void RenderAlpha(bool hitbox=false);
};

*/
#endif