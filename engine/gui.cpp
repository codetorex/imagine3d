#include <string.h>
#include <math.h>
#include <stdio.h>
#include "gui.h"
//#include <iostream.h>



unsigned int fontbase;
unsigned int smallfont;
unsigned int gcb1,gcb2;
unsigned int curtex;

char* clin[15];
char temp[100];

GLabel  lines;
GLabel contex;
int lace=0;
bool cshow=true;
char b;

void StartGUI(int deffont,int smafont,unsigned int cbox0,unsigned int cbox1,int mouse)
{
	fontbase = deffont;
	smallfont = smafont;
	gcb1 = cbox0;
	gcb2 = cbox1;
	curtex = mouse;
}

void GCursor()
{
	if (cshow)
	{
		Enter2D();
		
		glBindTexture(GL_TEXTURE_2D,curtex);
		glTranslated(GetMouseX(),GetHeight()-GetMouseY(),0);
			glColor3f(1 ,1 ,1);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			RenderPicture(0,0,16,-16);
			diTP();
		Exit2D();
	}
}

void GSCur(bool olsunmu){cshow = olsunmu;}

void CHandle(GuiH* ghand,int x,int y,int width,int height,bool visible,GuiH* parent)
{
	ghand->x = x;
	ghand->y = y;
	ghand->height = height;
	ghand->width = width;
	ghand->visible = visible;
	ghand->pid = parent;
}
void GConsole()
{
GBackGrd(0,0,GetWidth(),-13*16);
lines.textclr = m24b(255,255,255);
contex.textclr = m24b(255,255,255);
CHandle(&contex.ghand,0,195,GetWidth(),13,true,0);
lines.ghand.x = 0;
lines.ghand.height = 13;
lines.ghand.width = GetWidth();

	for (int i = 0;i<15;i++)
	{
		lines.caption = clin[i];
		lines.ghand.y = i*13;
		lines.render();
	}
	contex.render();

	if (GetTickCount() - lace > 150)
	{	

			for (i = 65;i <91;i++)
			{
				if (!IsKeyPress(VK_SHIFT))
				{
					if (IsKeyPress(i) == true )
					{	
						
						b = (char)i + 32;//+ 32;
						strcat(contex.caption,&b);
						SetKeyPress(i,false);
						
					};
				}else{
					
					if (IsKeyPress(i) == true )
					{
						strcat(contex.caption,(char*)&i);
						SetKeyPress(i,false);
					};

				};
			};
			for (i =48;i<58;i++)
			{
					if (IsKeyPress(i) == true )
					{
					strcat(contex.caption,(char*)&i);
					SetKeyPress(i,false);
					}
			}
				if (IsKeyPress(190)) {strcat(contex.caption,".");SetKeyPress(190,false);}
				if (IsKeyPress(32))  {strcat(contex.caption," ");SetKeyPress(32,false);}
				if (IsKeyPress(222)) {strcat(contex.caption,"i");SetKeyPress(222,false);}
				if (IsKeyPress(111)) {strcat(contex.caption,"/");SetKeyPress(111,false);}
			
			/*for ( i = 0; i<255 ; i++)
			{
				if (IsKeyPress(i) )
				{
					sprintf(contex.caption,"%i",i);
				};
			}*/
		
		if ( IsKeyPress(VK_RETURN) )
		{
		GCAdd((char*)contex.caption);
		delete [] contex.caption;
		contex.caption = 0;
		contex.caption = new char[100];
		strcpy(contex.caption,"\0");
		//contex.caption = "";
		lace = GetTickCount();
		}
	}

}

void GCAdd(char* what)
{

//	temp = "";
	for (int i = 0;i<14;i++)
	{
		//clin[i] = clin[i+1];
		strcpy(clin[i],clin[i+1]);
	}
	strcpy(temp,what);
	clin[14] = temp;
	//strcpy(clin[14],what);
}

void GCInit()
{
	for (int i=0;i<15;i++)
	{
		clin[i] = new char [100];
		strcpy(clin[i],"\0");
	}
}
void GBackGrd(float x,float y,float width,float height)
{
	Enter2D();
	y = GetHeight() - y;
	glBindTexture(GL_TEXTURE_2D,0);
	glTranslated(x,y,0);
		glColor4f(0 ,0 ,0.8f,0.7f);
		enTP();
		RenderPicture(0,0,width,height);
		diTP();
	Exit2D();

}


GSlider::GSlider()
{
	min = 0;
	max = 100;
	sx = 0;
	mx = 0;
	value = 0;
	bsl.pressed = false;
	bsl.font = smallfont;
	lc = GetTickCount();
	ghand.x = 0;
	ghand.y = 0;
	ghand.width = 0;
	ghand.height = 0;
	ghand.visible = true;
	ghand.pid=0;
	bsl.pressed = false;
	bsl.font = smallfont;
}

void GSlider::render()
{
	float x,y,w,h,tm;
	if (ghand.pid != 0)
	{
		x = ghand.pid->x + ghand.x;
		y = GetHeight()- (ghand.pid->y + ghand.y);
		w = ghand.width;
		h = -ghand.height;
	}
	else
	{
		x = ghand.x;
		y =GetHeight()-ghand.y;
		w = ghand.width;
		h = -ghand.height;
	}

	Enter2D();
	glBindTexture(GL_TEXTURE_2D,0);
	glTranslated(x,y,0);
	float maz;

	maz = h / 2;
	glColor3f(0.7f,0.7f,0.7f);
	RenderPicture( 0,maz,w,2);

	glColor3f(0.5f , 0.5f , 0.5f );
	glBegin(GL_LINES);
		glVertex2f(0,maz); glVertex2f(0,maz+2);
		glVertex2f(0,maz+2); glVertex2f(w,maz+2);
	glEnd();
	glColor3f(1.0f , 1.0f , 1.0f );
	glBegin(GL_LINES);
		glVertex2f(w,maz); glVertex2f(w,maz+2);
		glVertex2f(0,maz); glVertex2f(w,maz);
	glEnd();

	if (min <0){
		if (sx == 0) {sx = w/2;value = (int)( (((sx)*(max-min))/w) - ((max-min)/2) );}
	}else{
		if (sx == 0) {sx = 0;value = min;}
	}
	//sx = sx + x;

	if ( bsl.pressed)
	{
		tm = (float)GetMouseX();
		sx = tm - x;
		if ( tm > x+w )
		{
			sx = w;
		}
		if (tm < x-1)
		{
			sx = 0;
		}

		if (min <0){
			value = (int)( (((sx)*(max-min))/w) - ((max-min)/2) );
		}else{
			value = (int)( (((sx)*(max-min))/w) );
		};
		
		bsl.pressed = false;
	}
	else
	{
	}

	Exit2D();
	sprintf(bsl.caption,"%i",value);
	bsl.font = -2;

	bsl.ghand.x =x+ sx-5;

	bsl.ghand.y = GetHeight()-y;
	bsl.ghand.width = 10;
	bsl.ghand.height = -h;


	//CHandle(&bsl.ghand,sx-5,GetHeight() - y,10,h,true,0);
	bsl.render(); 
}

GCheckBox::GCheckBox()
{
	value = false;
	pic0 = 0;
	pic1 = 0;
	caption = "";
	ghand.x = 0;
	ghand.y = 0;
	ghand.width = 0;
	ghand.height = 0;
	ghand.visible = true;
	lt = GetTickCount();
	ghand.pid=0;
}

void GCheckBox::render()
{
	float x,y,w,h;
	if (ghand.pid != 0)
	{
		x = ghand.pid->x + ghand.x;
		y = GetHeight()- (ghand.pid->y + ghand.y);
		w = ghand.width;
		h = -ghand.height;
	}
	else
	{
		x = ghand.x;
		y =GetHeight()-ghand.y;
		w = ghand.width;
		h = -ghand.height;
	}

		pic0 = gcb1;
		pic1 = gcb2;

	Enter2D();
	glBindTexture(GL_TEXTURE_2D,0);
	glTranslated(x,y,0);
	glColor3ub(200,200,200);
	glBindTexture(GL_TEXTURE_2D, pic0);
	RenderPicture(0,0,13,13);

	y = y + 16;
	if (GetMouseX() > x && GetMouseX() < x + 13 && GetMouseY() > GetHeight() - y+h && GetMouseY() < (GetHeight() - y) + 13 )
	{
		glColor4f(0 ,0 ,0.8f,0.5f);
		enTP();
		RenderPicture(0,0,13,13);
		diTP();
		if (GetMouseClick(0))
		{
			if (GetTickCount() - lt > 200)
			{
			lt = GetTickCount();
			value = !value;
			}
		}
	}
	if (value )
	{
		glBindTexture(GL_TEXTURE_2D, pic1);
		RenderPicture(0,0,13,13);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4ub(200,200,200,255);
	glRasterPos2f(4*sizeof(caption)+3,13/2-3);
	PrintText(fontbase,caption);
	Exit2D();
}

GTexture::GTexture()
{
	ghand.x = 0;
	ghand.y = 0;
	ghand.width = 0;
	ghand.height = 0;
	ghand.visible = true;
	ghand.pid=0;
	texid = 0;
	border = true;
};

void GTexture::render()
{
	float x,y,w,h;
	if (ghand.pid != 0)
	{
		x = ghand.pid->x + ghand.x;
		y = GetHeight()- (ghand.pid->y + ghand.y);
	}
	else
	{
		x = ghand.x;
		y =GetHeight()-ghand.y;
	}
	w = ghand.width;
	h = -ghand.height;

	Enter2D();
	glBindTexture(GL_TEXTURE_2D, texid);
	glTranslated(x,y,0);
	glColor3ub(255,255,255);
	RenderPicture(0,0,w,h);
	glColor3ub(0,0,0);
	glBegin(GL_LINES);
		glVertex2f(0,0); glVertex2f(0,h); // sol
		glVertex2f(0,0); glVertex2f(w,0); // ust
		glVertex2f(w,0); glVertex2f(w,h); // sag
		glVertex2f(0,h); glVertex2f(w,h); // alt
	glEnd();

	Exit2D();
}

GButton::GButton()
{
	caption = "\0";
	caption = new char [100];
	backclr = m24b(204,204,204);
	pressed = false;
	font = -1;
	ghand.x = 0;
	ghand.y = 0;
	ghand.width = 0;
	ghand.height = 0;
	ghand.visible = true;
	ghand.pid=0;
	talign = true; // center of text
}

void GButton::render()
{
	float x,y,w,h;
	if (ghand.pid != 0)
	{
		x = ghand.pid->x + ghand.x;
		y = GetHeight()- (ghand.pid->y + ghand.y);
		w = ghand.width;
		h = -ghand.height;
	}
	else
	{
		x = ghand.x;
		y =GetHeight()-ghand.y;
		w = ghand.width;
		h = -ghand.height;
	}
	if (font == -1)
	{
		font = fontbase;
	}
	if (font == -2)
	{
		font = smallfont;
	}
	Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3ub(backclr.r , backclr.g , backclr.b );
	glTranslated(x,y,0);
	RenderPicture(0,0,w,h);
	glColor3f(1.0f , 1.0f , 1.0f );
	glBegin(GL_LINES);
		glVertex2f(0,0); glVertex2f(0,h); // sol
		glVertex2f(0,0); glVertex2f(w,0); // ust
	glEnd();
	glColor3f(0.5f , 0.5f , 0.5f );
	glBegin(GL_LINES);
		glVertex2f(w,0); glVertex2f(w,h); // sag
		glVertex2f(0,h); glVertex2f(w,h); // alt
	glEnd();

	glColor3f(0 , 0 , 0 );
	if(talign)
	{
		glRasterPos2f(w/2-(3*strlen(caption)),h/2-(2));
	}
	else
	{
		glRasterPos2f(3,h/2-(2));		
	}
	PrintText(font, caption);
	y = y + h;
	if (GetMouseX() > x && GetMouseX() < x + w && GetHeight()-GetMouseY() < y+ (-h)  && GetHeight()-GetMouseY() > y )
	{
		glColor4f(0 ,0 ,0.8f,0.5f);
		enTP();
		RenderPicture(0,0,w,h);
		diTP();
		if (GetMouseClick(0))
		{
			pressed=true;
		}
		else
		{
			pressed=false;
		};
		if (GetMouseClick(1))
		{
			pressed2=true;
		}
		else
		{
			pressed2=false;
		};

		isover = true;
	}
	else
	{
		isover = false;
	};

	Exit2D();
}

GProgressBar::GProgressBar()
{
	value = 0;
	barclr = m24b(0,0,153);
	backclr = m24b(1,1,1);
	ghand.x = 0;
	ghand.y = 0;
	ghand.width = 0;
	ghand.height = 0;
	ghand.visible = true;
	ghand.pid=0;
}

void GProgressBar::render()
{
	float x,y,w,h;
	float pr;
	if (value > 100) value = 100;
	if (value < 0) value = 0;
	if (ghand.pid != 0)
	{
		x = ghand.pid->x + ghand.x;
		y = (GetHeight()-ghand.pid->y) + (GetHeight()-ghand.y);
		w = ghand.pid->width + ghand.width;
		h = ghand.pid->height + ghand.height;
	}
	else
	{
		x = ghand.x;
		y = GetHeight()-ghand.y;
		w = ghand.width;
		h = -ghand.height;
	}
	pr = value * (w /100);

	// TODO : DUZELT BUNU
	// HATA : tick ve progress barin textureleri ve yeni progress bar kodu yaz
	Enter2D();
	glColor3ub(backclr.r,backclr.g,backclr.b);
	glBindTexture(GL_TEXTURE_2D, back);
	glTranslated(x,y,0);
	RenderPicture(0,0,w,h);
	glBindTexture(GL_TEXTURE_2D,0);
	glColor4f(barclr.r ,barclr.g ,barclr.b,0.5f);
	enTP();
	RenderPicture(0,0,pr,h);
	diTP();
	Exit2D();

}

GWindow::GWindow()
{
	backclr = m24b(128,128,128);
	barclr = m24b(0,0,128);
	caption = "";
	picture = 0;
	icon = 0;
	font = fontbase;
	ghand.x = 0;
	ghand.y = 0;
	ghand.width = 0;
	ghand.height = 0;
	ghand.visible = true;
	but.pressed = false;
	but.talign = false;
}

void GWindow::render()
{
	float x,y,w,h;
	float sx,sy,tx;
	x = ghand.x;
	y = GetHeight()-ghand.y;
	w = ghand.width;
	h = -ghand.height;

	Enter2D();

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3ub(backclr.r,backclr.g ,backclr.b);
	glTranslated(x,y,0);
	RenderPicture(0,0,w,h);
	//glColor3ub( barclr.r, barclr.g , barclr.b );
	//RenderPicture(3,h -12 , w-5 ,10);

	glColor3f(1 , 1 , 1 );
	glBegin(GL_LINES);
		glVertex2f(w,0); glVertex2f(w,h);
		glVertex2f(0,0); glVertex2f(w,0);
		glVertex2f(0,0); glVertex2f(0,h);
		glVertex2f(0,h); glVertex2f(w,h);
	glEnd();

Exit2D();

	CHandle(&but.ghand,2,2,w-3,12,true,&ghand);
	but.caption = caption;
	but.backclr = m24b(200,200,200);
	but.render();
	if (but.pressed)
	{

		sx = GetMouseX();
		sy = GetMouseY();
		ghand.x =ssx+(sx-msx);

		ghand.y =GetHeight()-ssy + (sy-msy);
		ghand.width = w;
		ghand.height = -h;

		//CHandle(&ghand,sx,sy,w,-h,true,0);

	}
	else
	{
		ssx = x;
		ssy = y;
		msx = GetMouseX();
		msy = GetMouseY();
	}

	//glColor3f(1 , 0 , 0 );
//	glRasterPos2f( (w / 2)-(sizeof(caption)*6), h-11 );
  //  PrintText(font, caption);

	Exit2D();
}


GLabel::GLabel()
{
	caption = new char [250];
	strcpy(caption,"\0");
	textclr = m24b(0,0,0);
	ghand.x = 0;
	ghand.y = 0;
	ghand.width = 0;
	ghand.height = 0;
	ghand.visible = true;
	border = false;
	ghand.pid=0;
	font = -1;
}

void GLabel::render()
{
	float x,y,w,h;
	if (ghand.pid != 0)
	{
		x = ghand.pid->x + ghand.x;
		y = GetHeight()- (ghand.pid->y + ghand.y);
		w = ghand.width;
		h = -ghand.height;
	}
	else
	{
		x = ghand.x;
		y =GetHeight()-ghand.y;
		w = ghand.width;
		h = -ghand.height;
	}

	if (font == -1)
	{
		font = fontbase;
	}
	if (font == -2)
	{
		font = smallfont;
	}
	Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3ub(textclr.r,textclr.g ,textclr.b);
	glTranslated(x,h+y,0);
	glRasterPos2f( 2, 5 );
    PrintText(font, caption);
	//x = x + (6*sizeof(caption));
	if (border)
	{
	glBegin(GL_LINES);
		glVertex2f(w,0); glVertex2f(w,h);
		glVertex2f(0,0); glVertex2f(w,0);
		glVertex2f(0,0); glVertex2f(0,h);
		glVertex2f(0,h); glVertex2f(w,h);
	glEnd();
	};

	Exit2D();
}


GTextbox::GTextbox()
{
	text = "";
	textclr = m24b(1,1,1);
	backclr = m24b(0,0,0);
	text = new char [100];
//	font = -1;
	ghand.x = 0;
	ghand.y = 0;
	ghand.width = 0;
	ghand.height = 0;
	ghand.visible = true;
	ghand.pid=0;
}

void GTextbox::render()
{
	float x,y,w,h;
	if (ghand.pid != 0)
	{
		x = ghand.pid->x + ghand.x;
		y = GetHeight()- (ghand.pid->y + ghand.y);
		w = ghand.width;
		h = -ghand.height;
	}
	else
	{
		x = ghand.x;
		y =GetHeight()-ghand.y;
		w = ghand.width;
		h = -ghand.height;
	}
	Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3ub(textclr.r,textclr.g ,textclr.b);
	glTranslated(x,y,0);
	glRasterPos2f( 2, 5 );
    PrintText(fontbase, text);

	glBegin(GL_LINES);
		glVertex2f(w,0); glVertex2f(w,h);
		glVertex2f(0,0); glVertex2f(w,0);
		glVertex2f(0,0); glVertex2f(0,h);
		glVertex2f(0,h); glVertex2f(w,h);
	glEnd();
	y = y + h;
	if (GetMouseX() > x && GetMouseX() < x + w && GetHeight()-GetMouseY() < y+ (-h)  && GetHeight()-GetMouseY() > y )
	{
		glColor4f(0 ,0.3f ,0.3f,0.5f);
		enTP();
		RenderPicture(0,0,w,h);
		diTP();

			/*for (int i =0;i<255;i++)
			{
					if (IsKeyPress(i) == true )
					{
					sprintf(text,"%i",i);
						//strcat(text,(char*)&i);
					SetKeyPress(i,false);
					}

			}*/


	};

	Exit2D();
	
}