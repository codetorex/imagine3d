#include "cbitmap.h"

void IBitmap::cellular(int pc,c24b palette,int style,bool ast)
{
	int* xcord;
	int* ycord;
	float* distb;
	xcord = new int [pc];
	ycord = new int [pc];
	distb = new float [bw*bh];
	float di;
	float tm=999999.0f;
	float tm2 = 999999.0f;

	float mindist = 999999.0f ;
	float maxdist = 0 ;
	int he;
	int x,y,i;
	float ntm;
	float la;
	int lcha;

	for (i=0;i<pc;i++)
	{
		xcord[i] = 1+ (rand()/(int)(((unsigned)RAND_MAX + 1) / bw));
		ycord[i] = 1+ (rand()/(int)(((unsigned)RAND_MAX + 1) / bh));
	}

	for (y=1;y<bh;y++)
	{
		for(x=1;x<bw;x++)
		{
			for (i=0;i<pc;i++)
			{
				di = sqrt( (xcord[i]-x)*(xcord[i]-x) + (ycord[i]-y)*(ycord[i]-y));
				if (di < tm){tm = di;lcha=i;}
			}
			if (style == 0) ntm = tm;
			if (style == 3) ntm = tm*tm;
			
			if (style == 1)
			{
				for (i=0;i<pc;i++)
				{
					di = sqrt( (xcord[i]-x)*(xcord[i]-x) + (ycord[i]-y)*(ycord[i]-y));
					if (di <tm2 && i!=lcha) tm2 = di;
				}
				ntm = tm2 - tm;
			}
			if (style == 2)
			{
				for (i=0;i<pc;i++)
				{
					di = sqrt( (xcord[i]-x)*(xcord[i]-x) + (ycord[i]-y)*(ycord[i]-y));
					if (di <tm2 && i!=lcha) tm2 = di;
				}
				ntm = tm2 * tm;
			}

			he = ((y-1)*bh) + (x-1);			
			distb[he] = ntm;
			if (tm < mindist) mindist = ntm;
			if (tm > maxdist) maxdist = ntm;
			tm = 999999.0f;
			tm2 = 999999.0f;
		}
	}

	for (y=1;y<bh+1;y++)
	{
		for(x=1;x<bw+1;x++)
		{
			he = ((y-1)*bh) + (x-1);
			c24b col;
			la =((distb[he]-mindist) / (maxdist-mindist));
			if (ast) la = 1-la;
			if (la > 1) la = 1;
			if (la < 0) la = 0;
			col.r =(palette.r*la);
			col.g =(palette.g*la);
			col.b =(palette.b*la);
			setpixel(x,y,col);
		}
	}
	delete [] xcord; xcord = 0;
	delete [] ycord; ycord = 0;
	delete [] distb; distb = 0;

}