#ifndef GUI_H
#define GUI_H

#include "c24b.h"
#include "cvision.h"
//Init
void StartGUI(int deffont,int smafont,unsigned int cbox0,unsigned int cbox1,int mouse);
//backgrd
void GBackGrd(float x,float y,float width,float height);
//options
void GSCur(bool olsunmu);
void GCAdd(char* what);
// Render
void GConsole();
void GCursor();
void GCInit();

// baskabiseye gerek yok
class GuiH // gui handle
{
public:
	GuiH*	pid;	// parent
	int		x;		// screen x
	int		y;		// screen y
	int		width;	// object width
	int		height;	// object height
	bool	visible;
};

void CHandle(GuiH* ghand,int x,int y,int width,int height,bool visible,GuiH* parent);

class GButton
{
public:
	GButton();
	GuiH	ghand;
	//properties
	c24b	backclr;
	char*	caption;
	bool	talign;
	bool	pressed;
	bool	pressed2;
	bool	isover;
	int		picture;
	int		font;
	//render
	void	render();
};

class GWindow
{
	GButton but;
	float ssx,ssy;
	float msx,msy;
public:
	GWindow();// pencerenin parenti olmaz!
	GuiH	ghand;
	//properties
	c24b	backclr;
	c24b	barclr;
	char*	caption;
	int		picture;
	int		icon;
	int		font;
	//render
	void	render();
};

class GLabel
{
public:
	GLabel();
	GuiH	ghand;
	//properties
	c24b	textclr;
	char*	caption;
	int		font;
	bool border;
	//render
	void	render();
};



class GTextbox
{
public:
	GTextbox();
	GuiH	ghand;
	//properties
	c24b	backclr;
	c24b	textclr;
	char*	text;
	//render
	void	render();
};

class GCheckBox
{
private:
	int lt;
public:
	GCheckBox();
	GuiH	ghand;
	//properties
	unsigned int pic0;
	unsigned int pic1;
	char*	caption;
	bool	value;
	//render
	void	render();
};

class GProgressBar
{
public:
	GProgressBar();
	GuiH	ghand;
	//properties
	int		back;
	int		tick;
	int		value; // percent
	c24b	barclr;
	c24b	backclr;
	//render
	void	render();
};

class GSlider
{
private:
	float	sx;
	int		lc;
	int		mx;
	GButton bsl;
public:
	GSlider();
	GuiH	ghand;
	//properties
	int		value;
	int		min;
	int		max;
	//render
	void	render();
};

class GTexture
{
public:
	GTexture();
	GuiH ghand;
	// propertise
	bool	border;
	int		texid;
	// render
	void render();
};

class GFrame
{
	GFrame();
	GuiH	ghand;
	//properties
	c24b	backcolor;
	char*	caption;
	//render
	void	render();
};

#endif