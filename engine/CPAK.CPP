#include <windows.h>	
#include <gl\gl.h>		
#include <gl\glu.h>		
#include <gl\glaux.h>	
#include <fstream.h>
#include "cpak.h"
#include <string>
#include "math.h"





void CPak::OpenPak (char* filename)
{

	fstream paq ( filename ,ios::binary|ios::in);
	paq.read ((char *)&hPAK,12);
	paq.seekp (hPAK.diroffset);
	filecount = hPAK.dirlength / 64;
	dPAK = new pakdir [filecount];
	for (int i = 0;i < filecount ;i++)
	{
		paq.read ((char *)&dPAK[i].filename,56);
		paq.read ((char *)&dPAK[i].filepos ,4);
		paq.read ((char *)&dPAK[i].filelength ,4);
	};
	curfile = filename;
	paq.close();
};


int CPak::ReturnPos (char* fname)
{
	int fileno = -1;
	for (int i = 0 ; i < filecount;i++)
	{
		if (strcmp(fname,dPAK[i].filename) == 0 )
		{
			fileno = i;
		};

	};
	if (fileno == -1)
	{
		return -1;
	};
	return dPAK[fileno].filepos;
}



