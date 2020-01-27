#include "cbitmap.h"

void IBitmap::rplasma(int r,int freq,int x,int y)
{

		float x0,y0;
		float reng;
		if (x == -1) x = bw / 2;
		if (y == -1) y = bh / 2;
		for (int i=0;i<r;i++)
		{
			for (float j=0;j<360;j+=0.1f)
			{
				x0 = cos((j*pi)/180)*i;
				y0 = sin((j*pi)/180)*i;
				reng = sin((j*pi*freq)/180)*255;
				setpixel(x+x0,y+y0,mono(reng));
			}
		}

}

void IBitmap::sinplasma(int r,int freq,int x,int y)
{
		float x0,y0;
		float reng;
		if (x == -1) x = bw / 2;
		if (y == -1) y = bh / 2;
		for (int i=0;i<r;i++)
		{
			for (float j=0;j<360;j+=0.1f)
			{
				x0 = cos((j*pi)/180)*i;
				y0 = sin((j*pi)/180)*i;
				//reng = 128 + sin((i*pi*freq)/180)*128;
				reng = 128 + sin((i*pi*freq)/180)*128;
				setpixel(x+x0,y+y0,mono(reng));
			}
		}

}