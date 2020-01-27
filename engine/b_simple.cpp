#include "cbitmap.h"

void IBitmap::histogram()
{
	int pco=0;
	for (int i=1;i<bw+1;i++){
		for (int j=1;j<bh+1;j++){
			c24b tcl;
			tcl = getpixel(i,j);
			if (tcl.r != 0 && tcl.g !=0 && tcl.b !=0)
			{
				pco++;
			}
		}

		for (j=1;j<bh+1;j++)
		{
			setpixel(i,j,m24b(0,0,0));
		}

		for (j=(bh-pco);j<bh+1;j++)
		{
			setpixel(i,j,m24b(255,255,255));
		}
		pco = 0;
	}
}

void IBitmap::centergradient(int r,int x,int y)
{
		float pi = 3.141592f;
		float x0,y0;
		if (x == -1) x = bw / 2;
		if (y == -1) y = bh / 2;
		for (int i=0;i<r;i++)
		{
			for (float j=0;j<360;j+=0.1f)
			{
				x0 = cos((j*pi)/180)*i;
				y0 = sin((j*pi)/180)*i;
				setpixel(x+x0,y+y0,mono(255-((i*255)/r)));
			}
		}
}

void IBitmap::monochrome()
{
	c24b t;
	char tmp;
	for (int i=1;i<bw+1;i++){
		for (int j=1;j<bh+1;j++){
		t = getpixel(i,j);
		tmp = (t.r + t.g + t.b) / 3;
		setpixel(i,j,mono(tmp));
		}
	}

}

void IBitmap::blend(IBitmap &oter)
{
	c24b t1,g1,c1;
	char a,b,c;
	
	for (int i=1;i<bw+1;i++){
		for (int j=1;j<bh+1;j++){
	
		t1 = getpixel(i,j);
		g1 = oter.getpixel(i,j);
		

		//g1 /= (100 / alpha);
		//t1 /= (100 / (100-alpha));
		if ( g1.r != 0 && g1.g !=0 && g1.b != 0)
		{

		c1.r = (t1.r + g1.r) / 2;
		c1.g = (t1.g + g1.g) / 2;
		c1.b = (t1.b + g1.b) / 2;
		}
		else
		{
		c1.r = t1.r;
		c1.g = t1.g;
		c1.b = t1.b;
		}
		
		setpixel(i,j,c1);
		}
	}
}

void IBitmap::add(IBitmap &oter)
{
	c24b t1,g1,c1;
	char a,b,c;
	
	for (int i=1;i<bw+1;i++){
		for (int j=1;j<bh+1;j++){
	
		t1 = getpixel(i,j);
		g1 = oter.getpixel(i,j);
		

		//g1 /= (100 / alpha);
		//t1 /= (100 / (100-alpha));
		if ( g1.r != 0 && g1.g !=0 && g1.b != 0)
		{

		c1.r = (t1.r + g1.r);
		c1.g = (t1.g + g1.g);
		c1.b = (t1.b + g1.b);
		}
		else
		{
		c1.r = t1.r;
		c1.g = t1.g;
		c1.b = t1.b;
		}
		
		setpixel(i,j,c1);
		}
	}
}

void IBitmap::recolor()
{
	c24b r;
	monochrome();
	for (int y=1;y<bh;y++)
	{
		for (int x=1;x<bw;x++)
		{
			r = getpixel(x,y);
			setpixel(x,y,r);
		}
	}
}