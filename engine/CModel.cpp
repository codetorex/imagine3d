#include "cmodel.h"
#include <fstream.h>
#include "cvision.h"
#include "cvector3f.h"
#include "gui.h"
#include "resmem.h"
#include "gl_arb_multitexture.h"


SModel::SModel()
{
	animid=0;
	timer = GetTickCount();
}




void SModel::ipav(float tween)// interpolate all vertices
{
	for (int i=0;i<IM3Header.objectcount;i++)
	{
		for (int j=0;j<IM3Mesh[i].vertcount;j++)
		{
			//vector3f linIp(const vector3f vsrc,const vector3f vdest,float tween);
			vector3f src,dest,res;
			src.set(IM3Curframe[i].mx[j],IM3Curframe[i].my[j],IM3Curframe[i].mz[j]);
			dest.set(IM3NextFrame[i].mx[j],IM3NextFrame[i].my[j],IM3NextFrame[i].mz[j]);
			res = linIp(src,dest,tween);
			IM3Mesh[i].mx.EditElement(j,res.x);
			IM3Mesh[i].my.EditElement(j,res.y);
			IM3Mesh[i].mz.EditElement(j,res.z);
/*			char c[100];
			sprintf(c,"%f %f",IM3Mesh[i].mx[j],res.x);
			MessageBox(0,c,"olmaz",MB_OK);*/
			// dest = frame's matrix * src
		}
	}
}




char lag[100];
IModel::IModel()
{
	bumptexs = false;
}
void IModel::RescIM3(char* imname)
{
	float tf;
	int i,j,ti;
	char tc;
	char buf[256];
	unsigned int rf=0;
	rf = memopen(imname,"IM3");
	memread((char*)&IM3Header.signature,4,rf);

	if ( IM3Header.signature == 1395871049)
	{
		memread((char*)&IM3Header.objectcount,4,rf);
		memread((char*)&IM3Header.entitycount,4,rf);
		memread((char*)&IM3Header.lightcount,4,rf);
		memread((char*)&IM3Header.cameracount,4,rf);
		memread((char*)&IM3Header.texturecount,4,rf);
		memread((char*)&IM3Header.alr,1,rf);
		memread((char*)&IM3Header.alg,1,rf);
		memread((char*)&IM3Header.alb,1,rf);
		memread((char*)&IM3Header.vertexlights,sizeof(bool),rf);
		memread((char*)&IM3Header.shadowface,sizeof(bool),rf);
		

		IM3Cameras = new IM3Camera [IM3Header.cameracount];
		IM3TexPath = new IM3Texture [IM3Header.texturecount];
		IM3Entitys = new IM3Entity [IM3Header.entitycount];
		IM3Lights = new IM3Light [IM3Header.lightcount];
		IM3Mesh = new IM3Object [IM3Header.objectcount];
		TextureCache = new CTexture [IM3Header.texturecount];

		for (i=0;i<IM3Header.texturecount;i++)
		{
			for (j=0;j<60;j++)
			{
				memread((char*)&IM3TexPath[i].names[j],1,rf);
			}
		}

		for (i=0;i<IM3Header.objectcount;i++)
		{
			memread((char*)&IM3Mesh[i].vertcount,4,rf);
			memread((char*)&IM3Mesh[i].facecount,4,rf);
			memread((char*)&IM3Mesh[i].tvcount,4,rf);
			memread((char*)&IM3Mesh[i].sfcount,4,rf);
			
			IM3Mesh[i].normalcount = IM3Mesh[i].facecount * 3;
			//memread((char*)&IM3Mesh[i].normalcount,4);
			for (j=0;j<IM3Mesh[i].vertcount;j++)
			{
				memread((char*)&tf,4,rf);IM3Mesh[i].mx.AddElement(tf);
				memread((char*)&tf,4,rf);IM3Mesh[i].my.AddElement(tf);
				memread((char*)&tf,4,rf);IM3Mesh[i].mz.AddElement(tf);
				memread((char*)&ti,4,rf);IM3Mesh[i].abone.AddElement(ti);
			}
			for (j=0;j<IM3Mesh[i].facecount;j++)
			{
				memread((char*)&ti,4,rf);IM3Mesh[i].v1.AddElement(ti);
				memread((char*)&ti,4,rf);IM3Mesh[i].v2.AddElement(ti);
				memread((char*)&ti,4,rf);IM3Mesh[i].v3.AddElement(ti);
				memread((char*)&ti,4,rf);IM3Mesh[i].mat.AddElement(ti);
			}
			for (j=0;j<IM3Mesh[i].tvcount;j++)
			{
				memread((char*)&tf,4,rf);IM3Mesh[i].tu.AddElement(tf);
				memread((char*)&tf,4,rf);IM3Mesh[i].tv.AddElement(tf);
			}
			for (j=0;j<IM3Mesh[i].facecount;j++)
			{
				memread((char*)&ti,4,rf);IM3Mesh[i].t1.AddElement(ti);
				memread((char*)&ti,4,rf);IM3Mesh[i].t2.AddElement(ti);
				memread((char*)&ti,4,rf);IM3Mesh[i].t3.AddElement(ti);
			}
			for(j=0;j<IM3Mesh[i].normalcount ;j++)
			{
				memread((char*)&tf,4,rf);IM3Mesh[i].hx.AddElement(tf);
				memread((char*)&tf,4,rf);IM3Mesh[i].hy.AddElement(tf);
				memread((char*)&tf,4,rf);IM3Mesh[i].hz.AddElement(tf);
			}
			if (IM3Header.vertexlights)
			{
				for (j=0;j<IM3Mesh[i].normalcount;j++)
				{
					memread((char*)&tc,1,rf);IM3Mesh[i].cr.AddElement(tc);
					memread((char*)&tc,1,rf);IM3Mesh[i].cg.AddElement(tc);
					memread((char*)&tc,1,rf);IM3Mesh[i].cb.AddElement(tc);
				}
			}
			if (IM3Header.shadowface)
			{
				
				//sprintf(buf,"SFaces for %i = %i",i,IM3Mesh[i].sfcount);GCAdd(buf);
				for (j=0;j<IM3Mesh[i].sfcount;j++)
				{
					float x1,y1,z1,x2,y2,z2,x3,y3,z3;
					memread((char*)&x1,4,rf);IM3Mesh[i].sf.AddElement(x1);
					memread((char*)&y1,4,rf);IM3Mesh[i].sf.AddElement(y1);
					memread((char*)&z1,4,rf);IM3Mesh[i].sf.AddElement(z1);

					memread((char*)&x2,4,rf);IM3Mesh[i].sf.AddElement(x2);
					memread((char*)&y2,4,rf);IM3Mesh[i].sf.AddElement(y2);
					memread((char*)&z2,4,rf);IM3Mesh[i].sf.AddElement(z2);

					memread((char*)&x3,4,rf);IM3Mesh[i].sf.AddElement(x3);
					memread((char*)&y3,4,rf);IM3Mesh[i].sf.AddElement(y3);
					memread((char*)&z3,4,rf);IM3Mesh[i].sf.AddElement(z3);
				}
			}


			
			memread((char*)&IM3Mesh[i].cx,4,rf);
			memread((char*)&IM3Mesh[i].cy,4,rf);
			memread((char*)&IM3Mesh[i].cz,4,rf);

			memread((char*)&IM3Mesh[i].bx,4,rf);
			memread((char*)&IM3Mesh[i].by,4,rf);
			memread((char*)&IM3Mesh[i].bz,4,rf);

			memread((char*)&IM3Mesh[i].kx,4,rf);
			memread((char*)&IM3Mesh[i].ky,4,rf);
			memread((char*)&IM3Mesh[i].kz,4,rf);

			for (j=0;j<50;j++)
			{
				memread((char*)&IM3Mesh[i].namesz[j],1,rf);
			}

		}

		for (i=0;i<IM3Header.entitycount;i++)
		{
			for (j=0;j<12;j++)
			{
				memread((char*)&IM3Entitys[i].matrix[j],4,rf);
			}
			for (j=0;j<100;j++)
			{
				memread((char*)&IM3Entitys[i].nameandparam[j],1,rf);
			}
		}
		
		for (i=0;i<IM3Header.cameracount;i++)
		{
			for (j=0;j<50;j++)
			{
				memread((char*)&IM3Cameras[i].names[j],1,rf);
			}
				
			memread((char*)&IM3Cameras[i].cx,4,rf);
			memread((char*)&IM3Cameras[i].cy,4,rf);
			memread((char*)&IM3Cameras[i].cz,4,rf);
			memread((char*)&IM3Cameras[i].tx,4,rf);
			memread((char*)&IM3Cameras[i].ty,4,rf);
			memread((char*)&IM3Cameras[i].tz,4,rf);
		}

		for (i=0;i<IM3Header.lightcount;i++)
		{
			for (j=0;j<50;j++)
			{
				memread((char*)&IM3Lights[i].namesz[j],1,rf);
			}
			memread((char*)&IM3Lights[i].lighttype,4,rf);
			
			for (j=0;j<12;j++)
			{
				memread((char*)&IM3Lights[i].lmatrix[j],4,rf);
			}

			for (j=0;j<12;j++)
			{
				memread((char*)&IM3Lights[i].tmatrix[j],4,rf);
			}
			memread((char*)&IM3Lights[i].intensity,4,rf);
			for (j=0;j<4;j++)
			{
				memread((char*)&IM3Lights[i].atten[j],4,rf);
			}

			memread((char*)&IM3Lights[i].r,1,rf);
			memread((char*)&IM3Lights[i].g,1,rf);
			memread((char*)&IM3Lights[i].b,1,rf);
		}

//		sprintf(lag,"IM3 LoadRes: %s",imname);
		//GCAdd(lag);

	}else{
//		sprintf(lag,"Invalid IM3: %s",imname);
		//GCAdd(lag);
	}
	memclose(rf);
}
void IModel::LoadIM3(char* impath, int fstart)
{
	float tf;
	int i,j,ti;
	char tc;
	char buf[256];
	fstream bf (impath,ios::binary|ios::in);
	bf.seekg(fstart);
	bf.read((char*)&IM3Header.signature,4);
	if ( IM3Header.signature == 1395871049)
	{
		bf.read((char*)&IM3Header.objectcount,4);
		bf.read((char*)&IM3Header.entitycount,4);
		bf.read((char*)&IM3Header.lightcount,4);
		bf.read((char*)&IM3Header.cameracount,4);
		bf.read((char*)&IM3Header.texturecount,4);
		bf.read((char*)&IM3Header.alr,1);
		bf.read((char*)&IM3Header.alg,1);
		bf.read((char*)&IM3Header.alb,1);
		bf.read((char*)&IM3Header.vertexlights,sizeof(bool));
		bf.read((char*)&IM3Header.shadowface,sizeof(bool));
		

		IM3Cameras = new IM3Camera [IM3Header.cameracount];
		IM3TexPath = new IM3Texture [IM3Header.texturecount];
		IM3Entitys = new IM3Entity [IM3Header.entitycount];
		IM3Lights = new IM3Light [IM3Header.lightcount];
		IM3Mesh = new IM3Object [IM3Header.objectcount];
		if (!bumptexs)
		{
		TextureCache = new CTexture [IM3Header.texturecount];
		}
		else
		{
			TextureCache = new CTexture [1];
			BumpCache = new BumpTex [IM3Header.texturecount];
		}

		for (i=0;i<IM3Header.texturecount;i++)
		{
			for (j=0;j<60;j++)
			{
				bf.read((char*)&IM3TexPath[i].names[j],1);
			}
		}

		for (i=0;i<IM3Header.objectcount;i++)
		{
			bf.read((char*)&IM3Mesh[i].vertcount,4);
			bf.read((char*)&IM3Mesh[i].facecount,4);
			bf.read((char*)&IM3Mesh[i].tvcount,4);
			bf.read((char*)&IM3Mesh[i].sfcount,4);
			
			IM3Mesh[i].normalcount = IM3Mesh[i].facecount * 3;
			//bf.read((char*)&IM3Mesh[i].normalcount,4);
			IM3Mesh[i].mx.Resize(IM3Mesh[i].vertcount);
			IM3Mesh[i].my.Resize(IM3Mesh[i].vertcount);
			IM3Mesh[i].mz.Resize(IM3Mesh[i].vertcount);
			IM3Mesh[i].v1.Resize(IM3Mesh[i].facecount);
			IM3Mesh[i].v2.Resize(IM3Mesh[i].facecount);
			IM3Mesh[i].v3.Resize(IM3Mesh[i].facecount);
			IM3Mesh[i].mat.Resize(IM3Mesh[i].facecount);
			IM3Mesh[i].tu.Resize(IM3Mesh[i].tvcount);
			IM3Mesh[i].tv.Resize(IM3Mesh[i].tvcount);
			IM3Mesh[i].t1.Resize(IM3Mesh[i].facecount);
			IM3Mesh[i].t2.Resize(IM3Mesh[i].facecount);
			IM3Mesh[i].t3.Resize(IM3Mesh[i].facecount);


			for (j=0;j<IM3Mesh[i].vertcount;j++)
			{
				bf.read((char*)&tf,4);IM3Mesh[i].mx.AddElement(tf);
				bf.read((char*)&tf,4);IM3Mesh[i].my.AddElement(tf);
				bf.read((char*)&tf,4);IM3Mesh[i].mz.AddElement(tf);
				bf.read((char*)&ti,4);IM3Mesh[i].abone.AddElement(ti);
			}
			for (j=0;j<IM3Mesh[i].facecount;j++)
			{
				bf.read((char*)&ti,4);IM3Mesh[i].v1.AddElement(ti);
				bf.read((char*)&ti,4);IM3Mesh[i].v2.AddElement(ti);
				bf.read((char*)&ti,4);IM3Mesh[i].v3.AddElement(ti);
				bf.read((char*)&ti,4);IM3Mesh[i].mat.AddElement(ti);
			}
			for (j=0;j<IM3Mesh[i].tvcount;j++)
			{
				bf.read((char*)&tf,4);IM3Mesh[i].tu.AddElement(tf);
				bf.read((char*)&tf,4);IM3Mesh[i].tv.AddElement(tf);
			}
			for (j=0;j<IM3Mesh[i].facecount;j++)
			{
				bf.read((char*)&ti,4);IM3Mesh[i].t1.AddElement(ti);
				bf.read((char*)&ti,4);IM3Mesh[i].t2.AddElement(ti);
				bf.read((char*)&ti,4);IM3Mesh[i].t3.AddElement(ti);
			}
			for(j=0;j<IM3Mesh[i].normalcount ;j++)
			{
				bf.read((char*)&tf,4);IM3Mesh[i].hx.AddElement(tf);
				bf.read((char*)&tf,4);IM3Mesh[i].hy.AddElement(tf);
				bf.read((char*)&tf,4);IM3Mesh[i].hz.AddElement(tf);
			}
			if (IM3Header.vertexlights)
			{
				for (j=0;j<IM3Mesh[i].normalcount;j++)
				{
					bf.read((char*)&tc,1);IM3Mesh[i].cr.AddElement(tc);
					bf.read((char*)&tc,1);IM3Mesh[i].cg.AddElement(tc);
					bf.read((char*)&tc,1);IM3Mesh[i].cb.AddElement(tc);
				}
			}
			if (IM3Header.shadowface)
			{
				
				//sprintf(buf,"SFaces for %i = %i",i,IM3Mesh[i].sfcount);GCAdd(buf);
				for (j=0;j<IM3Mesh[i].sfcount;j++)
				{
					float x1,y1,z1,x2,y2,z2,x3,y3,z3;
					bf.read((char*)&x1,4);IM3Mesh[i].sf.AddElement(x1);
					bf.read((char*)&y1,4);IM3Mesh[i].sf.AddElement(y1);
					bf.read((char*)&z1,4);IM3Mesh[i].sf.AddElement(z1);

					bf.read((char*)&x2,4);IM3Mesh[i].sf.AddElement(x2);
					bf.read((char*)&y2,4);IM3Mesh[i].sf.AddElement(y2);
					bf.read((char*)&z2,4);IM3Mesh[i].sf.AddElement(z2);

					bf.read((char*)&x3,4);IM3Mesh[i].sf.AddElement(x3);
					bf.read((char*)&y3,4);IM3Mesh[i].sf.AddElement(y3);
					bf.read((char*)&z3,4);IM3Mesh[i].sf.AddElement(z3);
				}
			}


			
			bf.read((char*)&IM3Mesh[i].cx,4);
			bf.read((char*)&IM3Mesh[i].cy,4);
			bf.read((char*)&IM3Mesh[i].cz,4);

			bf.read((char*)&IM3Mesh[i].bx,4);
			bf.read((char*)&IM3Mesh[i].by,4);
			bf.read((char*)&IM3Mesh[i].bz,4);

			bf.read((char*)&IM3Mesh[i].kx,4);
			bf.read((char*)&IM3Mesh[i].ky,4);
			bf.read((char*)&IM3Mesh[i].kz,4);

			for (j=0;j<50;j++)
			{
				bf.read((char*)&IM3Mesh[i].namesz[j],1);
			}

		}

		for (i=0;i<IM3Header.entitycount;i++)
		{
			for (j=0;j<12;j++)
			{
				bf.read((char*)&IM3Entitys[i].matrix[j],4);
			}
			for (j=0;j<100;j++)
			{
				bf.read((char*)&IM3Entitys[i].nameandparam[j],1);
			}
		}
		
		for (i=0;i<IM3Header.cameracount;i++)
		{
			for (j=0;j<50;j++)
			{
				bf.read((char*)&IM3Cameras[i].names[j],1);
			}
				
			bf.read((char*)&IM3Cameras[i].cx,4);
			bf.read((char*)&IM3Cameras[i].cy,4);
			bf.read((char*)&IM3Cameras[i].cz,4);
			bf.read((char*)&IM3Cameras[i].tx,4);
			bf.read((char*)&IM3Cameras[i].ty,4);
			bf.read((char*)&IM3Cameras[i].tz,4);
		}

		for (i=0;i<IM3Header.lightcount;i++)
		{
			for (j=0;j<50;j++)
			{
				bf.read((char*)&IM3Lights[i].namesz[j],1);
			}
			bf.read((char*)&IM3Lights[i].lighttype,4);
			
			for (j=0;j<12;j++)
			{
				bf.read((char*)&IM3Lights[i].lmatrix[j],4);
			}

			for (j=0;j<12;j++)
			{
				bf.read((char*)&IM3Lights[i].tmatrix[j],4);
			}
			bf.read((char*)&IM3Lights[i].intensity,4);
			for (j=0;j<4;j++)
			{
				bf.read((char*)&IM3Lights[i].atten[j],4);
			}

			bf.read((char*)&IM3Lights[i].r,1);
			bf.read((char*)&IM3Lights[i].g,1);
			bf.read((char*)&IM3Lights[i].b,1);
		}

		sprintf(lag,"IM3 Load: %s",impath);
		//GCAdd(lag);

	}else{
		sprintf(lag,"Invalid IM3: %s",impath);
		//GCAdd(lag);
	}
	//SetUp_GL_ARB_multitexture();

}
void IModel::RenderHitBox()
{
	float x0,y0,z0,x1,y1,z1;
	for (int i=0;i <IM3Header.objectcount;i++)
	{
		x0 = IM3Mesh[i].bx; y0=IM3Mesh[i].by;z0=IM3Mesh[i].bz;
		x1 = IM3Mesh[i].kx; y1=IM3Mesh[i].ky;z1=IM3Mesh[i].kz;
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_LINES);
		glColor3f(0,1,0);
			glVertex3f(x0,y0,z0);glVertex3f(x1,y0,z0);
			glVertex3f(x1,y0,z0);glVertex3f(x1,y0,z1);
			glVertex3f(x1,y0,z1);glVertex3f(x0,y0,z1);
			glVertex3f(x0,y0,z1);glVertex3f(x0,y0,z0);
			glVertex3f(x0,y0,z0);glVertex3f(x0,y1,z0);
			glVertex3f(x1,y0,z0);glVertex3f(x1,y1,z0);
			glVertex3f(x1,y0,z1);glVertex3f(x1,y1,z1);
			glVertex3f(x0,y0,z1);glVertex3f(x0,y1,z1);
			glVertex3f(x0,y1,z0);glVertex3f(x1,y1,z0);
			glVertex3f(x0,y1,z0);glVertex3f(x0,y1,z1);
			glVertex3f(x1,y1,z0);glVertex3f(x1,y1,z1);
			glVertex3f(x1,y1,z1);glVertex3f(x0,y1,z1);

		glEnd();
		glColor4f(1,1,1,1);

	}
}
/*
void IModel::RenderHitBox()
{
	float x0,y0,z0,x1,y1,z1;
	for (int i=0;i<IM3Header.
	x0 = HitBoxV[0].x; y0=HitBoxV[0].y;z0=HitBoxV[0].z;
	x1 = HitBoxV[1].x; y1=HitBoxV[1].y;z1=HitBoxV[1].z;
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_LINES);
	glColor3f(0,1,0);
		glVertex3f(x0,y0,z0);glVertex3f(x1,y0,z0);
		glVertex3f(x1,y0,z0);glVertex3f(x1,y0,z1);
		glVertex3f(x1,y0,z1);glVertex3f(x0,y0,z1);
		glVertex3f(x0,y0,z1);glVertex3f(x0,y0,z0);
		glVertex3f(x0,y0,z0);glVertex3f(x0,y1,z0);
		glVertex3f(x1,y0,z0);glVertex3f(x1,y1,z0);
		glVertex3f(x1,y0,z1);glVertex3f(x1,y1,z1);
		glVertex3f(x0,y0,z1);glVertex3f(x0,y1,z1);
		glVertex3f(x0,y1,z0);glVertex3f(x1,y1,z0);
		glVertex3f(x0,y1,z0);glVertex3f(x0,y1,z1);
		glVertex3f(x1,y1,z0);glVertex3f(x1,y1,z1);
		glVertex3f(x1,y1,z1);glVertex3f(x0,y1,z1);

	glEnd();
	glColor4f(1,1,1,1);
}*/
void IModel::LoadTexturesA()
{
	char tiar[512];
		for (int i=0;i<IM3Header.texturecount;i++)
		{

			if (!bumptexs)
			{
				TextureCache[i].LoadBMPFile(IM3TexPath[i].names,0);
			}
			else
			{
				TextureCache[0].LoadBMPFile(IM3TexPath[i].names,0);
				BumpCache[i].basemap = TextureCache[0].ID;
				sprintf(tiar,"%sn",IM3TexPath[i].names);
				TextureCache[0].LoadBMPFile(tiar,0);
				BumpCache[i].bumpmap = TextureCache[0].ID;
				BumpCache[i].GenNormalizationCubeMap(128);
			}
		}
}
void IModel::LoadTexturesFromPAK(CPak paque)
{
	for (int i=0;i<IM3Header.texturecount;i++)
	{
//		TextureCache[i].LoadBMPFile(CPak.curfile,
	}
}

void IModel::Wireframe()
{
	int h1,h2,h3,z1,z2,z3;
	glBindTexture(GL_TEXTURE_2D,0);
	for (int i=0;i<IM3Header.objectcount;i++)
	{
		int tra=0;
		for (int j=0;j<IM3Mesh[i].facecount;j++)
		{


			 z1 = IM3Mesh[i].v1[j];
			 z2 = IM3Mesh[i].v2[j];
			 z3 = IM3Mesh[i].v3[j];
			glBegin(GL_LINES);
				glColor3ub(0,255,0);
				glVertex3f(IM3Mesh[i].mx[z1],IM3Mesh[i].my[z1],IM3Mesh[i].mz[z1]);
				glVertex3f(IM3Mesh[i].mx[z2],IM3Mesh[i].my[z2],IM3Mesh[i].mz[z2]);

				glVertex3f(IM3Mesh[i].mx[z2],IM3Mesh[i].my[z2],IM3Mesh[i].mz[z2]);
				glVertex3f(IM3Mesh[i].mx[z3],IM3Mesh[i].my[z3],IM3Mesh[i].mz[z3]);

				glVertex3f(IM3Mesh[i].mx[z3],IM3Mesh[i].my[z3],IM3Mesh[i].mz[z3]);
				glVertex3f(IM3Mesh[i].mx[z1],IM3Mesh[i].my[z1],IM3Mesh[i].mz[z1]);
			glEnd();
			
		}
	}
}
/*void IModel::RenderPoints()
{
	for (int i=0;i<
}*/
void IModel::Axis()
{
	glDisable(GL_DEPTH_TEST);
	for (int i=0;i<IM3Header.objectcount;i++)
	{
		
		glBegin(GL_LINES);
			glColor3ub(255,0,0);
			glVertex3f(IM3Mesh[i].cx,IM3Mesh[i].cy,IM3Mesh[i].cz);
			glVertex3f(IM3Mesh[i].cx+1,IM3Mesh[i].cy,IM3Mesh[i].cz);

			glColor3ub(0,255,0);
			glVertex3f(IM3Mesh[i].cx,IM3Mesh[i].cy,IM3Mesh[i].cz);
			glVertex3f(IM3Mesh[i].cx,IM3Mesh[i].cy+1,IM3Mesh[i].cz);

			glColor3ub(0,0,255);
			glVertex3f(IM3Mesh[i].cx,IM3Mesh[i].cy,IM3Mesh[i].cz);
			glVertex3f(IM3Mesh[i].cx,IM3Mesh[i].cy,IM3Mesh[i].cz+1);
		glEnd();
		
	}

	glEnable(GL_DEPTH_TEST);

}




bool IModel::smvl(float s,float t)
{
	if ( (s > (t-0.1f) && s < (t+0.1f)) || s == t ) return true;
	return false;
}

bool IModel::check(vector3f ne)
{
	int j,m;
	int f1,f2,f3;
	vector3f v1,v2,v3;

		for (j=0;j<IM3Header.objectcount;j++)
		{					
			for (m=0;m<IM3Mesh[j].facecount;m++)
			{
				f1 = IM3Mesh[j].v1[m];f2 = IM3Mesh[j].v2[m];f3 = IM3Mesh[j].v3[m];
				v1.x = IM3Mesh[j].mx[f1]; v1.y = IM3Mesh[j].my[f1];v1.z = IM3Mesh[j].mz[f1];
				v2.x = IM3Mesh[j].mx[f2]; v2.y = IM3Mesh[j].my[f2];v2.z = IM3Mesh[j].mz[f2];
				v3.x = IM3Mesh[j].mx[f3]; v3.y = IM3Mesh[j].my[f3];v3.z = IM3Mesh[j].mz[f3];
				if (smvl(ne.x,v1.x) && smvl(ne.y,v1.y) && smvl(ne.z,v1.z)) return false;
				if (smvl(ne.x,v2.x) && smvl(ne.y,v2.y) && smvl(ne.z,v2.z)) return false;
				if (smvl(ne.x,v3.x) && smvl(ne.y,v3.y) && smvl(ne.z,v3.z)) return false;
			}
		}
	return true;
}

void IModel::Shadow2(float lx,float ly,float lz)
{
	int i,j,k,l,m;
	ray lr1,lr2,lr3; // light rays
	
	int f1,f2,f3;
	vector3f v1,v2,v3;

	int r1,r2,r3;
	vector3f re1,re2,re3;

	float a1,a2; // average disytance

		lr1.p.x = lx;lr1.p.y = ly;lr1.p.z = lz;
		//lr1.p.x = IM3Lights[i].lmatrix[9] * LoadScale.x;lr1.p.y = IM3Lights[i].lmatrix[11] * LoadScale.y;lr1.p.z = -IM3Lights[i].lmatrix[10] * LoadScale.z;
		lr2.p = lr1.p; lr3.p = lr1.p;		
		for (j=0;j<IM3Header.objectcount;j++)
		{
			for (k=0;k<IM3Mesh[j].facecount;k++)
			{
				f1 = IM3Mesh[j].v1[k];f2 = IM3Mesh[j].v2[k];f3 = IM3Mesh[j].v3[k];
				v1.x = IM3Mesh[j].mx[f1]; v1.y = IM3Mesh[j].my[f1];v1.z = IM3Mesh[j].mz[f1];
				v2.x = IM3Mesh[j].mx[f2]; v2.y = IM3Mesh[j].my[f2];v2.z = IM3Mesh[j].mz[f2];
				v3.x = IM3Mesh[j].mx[f3]; v3.y = IM3Mesh[j].my[f3];v3.z = IM3Mesh[j].mz[f3];
				lr1.d = v1; lr2.d = v2; lr3.d = v3;
				//lr1.extend(20);lr2.extend(20);lr3.extend(20);
					/*
					glBindTexture(GL_TEXTURE_2D,0);
					glColor3ub(0,255,0);
					glBegin(GL_LINES);
						glVector3f(lr1.p);glVector3f(lr1.d);
						glVector3f(lr2.p);glVector3f(lr2.d);
						glVector3f(lr3.p);glVector3f(lr3.d);
					glEnd();
					*/
				a1 = (lr1.dist() + lr2.dist() + lr3.dist()) /3;
				
				for (l=0;l<IM3Header.objectcount;l++)
				{
					for (m=0;m<IM3Mesh[l].facecount;m++)
					{
						f1 = IM3Mesh[l].v1[m];f2 = IM3Mesh[l].v2[m];f3 = IM3Mesh[l].v3[m];
						v1.x = IM3Mesh[l].mx[f1]; v1.y = IM3Mesh[l].my[f1];v1.z = IM3Mesh[l].mz[f1];
						v2.x = IM3Mesh[l].mx[f2]; v2.y = IM3Mesh[l].my[f2];v2.z = IM3Mesh[l].mz[f2];
						v3.x = IM3Mesh[l].mx[f3]; v3.y = IM3Mesh[l].my[f3];v3.z = IM3Mesh[l].mz[f3];
						a2 = (vecdist(lr1.p,v1) + vecdist(lr1.p,v2) + vecdist(lr1.p,v3)) / 3;
						if (a1 < a2)
						{
							re1.set(0,0,0);
							triangle tri;
							tri.v0 = v1; tri.v1 = v2; tri.v2 = v3;
							r1 = intersect_RayTriangle(lr1,tri,&re1);
							r2 = intersect_RayTriangle(lr2,tri,&re2);
							r3 = intersect_RayTriangle(lr3,tri,&re3);

							if (r1 + r2 + r3 > 1)
							{
								if (check(re1) && check(re2) && check(re3))//if ( r1== 1 && r2==1 && r3==1)
								{
									glBegin(GL_LINES);
										glVector3f(re1);glVector3f(re2);
										glVector3f(re2);glVector3f(re3);
										glVector3f(re3);glVector3f(re1);
									glEnd();

									glColor3ub(0,0,0);
									glBegin(GL_TRIANGLES);
										glVector3f(re1);glVector3f(re2);glVector3f(re3);
									glEnd();
								}
							}
						}
						else
						{
							continue;
						};
					}
				}
			}
		}
	
}
void IModel::RenderFaces()
{
	for (int i=0;i<IM3Header.objectcount;i++)
	{
		int tra=0;
		for (int j=0;j<IM3Mesh[i].facecount;j++)
		{
			int z1 = IM3Mesh[i].v1[j];
			int z2 = IM3Mesh[i].v2[j];
			int z3 = IM3Mesh[i].v3[j];

			glBegin(GL_TRIANGLES);
				glNormal3f(IM3Mesh[i].hx[tra],IM3Mesh[i].hy[tra],IM3Mesh[i].hz[tra]);
				//glTexCoord2f(IM3Mesh[i].tu[h1],IM3Mesh[i].tv[h1]);
				glVertex3f(IM3Mesh[i].mx[z1],IM3Mesh[i].my[z1],IM3Mesh[i].mz[z1]);

				glNormal3f(IM3Mesh[i].hx[tra+1],IM3Mesh[i].hy[tra+1],IM3Mesh[i].hz[tra+1]);
				//glTexCoord2f(IM3Mesh[i].tu[h2],IM3Mesh[i].tv[h2]);
				glVertex3f(IM3Mesh[i].mx[z2],IM3Mesh[i].my[z2],IM3Mesh[i].mz[z2]);

				glNormal3f(IM3Mesh[i].hx[tra+2],IM3Mesh[i].hy[tra+2],IM3Mesh[i].hz[tra+2]);
				//glTexCoord2f(IM3Mesh[i].tu[h3],IM3Mesh[i].tv[h3]);
				glVertex3f(IM3Mesh[i].mx[z3],IM3Mesh[i].my[z3],IM3Mesh[i].mz[z3]);
			glEnd();
			tra+=3;
		}
	}
}
void IModel::Scale(vector3f nscal)
{
	for (int o=0;o<IM3Header.objectcount;o++)
	{
		for (long l=0;l<IM3Mesh[o].vertcount;l++)
		{
			vector3f z;
			z.x = IM3Mesh[o].mx[l];
			z.y = IM3Mesh[o].my[l];
			z.z = IM3Mesh[o].mz[l];

			IM3Mesh[o].mx[l] = z.x * nscal.x;
			IM3Mesh[o].my[l] = z.y * nscal.y;
			IM3Mesh[o].mz[l] = z.z * nscal.z;
		}
	}
}
void IModel::Normalize()
{
	for (int o=0;o<IM3Header.objectcount;o++)
	{
		for (long l=0;l<IM3Mesh[o].vertcount;l++)
		{
			vector3f c;
			c.x = IM3Mesh[o].mx[l];
			c.y = IM3Mesh[o].my[l];
			c.z = IM3Mesh[o].mz[l];
			c.normalize();
			IM3Mesh[o].mx[l] = c.x;
			IM3Mesh[o].my[l] = c.y;
			IM3Mesh[o].mz[l] = c.z;
		}
	}	
}
void IModel::Render()
{
	float trax,tray,traz;
	int matss;
	for (int i=0;i<IM3Header.objectcount;i++)
	{
		int tra=0;
		for (int j=0;j<IM3Mesh[i].facecount;j++)
		{
			matss = IM3Mesh[i].mat[j];
			if (!bumptexs)
			{
				glBindTexture(GL_TEXTURE_2D,TextureCache[matss].ID);
			}
			else
			{
				BumpCache[i].AttachTexture();
			}
			
			int h1 = IM3Mesh[i].t1[j];
			int h2 = IM3Mesh[i].t2[j];
			int h3 = IM3Mesh[i].t3[j];

			int z1 = IM3Mesh[i].v1[j];
			int z2 = IM3Mesh[i].v2[j];
			int z3 = IM3Mesh[i].v3[j];

			if (IM3Header.vertexlights)
			{

				glBegin(GL_TRIANGLES);
					glNormal3f(IM3Mesh[i].hx[tra],IM3Mesh[i].hy[tra],IM3Mesh[i].hz[tra]);
					glColor3ub(IM3Mesh[i].cr[tra],IM3Mesh[i].cg[tra],IM3Mesh[i].cb[tra]);
					glTexCoord2f(IM3Mesh[i].tu[h1],IM3Mesh[i].tv[h1]);
					glVertex3f(IM3Mesh[i].mx[z1],IM3Mesh[i].my[z1],IM3Mesh[i].mz[z1]);

					glNormal3f(IM3Mesh[i].hx[tra+1],IM3Mesh[i].hy[tra+1],IM3Mesh[i].hz[tra+1]);
					glColor3ub(IM3Mesh[i].cr[tra+1],IM3Mesh[i].cg[tra+1],IM3Mesh[i].cb[tra+1]);
					glTexCoord2f(IM3Mesh[i].tu[h2],IM3Mesh[i].tv[h2]);
					glVertex3f(IM3Mesh[i].mx[z2],IM3Mesh[i].my[z2],IM3Mesh[i].mz[z2]);

					glNormal3f(IM3Mesh[i].hx[tra+2],IM3Mesh[i].hy[tra+2],IM3Mesh[i].hz[tra+2]);
					glColor3ub(IM3Mesh[i].cr[tra+2],IM3Mesh[i].cg[tra+2],IM3Mesh[i].cb[tra+2]);
					glTexCoord2f(IM3Mesh[i].tu[h3],IM3Mesh[i].tv[h3]);
					glVertex3f(IM3Mesh[i].mx[z3],IM3Mesh[i].my[z3],IM3Mesh[i].mz[z3]);
				glEnd();

			}
			else
			{
				if (!bumptexs)
				{
					glBegin(GL_TRIANGLES);
						glNormal3f(IM3Mesh[i].hx[tra],IM3Mesh[i].hy[tra],IM3Mesh[i].hz[tra]);
						glTexCoord2f(IM3Mesh[i].tu[h1],IM3Mesh[i].tv[h1]);
						glVertex3f(IM3Mesh[i].mx[z1],IM3Mesh[i].my[z1],IM3Mesh[i].mz[z1]);

						glNormal3f(IM3Mesh[i].hx[tra+1],IM3Mesh[i].hy[tra+1],IM3Mesh[i].hz[tra+1]);
						glTexCoord2f(IM3Mesh[i].tu[h2],IM3Mesh[i].tv[h2]);
						glVertex3f(IM3Mesh[i].mx[z2],IM3Mesh[i].my[z2],IM3Mesh[i].mz[z2]);

						glNormal3f(IM3Mesh[i].hx[tra+2],IM3Mesh[i].hy[tra+2],IM3Mesh[i].hz[tra+2]);
						glTexCoord2f(IM3Mesh[i].tu[h3],IM3Mesh[i].tv[h3]);
						glVertex3f(IM3Mesh[i].mx[z3],IM3Mesh[i].my[z3],IM3Mesh[i].mz[z3]);
					glEnd();
				}
				else
				{
					glBegin(GL_TRIANGLES);
						//glNormal3f(IM3Mesh[i].hx[tra],IM3Mesh[i].hy[tra],IM3Mesh[i].hz[tra]);
						BumpCache[i].glBumpedVertex(mv3f(IM3Mesh[i].mx[z1],IM3Mesh[i].my[z1],IM3Mesh[i].mz[z1]),IM3Mesh[i].tu[h1],IM3Mesh[i].tv[h1],IM3Mesh[i].TBN_Tangent[z1],IM3Mesh[i].TBN_Binormal[z1],IM3Mesh[i].TBN_Normal[z1]);
						
						//glNormal3f(IM3Mesh[i].hx[tra+1],IM3Mesh[i].hy[tra+1],IM3Mesh[i].hz[tra+1]);
						BumpCache[i].glBumpedVertex(mv3f(IM3Mesh[i].mx[z2],IM3Mesh[i].my[z2],IM3Mesh[i].mz[z2]),IM3Mesh[i].tu[h2],IM3Mesh[i].tv[h2],IM3Mesh[i].TBN_Tangent[z2],IM3Mesh[i].TBN_Binormal[z2],IM3Mesh[i].TBN_Normal[z2]);


						//glNormal3f(IM3Mesh[i].hx[tra+2],IM3Mesh[i].hy[tra+2],IM3Mesh[i].hz[tra+2]);
						BumpCache[i].glBumpedVertex(mv3f(IM3Mesh[i].mx[z3],IM3Mesh[i].my[z3],IM3Mesh[i].mz[z3]),IM3Mesh[i].tu[h3],IM3Mesh[i].tv[h3],IM3Mesh[i].TBN_Tangent[z3],IM3Mesh[i].TBN_Binormal[z3],IM3Mesh[i].TBN_Normal[z3]);

					glEnd();
				//		glFlush ();													// Flush The GL Rendering Pipeline
		
				}
			}


			// POP 1
			tra+=3;
		}	
	}
	if(bumptexs) DisableBumpMap();

	if (IM3Header.shadowface)
	{	
		for (i=0;i<IM3Header.objectcount;i++)
		{
			glBindTexture(GL_TEXTURE_2D,0);
			//glColor4f(0,0,0,1);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glColor4ub(0,0,0,120);
			glBegin(GL_TRIANGLES);
			for (int j=0;j<IM3Mesh[i].sfcount*9;j+=9)
			{
				//glVertex3f (IM3Mesh[i].sf[j],IM3Mesh[i].sf[j+1],IM3Mesh[i].sf[j+2]);
				
					glVertex3f(IM3Mesh[i].sf[j+0],IM3Mesh[i].sf[j+1],IM3Mesh[i].sf[j+2]);
					glVertex3f(IM3Mesh[i].sf[j+3],IM3Mesh[i].sf[j+4],IM3Mesh[i].sf[j+5]);
					glVertex3f(IM3Mesh[i].sf[j+6],IM3Mesh[i].sf[j+7],IM3Mesh[i].sf[j+8]);
			}
			glEnd();
				glBindTexture(GL_TEXTURE_2D,TextureCache[matss].ID);
				diTP();			
		}
	}

}

/*bool IModel::IsInBox(vector3f v)
{
	bool cond;
	cond = false;
	if ( (v.x < HitBoxV[0].x) && (v.x > HitBoxV[1].x) ){if ( (v.y < HitBoxV[0].y) && (v.y > HitBoxV[1].y) ){if ( (v.z < HitBoxV[0].z) && (v.z > HitBoxV[1].z ) ){ cond = true;}}};
	return cond;
}*/

void IModel::CopyRender(vector3f cords)
{
	glPushMatrix();
		glTranslatef(cords.x,cords.y,cords.z);
		Render();
	glPopMatrix();
}

void IModel::PrepareTexture(int tcount)
{
	TextureCache = new CTexture [tcount];
}

/*


//reverse tangents if necessary
VECTOR3D tangentCross=sTangent.CrossProduct(tTangent);
if(tangentCross.DotProduct(normal)<0.0f)
{
sTangent=-sTangent;
tTangent=-tTangent;
}
}





*/