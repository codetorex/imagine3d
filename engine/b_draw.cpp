#include "cbitmap.h"


void IBitmap::perp(int x1, int y1, int dx, int dy, int thick,c24b color)
{
    int sx = (dx > 0)? 1: -1;
    int sy = (dy > 0)? 1: -1;
    int ax = 2*sx*dx;
    int ay = 2*sy*dy;
    int x = x1;
    int y = y1;
    int T = thick;

    if (ax > ay) {
        int d = ay - ax/2;
        while (1) {
            if (T-- <= 0) return;
            if (d >= 0) {
                y += sy;
                setpixel(x,y,color);
                d -= ax;
            }
            x += sx;
            d += ay;
            setpixel(x,y,color);
        }
    }
    else {
        int d = ax - ay/2;
        while (1) {
            if (T-- <= 0) return;
            if (d >= 0) {
                x += sx;
                setpixel(x,y,color);
                d -= ay;
            }
            y += sy;
            d += ax;
            setpixel(x,y,color);
        }
    }
}

void IBitmap::setpixel(long x,long y,c24b color)
{
	int tp;
	x--;y--;
	tp = (bh - y) * bw * 3;
	tp = tp + ( x * 3) - (bw * 3);
	if (color.b == color.g && color.r == color.g)
	{
		//mono color, maybe we use palette
		bytes[tp + 0] = pal[color.r].b;
		bytes[tp + 1] = pal[color.r].g;
		bytes[tp + 2] = pal[color.r].r;
	}
	else
	{
		bytes[tp + 0] = color.b;
		bytes[tp + 1] = color.g;
		bytes[tp + 2] = color.r;
	}
}
void IBitmap::setpixelw(long x,long y,long color)
{
	int tp;
	x--;y--;
	tp = (bh - y) * bw * 3;
	tp = tp + ( x * 3) - (bw * 3);

	unsigned char* temp;
	temp = new unsigned char [4];
	memcpy(temp,&color,4);
	bytes[tp + 0] = temp[3];
	bytes[tp + 1] = temp[2];
	bytes[tp + 2] = temp[1];

	delete [] temp;
}

c24b IBitmap::getpixel(long x,long y)
{
	int tp;
	c24b temp;
	x--;y--;
	tp = (bh - y) * bw * 3;
	tp = tp + ( x * 3) - (bw * 3);
	temp.b = bytes[tp+0];
	temp.g = bytes[tp+1];
	temp.r = bytes[tp+2];
	return temp;
}

void IBitmap::wideline(int x1, int y1, int x2, int y2, int thick,c24b color)
{
    int dx = x2-x1;
    int dy = y2-y1;
    int sx = (dx > 0)? 1: -1;
    int sy = (dy > 0)? 1: -1;
    int ax = 2*sx*dx;
    int ay = 2*sy*dy;
    int x = x1;
    int y = y1;

    if (ax > ay) {
        int d = ay - ax/2;
        while (1) {
            setpixel(x,y,color);
            perp(x,y,dy,-dx, thick/2,color);
            perp(x,y,-dy,dx, thick-thick/2-1,color);
            if (x == x2)  return;
            if (d >= 0) {
                y += sy;
                d -= ax;
            }
            x += sx;
            d += ay;
        }
    }
    else {
        int d = ax - ay/2;
        while (1) {
            setpixel(x,y,color);
            perp(x,y,dy,-dx, thick/2,color);
            perp(x,y,-dy,dx, thick-thick/2-1,color);
            if (y == y2)  return;
            if (d >= 0) {
                x += sx;
                d -= ay;
            }
            y += sy;
            d += ax;
        }
    }
}

void IBitmap::drawline(long x,long y,long x2,long y2,c24b color)
{
	bool yLonger=false;
	int incrementVal;
	int shortLen=y2-y;
	int longLen=x2-x;

	if (abs(shortLen)>abs(longLen)) {
		int swap=shortLen;
		shortLen=longLen;
		longLen=swap;
		yLonger=true;
	}

	if (longLen<0) incrementVal=-1;
	else incrementVal=1;

	double multDiff;
	if (longLen==0.0) multDiff=(double)shortLen;
	else multDiff=(double)shortLen/(double)longLen;
	if (yLonger) {
		for (int i=0;i!=longLen;i+=incrementVal) {
			setpixel(x+(int)((double)i*multDiff),y+i,color);
		}
	} else {
		for (int i=0;i!=longLen;i+=incrementVal) {
			setpixel(x+i,y+(int)((double)i*multDiff),color);
		}
	}
}

void IBitmap::drawstar(long x,long y,long r,long gon,c24b color,bool fill)
{
	int stp = 360 / gon;
	int x1,y1,x2,y2;
	if (!fill)
	{
		for (int i=0;i<360;i+=stp)
		{
			x1 = cos((i*pi)/180) * r;
			y1 = sin((i*pi)/180) * r;
			x2 = cos(((i+2*stp)*pi)/180) * r;
			y2 = sin(((i+2*stp)*pi)/180) * r;
			drawline(x+x1,y+y1,x+x2,y+y2,color);
		}
	}
	else
	{
		for (int s=r;s>0;s--)
		{
			for (int i=0;i<360;i+=stp)
			{
				x1 = cos((i*pi)/180) * s;
				y1 = sin((i*pi)/180) * s;
				x2 = cos(((i+2*stp)*pi)/180) * s;
				y2 = sin(((i+2*stp)*pi)/180) * s;
				drawline(x+x1,y+y1,x+x2,y+y2,color);
			}
		}

	}
}

void IBitmap::drawcirc(long x,long y,long r,c24b color,bool fill)
{
	float stp=4*r;
	stp/=r*r;
	int x1,y1;

	if (!fill)
	{
		for (float i=0;i<360;i+=stp)
		{
			x1 = cos((i*pi)/180) * r;
			y1 = sin((i*pi)/180) * r;
			setpixel(x+x1,y+y1,color);
		}
	}
	else
	{
		for (int s=r;s>0;s--)
		{
			for (float i=0;i<360;i+=stp)
			{
				x1 = cos((i*pi)/180) * s;
				y1 = sin((i*pi)/180) * s;
				setpixel(x+x1,y+y1,color);
			}
		}
	}
}

void IBitmap::fillall(c24b color)
{
	for (int y=1;y<bh+1;y++)
	{
		for (int x=1;x<bw+1;x++)
		{
			setpixel(x,y,color);
		}
	}
}