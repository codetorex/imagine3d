#ifndef CBITMAP_H
#define CBITMAP_H

#include <stdio.h>
#include "cvision.h"
#include <string.h>
#include <fstream.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"
#include "c24b.h"
#include "constant.h"

#define sint short int
#define byte unsigned char

class IBitmap
{
public:
	IBitmap();
	~IBitmap();
	byte* bytes;	
	byte* fhed;
	c24b pal[256];
	int total;
	
	long bw;
	long bh;
	unsigned int ID;

	// file operation
	void createbitmap(long width,long height);		// creates bitmap in memory
	void writebmp(char* path);						// writes bmp to harddrive

	void loadres(char* name);						// load bmp from resource
	void loadbmp(char* path);						// loads bmp
	void loadpal(char* path);

	// drawing
	void setpixel(long x,long y,c24b color);		// set pixel
	void setpixelw(long x,long y,long color);
	c24b getpixel(long x,long y);					// getpixel
	void drawline(long x,long y,long x2,long y2,c24b color); // line drawing
	void wideline(int x1, int y1, int x2, int y2, int thick,c24b color);
	void drawstar(long x,long y,long r,long gon,c24b color,bool fill = false);
	void drawcirc(long x,long y,long r,c24b color,bool fill=false);
	void perp(int x1, int y1, int dx, int dy, int thick,c24b color);
	void fillall(c24b color);

	//basic commands
	void matrixmul(float m[],int mw,int mh,bool mabs = true); // matrix multiplicion m is pointer mw is matrix width mh is matrix height
	void monochrome();								// make monochrome
	void blend(IBitmap &oter);						// blend another texture
	void add(IBitmap &oter);

	void gettexid(bool alpha=false);				// get texture id for OpenGL
	void refilltex(bool alpha=false);				// refresh texture in GL memory
	void recolor();
	
	// image processing algorithms
	void sharpen();									// make sharpen
	void emboss();									// make emboss
	void edged();									// make edged
	void blur();									// make blur
	void resize(long dwidth,long dheight);			// resize image

	// utilites
	void histogram();								// take histogram
	void centergradient(int r,int x=-1,int y=-1);	// make center gradient
	void cellular(int pc,c24b palette,int style=0,bool ast=false);
	void pnoise(float z,float scal=16.0f);
	void rplasma(int r,int freq,int x=-1,int y=-1);
	void sinplasma(int r,int freq,int x=-1,int y=-1);
	void randompal();
	void invert();
	void deneme();

	// presets
	void turkbayragi();
	void guimouse();

};
#endif	