#include "cbitmap.h"
#include "resmem.h"

IBitmap::IBitmap()
{
	for (int i=0;i<256;i++)
	{
		pal[i].r = i;
		pal[i].g = i;
		pal[i].b = i;
	}
}


void IBitmap::loadpal(char* path)
{
	FILE* bm = 0;
	bm = fopen(path,"rb");
	for (int i=0;i<256;i++)
	{
		fread(&pal[i].r,1,1,bm);
		fread(&pal[i].g,1,1,bm);
		fread(&pal[i].b,1,1,bm);
	}
	fclose(bm);
}

void IBitmap::loadres(char* name)
{

	long size;
	unsigned int bm = 0;
	bm = memopen(name,"BMR");
	MEMFILE *memfile = (MEMFILE *)bm;
	size = memfile->length;
	bytes = new byte [size];
	memseek(bm,54,0);
	memread(bytes,size-54,bm);
	total = size-54;
	memseek(bm,18,0);
	memread(&bw,4,bm);
	memseek(bm,22,0);
	memread(&bh,4,bm);
	memclose(bm);

}

void IBitmap::loadbmp(char* path)
{
	long size;
	FILE* bm = 0;
	bm = fopen(path,"rb");
	fseek(bm,0,2);
	size = ftell(bm);
	bytes = new byte [size];
	fseek(bm,54,0);
	fread(bytes,1,size-54,bm);
	total = size-54;
	fseek(bm,18,0);
	fread(&bw,4,1,bm);
	fseek(bm,22,0);
	fread(&bh,4,1,bm);
	fclose(bm);
}

void IBitmap::createbitmap(long width,long height)
{
	bw = width;
	bh = height;
	total = bw * bh;
	total = (total * 3);
	bytes = new byte [total];
	bytes = (byte*)malloc(sizeof(byte) * total);
	wastemem(bytes,total);
	fhed = new byte [54];
	fhed[0] = 0x42;
	fhed[1] = 0x4D;
	LTC(fhed,total+54,2);
	LTC(fhed,0,6);
	LTC(fhed,54,10);
	LTC(fhed,40,14);
	LTC(fhed,bw,18);
	LTC(fhed,bh,22);
	LTC(fhed,1572865,26);
	LTC(fhed,0,30);
	LTC(fhed,0,34);
	LTC(fhed,0,38);
	LTC(fhed,0,42);
	LTC(fhed,0,46);
	LTC(fhed,0,50);
}

void IBitmap::writebmp(char *path)
{
	FILE* bm =0;
	bm = fopen(path,"wb");

	fwrite(fhed,1,54,bm);
	fwrite(bytes,1,total,bm);
	fclose(bm);
	delete [] fhed;
	fhed = 0;
}

IBitmap::~IBitmap()
{
	if(!fhed)	delete [] fhed;	
	if(!bytes)	delete [] bytes;
}

void IBitmap::gettexid(bool alpha)
{
	int isize=3;
	isize*=bw;
	isize*=bh;

	glGenTextures(1, &ID);
	refilltex(alpha);
   
}

void IBitmap::refilltex(bool alpha)
{
	unsigned char* buf;
	if(!alpha)
	{
		buf = new unsigned char [3*bw*bh];
		c24b te;
		int nc,ng;
		for (int y=1;y<bh+1;y++)
		{
			for (int x=1;x<bw+1;x++)
			{
				te = getpixel(x,y);
				nc = y-1;
				ng = x-1;
			
				buf[(3*(bh-y)*bw)+(3*(x-1))+0] = te.r;
				buf[(3*(bh-y)*bw)+(3*(x-1))+1] = te.g;
				buf[(3*(bh-y)*bw)+(3*(x-1))+2] = te.b;
			}
		}
		glBindTexture(GL_TEXTURE_2D, ID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bw, bh, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bw, bh,GL_RGB, GL_UNSIGNED_BYTE, buf);
	}
	else
	{
		buf = new unsigned char [4*bw*bh];
		c24b te;
		for (int y=1;y<bh+1;y++)
		{
			for (int x=1;x<bw+1;x++)
			{
				te = getpixel(x,y);
															buf[(4*(bh-y)*bw)+(4*(x-1))+0] = te.r;
															buf[(4*(bh-y)*bw)+(4*(x-1))+1] = te.g;
															buf[(4*(bh-y)*bw)+(4*(x-1))+2] = te.b;
				if (te.r == 0 && te.g == 255 && te.b == 0){	buf[(4*(bh-y)*bw)+(4*(x-1))+3] = 0;}
				else{										buf[(4*(bh-y)*bw)+(4*(x-1))+3] = 255;}
	
			}
		}
		glBindTexture(GL_TEXTURE_2D, ID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bw, bh, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, bw, bh,GL_RGBA, GL_UNSIGNED_BYTE, buf);
	
	}
	delete [] buf;
}