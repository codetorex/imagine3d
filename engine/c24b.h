#ifndef COLOR_H
#define COLOR_H

class c24b
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;

	c24b operator / (float w);
	c24b operator /= (float w);
	c24b operator * (float w);
	c24b& operator = (c24b &w);

};

c24b m24b(unsigned char r,unsigned char g,unsigned char b);
c24b mono(unsigned char l);
c24b lin_interpolate (c24b c1,c24b c2,float d);

#endif