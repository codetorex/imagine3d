#include "cbitmap.h"

void IBitmap::deneme()
{
	int a,r,x;
	float y=0;
	for (r=1;r<30;r++)
	{
		for (x=1;x<bw;x++)
		{
			y += 0.5f;
				a = 64+ sin((y*pi)/180)*128; 	
				float asd = cos((r*pi)/180);
				float as2 = sin((r*pi)/180);
				
				setpixel(64+ x*asd,128+a,mono(cos((x*pi)/180)*255));
		}
	}

}


void IBitmap::turkbayragi()
{
	fillall(m24b(255,0,0));
	drawcirc(bh/2,bh/2,32,m24b(255,255,255),true);
	drawcirc((bh/2) + (bh/16),bh/2,25,m24b(255,0,0),true);
	drawstar(112,bh/2,16,5,m24b(255,255,255),true);
}

void IBitmap::guimouse()
{
	
}

void IBitmap::invert()
{
	int x,y;
	c24b alet;
	for (y=1;y<bh+1;y++)
	{
		for (x=1;x<bw+1;x++)
		{
			alet = getpixel(x,y);
			setpixel(x,y,m24b(255-alet.r,255-alet.g,255-alet.b));
		}
	}
}


void IBitmap::resize(long dwidth,long dheight)
{
	IBitmap dbitmap; // destination bitmap object
	float alpha,f;
	long Ff,Fc;
	c24b p1,p2,pd;
	dbitmap.createbitmap(dwidth,bh);

	alpha = (float)bw / (float)dwidth; // resize factor
	
	for (int Sy=1;Sy<bh+1;Sy++)
	{
		for (int Dx=1;Dx<dwidth+1;Dx++)
		{
			f = alpha * Dx; // destination x from source x (facted x)
			Ff = floor(f);
			Fc = Ff+1;
			p1 = getpixel(Ff,Sy);
			p2 = getpixel(Fc,Sy);
			pd = lin_interpolate(p1,p2,(long)f-Ff);
			dbitmap.setpixel(Dx,Sy,pd);			
		}
	}
	dbitmap.writebmp("test.bmp");

	IBitmap fbitmap; // final bitmap
	fbitmap.createbitmap(dwidth,dheight);

	alpha = (float)bh / (float)dheight;

	for ( int Sx=1;Sx<dwidth+1;Sx++) 
	{
		for (int Dy=1;Dy<dheight+1;Dy++)
		{
			f = alpha * Dy;
			Ff = floor(f);
			Fc = Ff+1;
			p1 = dbitmap.getpixel(Sx,Ff);
			p2 = dbitmap.getpixel(Sx,Fc);
			pd = lin_interpolate(p1,p2,(long)f-Ff);
			fbitmap.setpixel(Sx,Dy,pd);
		}
	}
	fbitmap.writebmp("test-f.bmp");
}