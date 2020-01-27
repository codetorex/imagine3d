#include "stdafx.h"
#include "exporter.h"


void MyExporter::WriteToFile()
{
	WriteHeader();
	//TEXUTRES
	for (int i=0;i<fh.texturecount;i++)
	{
		WriteTexture(i);
	}
	//OBJECTS
	for ( i=0;i<curo;i++)
	{
		WriteObject(i);
	}
	//ENTITYS
	for ( i=0;i<cure;i++)
	{
		WriteEntity(i);
	}
	//CAMERAS
	for ( i=0;i<curc;i++)
	{
		WriteCamera(i);
	}
	//LIGHTS
	for ( i=0;i<curl;i++)
	{
		WriteLight(i);
	}
	fclose(m_fileStream);
}

void MyExporter::WriteHeader()
{
	fwrite(&fh.signature,1,sizeof(int),m_fileStream);
	fwrite(&curo,1,sizeof(int),m_fileStream);
	fwrite(&cure,1,sizeof(int),m_fileStream);
	fwrite(&curl,1,sizeof(int),m_fileStream);
	fwrite(&curc,1,sizeof(int),m_fileStream);
	fwrite(&fh.texturecount,1,sizeof(int),m_fileStream);

	fwrite(&fh.alr,1,sizeof(char),m_fileStream);
	fwrite(&fh.alg,1,sizeof(char),m_fileStream);
	fwrite(&fh.alb,1,sizeof(char),m_fileStream);

	fwrite(&fh.vertexlights,1,sizeof(bool),m_fileStream);
	fwrite(&fh.shadowface,1,sizeof(bool),m_fileStream);
}/*
struct IM3Camera
{
	char names[50];
	float cx,cy,cz; // camera position
	float tx,ty,tz; // target position
};
*/
void MyExporter::WriteTexture(int id)
{
	for (int i=0;i<60;i++)
	{
		fwrite(&tc[id].names[i],1,sizeof(char),m_fileStream);
	}
}
void MyExporter::WriteCamera(int id)
{
	for (int i=0;i<50;i++)
	{
		fwrite(&cc[id].names[i],1,sizeof(char),m_fileStream);
	}
	fwrite(&cc[id].cx,1,sizeof(float),m_fileStream);
	fwrite(&cc[id].cy,1,sizeof(float),m_fileStream);
	fwrite(&cc[id].cz,1,sizeof(float),m_fileStream);

	fwrite(&cc[id].tx,1,sizeof(float),m_fileStream);
	fwrite(&cc[id].ty,1,sizeof(float),m_fileStream);
	fwrite(&cc[id].tz,1,sizeof(float),m_fileStream);
}

void MyExporter::WriteLight(int id)
{
	for (int i=0;i<50;i++)
	{
		fwrite(&lc[id].namesz[i],1,sizeof(char),m_fileStream);
	}
	fwrite(&lc[id].lighttype,1,sizeof(int),m_fileStream);
	for (i=0;i<12;i++)
	{
		fwrite(&lc[id].lmatrix[i],1,sizeof(float),m_fileStream);
	}
	for (i=0;i<12;i++)
	{
		fwrite(&lc[id].tmatrix[i],1,sizeof(float),m_fileStream);
	}
	fwrite(&lc[id].intensity,1,sizeof(float),m_fileStream);
	for (i=0;i<4;i++)
	{
		fwrite(&lc[id].atten[i],1,sizeof(float),m_fileStream);
	}
	fwrite(&lc[id].r,1,sizeof(char),m_fileStream);
	fwrite(&lc[id].g,1,sizeof(char),m_fileStream);
	fwrite(&lc[id].b,1,sizeof(char),m_fileStream);
}
void MyExporter::WriteEntity(int id)
{
	for (int i=0;i<12;i++)
	{
		fwrite(&ec[id].matrix[i],1,sizeof(float),m_fileStream);
	}
	for (i=0;i<100;i++)
	{
		fwrite(&ec[id].nameandparam[i],1,sizeof(char),m_fileStream);
	}
}

void MyExporter::WriteObject(int id)
{
	int i;

	fwrite(&oc[id].vertcount,1,sizeof(int),m_fileStream);
	fwrite(&oc[id].facecount,1,sizeof(int),m_fileStream);
	fwrite(&oc[id].tvcount,1,sizeof(int),m_fileStream);
	fwrite(&oc[id].sfcount,1,sizeof(int),m_fileStream);

	for (i=0;i<oc[id].vertcount;i++)
	{
		fwrite(&oc[id].mx[i],1,sizeof(float),m_fileStream);
		fwrite(&oc[id].my[i],1,sizeof(float),m_fileStream);
		fwrite(&oc[id].mz[i],1,sizeof(float),m_fileStream);
		fwrite(&oc[id].abone[i],1,sizeof(int),m_fileStream);
	}

	for (i=0;i<oc[id].facecount;i++)
	{
		fwrite(&oc[id].v1[i],1,sizeof(int),m_fileStream);
		fwrite(&oc[id].v2[i],1,sizeof(int),m_fileStream);
		fwrite(&oc[id].v3[i],1,sizeof(int),m_fileStream);
		fwrite(&oc[id].mat[i],1,sizeof(int),m_fileStream);
	}
	for (i=0;i<oc[id].tvcount;i++)
	{
		fwrite(&oc[id].tu[i],1,sizeof(float),m_fileStream);
		fwrite(&oc[id].tv[i],1,sizeof(float),m_fileStream);
	}
	for (i=0;i<oc[id].facecount;i++)
	{
		fwrite(&oc[id].t1[i],1,sizeof(int),m_fileStream);
		fwrite(&oc[id].t2[i],1,sizeof(int),m_fileStream);
		fwrite(&oc[id].t3[i],1,sizeof(int),m_fileStream);
	}

	for (i=0;i<oc[id].normalcount;i++)
	{
		fwrite(&oc[id].hx[i],1,sizeof(float),m_fileStream);
		fwrite(&oc[id].hy[i],1,sizeof(float),m_fileStream);
		fwrite(&oc[id].hz[i],1,sizeof(float),m_fileStream);
	}
				
	if (fh.vertexlights)
	{
		for (i=0;i<oc[id].normalcount;i++)
		{
			fwrite(&oc[id].cr[i],1,sizeof(char),m_fileStream);
			fwrite(&oc[id].cg[i],1,sizeof(char),m_fileStream);
			fwrite(&oc[id].cb[i],1,sizeof(char),m_fileStream);
		}
	}
	if (fh.shadowface)
	{
		for (i=0;i<oc[id].sfcount*9;i+=9)
		{
			fwrite(&oc[id].sf[i+0],1,sizeof(float),m_fileStream);
			fwrite(&oc[id].sf[i+1],1,sizeof(float),m_fileStream);
			fwrite(&oc[id].sf[i+2],1,sizeof(float),m_fileStream);
			
			fwrite(&oc[id].sf[i+3],1,sizeof(float),m_fileStream);
			fwrite(&oc[id].sf[i+4],1,sizeof(float),m_fileStream);
			fwrite(&oc[id].sf[i+5],1,sizeof(float),m_fileStream);

			fwrite(&oc[id].sf[i+6],1,sizeof(float),m_fileStream);
			fwrite(&oc[id].sf[i+7],1,sizeof(float),m_fileStream);
			fwrite(&oc[id].sf[i+8],1,sizeof(float),m_fileStream);
			//sprintf(dbuffer,"Exported %i/%i of shadow faces",i,oc[id].sfcount*9);AddDbg();
		}
	}

	fwrite(&oc[id].cx,1,sizeof(float),m_fileStream);
	fwrite(&oc[id].cy,1,sizeof(float),m_fileStream);
	fwrite(&oc[id].cz,1,sizeof(float),m_fileStream);

	fwrite(&oc[id].bx,1,sizeof(float),m_fileStream);
	fwrite(&oc[id].by,1,sizeof(float),m_fileStream);
	fwrite(&oc[id].bz,1,sizeof(float),m_fileStream);

	fwrite(&oc[id].kx,1,sizeof(float),m_fileStream);
	fwrite(&oc[id].ky,1,sizeof(float),m_fileStream);
	fwrite(&oc[id].kz,1,sizeof(float),m_fileStream);

	for (i=0;i<50;i++)
	{
		fwrite(&oc[id].namesz[i],1,sizeof(char),m_fileStream);
	}
}