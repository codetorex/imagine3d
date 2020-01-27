#include "stdafx.h"
#include "exporter.h"

void MyExporter::WriteBones()
{
	WriteIMBHeader();
	for (int i=0;i<bh.bonecount;i++)
	{
		WriteBone(i);
	}
	sprintf(dbuffer,"Total %i bones exported.",bh.bonecount);AddDbg();
	sprintf(dbuffer,"Export tooks %i ms.",GetTickCount()-elaptimer);AddDbg();

	fclose(m_fileStream);
}

void MyExporter::WriteIMBHeader()
{
	fwrite(&bh.signature,1,sizeof(int),m_fileStream);
	fwrite(&bh.bonecount,1,sizeof(int),m_fileStream);
	fwrite(&bh.keystart,1,sizeof(int),m_fileStream);
	fwrite(&bh.keyend,1,sizeof(int),m_fileStream);
	fwrite(&bh.framerate,1,sizeof(int),m_fileStream);
//	fwrite(&bh.ticksperframe,1,sizeof(int),m_fileStream);
}

void MyExporter::WriteBone(int id)
{
	fwrite(&bcon[id].boneid,1,sizeof(int),m_fileStream);
//	fwrite(&bcon[id].parentid,1,sizeof(int),m_fileStream);
//	fwrite(&bcon[id].childid,1,sizeof(int),m_fileStream);
	fwrite(&bcon[id].framec,1,sizeof(int),m_fileStream);
	//sprintf(dbuffer,"Bone:%i Parent:%i Child:%i FrameCount:%i",bcon[id].boneid,bcon[id].parentid,bcon[id].childid,bcon[id].framec);AddDbg();
	for (int i=0;i<bcon[id].framec;i++)
	{
		fwrite(&bcon[id].frames[i].frameno,1,sizeof(int),m_fileStream);
		//sprintf(dbuffer,"-- Frame: %i Framestart: %i",i,bcon[id].frames[i].frameno);AddDbg();

		fwrite(&bcon[id].frames[i].xPos,1,sizeof(float),m_fileStream);
		fwrite(&bcon[id].frames[i].yPos,1,sizeof(float),m_fileStream);
		fwrite(&bcon[id].frames[i].zPos,1,sizeof(float),m_fileStream);

		fwrite(&bcon[id].frames[i].xRot,1,sizeof(float),m_fileStream);
		fwrite(&bcon[id].frames[i].yRot,1,sizeof(float),m_fileStream);
		fwrite(&bcon[id].frames[i].zRot,1,sizeof(float),m_fileStream);


/*		for (int j=0;j<12;j++)
		{
			fwrite(&bcon[id].frames[i].m[j],1,sizeof(float),m_fileStream);
			//sprintf(dbuffer,"---- Matrix[%i] = %f",j,bcon[id].frames[i].m[j]);AddDbg();
		}*/
	}
	// taam
}