#ifndef CG_H
#define CG_H

// TODO: guiyi yenile cok super seyler ekle
// TODO: x y ve en boy classlarda tanimlansin ve init ederken (34,356,453,3) gibi olsun


#include "cvision.h"
#include "ctexture.h"
#include "ctypes.h"

void GDefFont (unsigned int font);
void GSmaFont (unsigned int font);
void GCBox(unsigned int t1,unsigned int t2);
void GCTex(unsigned int t1);

void GCInit();
void GConsole();
void GCAdd(char* what);

void GCursor();
void GSCur(bool olsunmu);

void GBackGrd(float x,float y,float width,float height);

class GButton
{
public:
	GButton();	
	bool isslider;
	bool pressed;
	bool pressed2;
	char* Caption;
	fcolor3 BackColor;
	void render(float x,float y,float height,float width);	
	bool ispressed();
	bool isover;
	bool protection;
};

class GSlider
{
private:
	float sx;
	int lc;
	int mx;
	GButton myslide;
public:
	GSlider();
	int value;
	float min,max;
	void render(float x,float y,float width,float height);
};

class GCheckBox
{
private:
	int lt;
public:
	GCheckBox();
	bool value;
	int style;
	char* caption;
	void render(float x,float y);
};

class GProgressBar
{
public:
	GProgressBar();
	int percent; 
	void render(float x,float y,float height,float width); 
	CTexture texture;
	fcolor3 BackColor; 
	fcolor3 BarColor; 
};

class GFrame
{
public:
	GFrame();
	void render(float x, float y, float height,float width);
	fcolor3 BackColor;

};

class GWindow
{
public:
	GWindow();
	void render(float x,float y,float height,float width);
	fcolor3 BackColor;
	fcolor3 BarColor;
	char* caption;
};

class GLabel
{
public:
	GLabel();
	void render(float x,float y, float height,float width,bool border = false);
	fcolor3 textcolor;
	char* caption;
};

class GTextBox
{
public:
	GTextBox();
	void render(float x, float y, float height,float width);
	fcolor3 textcolor;
	char* text;
};

class GPB
{
public:
	GPB();
	void render(float x, float y,float height, float width);
	int percent;
	fcolor3	ProgressColor;
};

#endif