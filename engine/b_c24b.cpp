#include "c24b.h"

c24b mono(unsigned char l)
{
	c24b resu;
	resu.r = l;resu.g = l;resu.b =l;
	return resu;
}

c24b c24b::operator / (float w)
{
	c24b rea;
	rea.r = r/w;
	rea.g = g/w;
	rea.b = b/w;
	return rea;
}
c24b c24b::operator /= (float w)
{
	r /= w;
	g /= w;
	b /= w;
	return *this;
}
c24b c24b::operator * (float w)
{
	c24b res;
	res.r =r*w;
	res.g =g*w;
	res.b =b*w;
	if (res.r > 255) res.r = 255;
	if (res.g > 255) res.g = 255;
	if (res.b > 255) res.b = 255;
	if (res.r < 0) res.r = 0;
	if (res.g < 0) res.g = 0;
	if (res.b < 0) res.b = 0;
	return res;

}

c24b& c24b::operator = (c24b &w)
{
	r = w.r;
	g = w.g;
	b = w.b;
	return *this;
}

c24b m24b(unsigned char r,unsigned char g,unsigned char b)
{
	c24b temp;
	temp.r = r;
	temp.g = g;
	temp.b = b;
	return temp;
}

c24b lin_interpolate(c24b c1,c24b c2,float d)
{
/*	vector3f linIp(const vector3f vsrc,const vector3f vdest,float tween)
{
	vector3f tw;
	tw.x = (vdest.x * tween) + vsrc.x * (1.0f - tween);
	tw.y = (vdest.y * tween) + vsrc.y * (1.0f - tween);
	tw.z = (vdest.z * tween) + vsrc.z * (1.0f - tween);
	return tw;
}*/

	c24b rt;
	float r2,g2,b2;
	rt.r = (unsigned char)(((float)c2.r * d) + (float)c1.r *( 1.0f - d));
	rt.g = (unsigned char)(((float)c2.g * d) + (float)c1.g *( 1.0f - d));
	rt.b = (unsigned char)(((float)c2.b * d) + (float)c1.b *( 1.0f - d));
	return rt;

}
/*
void IBitmap::randompal()
{
	c24b t1,t2;
	float z;

	for (int i=0;i<10;i++)
	{
		t2.r = rand()%255;
		t2.g = rand()%255;
		t2.b = rand()%255; 
		t1.r = rand()%255;
		t1.g = rand()%255;
		t1.b = rand()%255;
		z = 1;
		for (int x=i*16;x<i+1*16;x++)
		{
			pal[x].r = 255*linpt(t1.r,t2.r,z/16);
			pal[x].g = 255*linpt(t1.g,t2.g,z/16);
			pal[x].b = 255*linpt(t1.b,t2.b,z/16);
			z++;
		}

	}
}*/