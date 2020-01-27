#include <string.h>
#include <math.h>
#include "cgui.h"

unsigned int fontbase;
unsigned int smallfont;
unsigned int gcb1,gcb2;
unsigned int curtex;

char* clin[15];
char temp[100];

GLabel lines;
GLabel contex;
int lace=0;
bool cshow=true;
char b;

void GCTex(unsigned int t1){ curtex = t1; }

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

void GCBox(unsigned int t1,unsigned int t2)
{
	gcb1 = t1; gcb2 = t2;
}
void GConsole()
{

GBackGrd(0,0,GetWidth(),-13*15);
lines.textcolor.r = 1;lines.textcolor.g = 1;lines.textcolor.b = 1;
contex.textcolor.r = 1;contex.textcolor.g = 1;contex.textcolor.b = 1;
  
	for (int i = 0;i<15;i++)
	{
		lines.caption = clin[i];
		lines.render(0,i*13,13,GetWidth());
	}
	contex.render( 0,195,13,GetWidth());

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
/*
class GSlider
{
private:
	int sx;
public:
	GSlider();
	int value;
	int min,max;
	void render(float x,float y,float width,float height);
}*/
GSlider::GSlider()
{
	min = 0;
	max = 100;
	sx = 0;
	mx = 0;
	value = 0;
	myslide.pressed = false;
	myslide.isslider = true;
	lc = GetTickCount();
}

void GSlider::render(float x,float y,float width,float height)
{
	y = GetHeight() - y;
	Enter2D();
	glBindTexture(GL_TEXTURE_2D,0);
	glTranslated(x,y,0);
	float maz;
	maz = height / 2;

	glColor3f(0.7f,0.7f,0.7f);
	RenderPicture( 0,maz,width,2);

	glColor3f(0.5f , 0.5f , 0.5f );
	glBegin(GL_LINES);
		glVertex2f(0,maz); glVertex2f(0,maz+2);
		glVertex2f(0,maz+2); glVertex2f(width,maz+2);
	glEnd();
	glColor3f(1.0f , 1.0f , 1.0f );
	glBegin(GL_LINES);
		glVertex2f(width,maz); glVertex2f(width,maz+2);
		glVertex2f(0,maz); glVertex2f(width,maz);
	glEnd();

	if (sx == 0) {sx = x+width/2;value = (int)( (((sx - x)*(max-min))/width) - ((max-min)/2) );}
	if ( myslide.pressed)
	{
		sx = (float)GetMouseX();
		if ( sx > x + width )
		{
			sx = x + width;
		}
		if (sx < x)
		{
			sx = x;
		}
		value = (int)( (((sx - x)*(max-min))/width) - ((max-min)/2) );
		myslide.pressed = false;
	}

	Exit2D();

	sprintf(myslide.Caption,"      %i",value);
	myslide.render(sx-5,GetHeight() - y,height,10); 
}


GCheckBox::GCheckBox()
{
	value = false;
	caption = "";
	style = 0;
}

void GCheckBox::render(float x,float y)
{
	y = GetHeight() - y;
	Enter2D();
	glBindTexture(GL_TEXTURE_2D,0);
	glTranslated(x,y,0);
	if (style == 0)
	{
	glColor3f(0.0f,0.2f,0.0f);
	glBegin(GL_LINES);
		glVertex2f(0,0); glVertex2f(0,13);
		glVertex2f(0,13); glVertex2f(13,13);
		glVertex2f(13,0); glVertex2f(13,14);
		glVertex2f(0,0); glVertex2f(13,0);
	glEnd();
	}
	if( style == 1)
	{
	glColor3f(0.9f,0.9f,0.9f);
	RenderPicture(0,0,13,13);
	glColor3f(0.5f,0.5f,0.5f);
	glBegin(GL_LINES);
		glVertex2f(0,0); glVertex2f(0,13);
		glVertex2f(0,13); glVertex2f(13,13);
	glEnd();
	
	glColor3f(0.25f,0.25f,0.25f);
	glBegin(GL_LINES);
		glVertex2f(1,1); glVertex2f(1,12);
		glVertex2f(1,12); glVertex2f(12,12);
	glEnd();

	glColor3f(0.82f, 0.81f , 0.78f);
	glBegin(GL_LINES);
		glVertex2f(12,1); glVertex2f(12,12);
		glVertex2f(1,1); glVertex2f(12,1);
	glEnd();	
	
	glColor3f(1.0f, 1.0f , 1.0f);
	glBegin(GL_LINES);
		glVertex2f(13,0); glVertex2f(13,14);
		glVertex2f(0,0); glVertex2f(13,0);
	glEnd();
	}
	if (style == 3)
	{
		glBindTexture(GL_TEXTURE_2D, gcb1);
		RenderPicture(0,0,13,13);
	}
	
	y = y + 16;

	if (GetMouseX() > x && GetMouseX() < x + 13 && GetMouseY() > GetHeight() - y && GetMouseY() < (GetHeight() - y) + 13 )
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

		//isover = true;
	}
	else
	{
		//isover = false;
	};

	if (value )
	{

		if (style == 0)
		{
		glBegin(GL_LINES);		
		glColor3f(1, 1 ,1);
			glVertex2f(0,0);glVertex2f(12,12);
			glVertex2f(0,12);glVertex2f(12,0);
		glEnd();
		}
		if(style == 1)
		{
		glBegin(GL_LINES);
		glColor3f(0, 0 ,0);
			glVertex2f(3,7); glVertex2f(6,4);
			glVertex2f(6,4); glVertex2f(10,10);
		glEnd();
		}
		

		if (style == 3)
		{
			glBindTexture(GL_TEXTURE_2D, gcb2);
			RenderPicture(0,0,13,13);
		}
		
	};
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f(0.8f,0.8f,0.8f,1);
	glRasterPos2f(4*sizeof(caption)+3,13/2-3);
	PrintText(fontbase,caption);


//	if (!GetMouseClick(0)) pressed=false;
	Exit2D();
	//glColor4f(0,0,0,1);
}

void GButton::render(float x,float y,float height,float width)
{
	Enter2D();
	y = GetHeight() - y;
//	x = x1;y = y1;height = heig;width = wid;
	//y = GetHeight() - y;
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(BackColor.r , BackColor.g , BackColor.b );
	glTranslated(x,y,0);
	RenderPicture(0,0,width,height);
	glColor3f(0.5f , 0.5f , 0.5f );
	glBegin(GL_LINES);
		glVertex2f(width,0); glVertex2f(width,height);
		glVertex2f(0,0); glVertex2f(width,0);
	glEnd();
	glColor3f(1.0f , 1.0f , 1.0f );
	glBegin(GL_LINES);
		glVertex2f(0,0); glVertex2f(0,height);
		glVertex2f(0,height); glVertex2f(width,height);
	glEnd();

	glColor3f(0 , 0 , 0 );
	glRasterPos2f(width/2-(4*sizeof(Caption)),height/2-(2));
	if (isslider == true ){PrintText(smallfont, Caption);}else{PrintText(fontbase, Caption);} ;


	y = y + height;
	if (GetMouseX() > x && GetMouseX() < x + width && GetMouseY() > GetHeight() - y && GetMouseY() < (GetHeight() - y) + height )
	{
		glColor4f(0 ,0 ,0.8f,0.5f);
		enTP();
		RenderPicture(0,0,width,height);
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

//if (!GetMouseClick(0)) pressed=false;

	Exit2D();
}

bool GButton::ispressed()
{

	if(protection==true) SetMouseClick(0,false);
	return pressed;
}

GProgressBar::GProgressBar()
{
	percent = 0;
	BarColor.r = 0.0f;
	BarColor.g = 0.0f;
	BarColor.b = 0.6f;
	BackColor.r = 1.0f;
	BackColor.g = 1.0f;
	BackColor.b = 1.0f;
};

void GProgressBar::render(float x,float y,float height,float width)
{
	float pr;
	if (percent > 100) percent = 100;
	if (percent < 0) percent = 0;
//	y = (GetHeight()/2) - (y/2);
//	x = (x/2);
	y = GetHeight() - y;
	pr = percent * (width / 100 );
	Enter2D();
	glColor3f(BackColor.r,BackColor.g,BackColor.b);
	glBindTexture(GL_TEXTURE_2D, texture.ID);
	glTranslated(x,y,0);
	RenderPicture(0,0,width,height);
	glBindTexture(GL_TEXTURE_2D,0);
	glColor4f(BarColor.r ,BarColor.g ,BarColor.b,0.5f);
	enTP();
	RenderPicture(0,0,pr,height);
	diTP();
	Exit2D();

};

GButton::GButton()
{
	//Caption = new char [256];
	Caption = "";
	BackColor.r = 0.8f;
	BackColor.g = 0.8f;
	BackColor.b = 0.8f;
	pressed = false;
	protection=true;
	fontbase = GetDefFont();
	isslider = false;
}



GFrame::GFrame()
{
	BackColor.r = 0.7f;
	BackColor.g = 0.7f;
	BackColor.b = 0.7f;
}

void GFrame::render(float x, float y,float height,float width)
{
	Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(BackColor.r , BackColor.g , BackColor.b );
	glTranslated(x,y,0);
	RenderPicture(0,0,width,height);
	glColor3f(1 , 1 , 1 );
	glBegin(GL_LINES);
		glVertex2f(width,0); glVertex2f(width,height);
		glVertex2f(0,0); glVertex2f(width,0);
		glVertex2f(0,0); glVertex2f(0,height);
		glVertex2f(0,height); glVertex2f(width,height);
	glEnd();
	Exit2D();


};

GWindow::GWindow()
{
	BackColor.r = 0.5f;
	BackColor.g = 0.5f;
	BackColor.b = 0.5f;
	BarColor.r = 0;
	BarColor.g = 0;
	BarColor.b = 0.5f;
	caption = "";
	fontbase = GetDefFont();
}

void GWindow::render(float x, float y,float height , float width)
{
	Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(BackColor.r,BackColor.g ,BackColor.b);
	glTranslated(x,y,0);
	RenderPicture(0,0,width,height);
	glColor3f( BarColor.r, BarColor.g , BarColor.b );
	RenderPicture(3,height -12 , width-5 ,10);
	glColor3f(1 , 1 , 1 );
	glBegin(GL_LINES);
		glVertex2f(width,0); glVertex2f(width,height);
		glVertex2f(0,0); glVertex2f(width,0);
		glVertex2f(0,0); glVertex2f(0,height);
		glVertex2f(0,height); glVertex2f(width,height);
	glEnd();

	//glColor3f(1 , 0 , 0 );
	glRasterPos2f( (width / 2)-(sizeof(caption)*6), height-11 );
    PrintText(fontbase, caption);

	Exit2D();
}

void GDefFont (unsigned int font)
{
	fontbase = font;
}

void GSmaFont (unsigned int font)
{
	smallfont = font;
}

GLabel::GLabel()
{
	caption = new char [250];
	strcpy(caption,"\0");
	textcolor.r = 0;textcolor.g = 0;textcolor.b = 0;

};

void GLabel::render(float x,float y, float height,float width,bool border)
{
	y = GetHeight() - y;
	Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(textcolor.r,textcolor.g ,textcolor.b);
	glTranslated(x,y,0);
	glRasterPos2f( 2, 5 );
    PrintText(fontbase, caption);
	//x = x + (6*sizeof(caption));
	if (border)
	{
	glBegin(GL_LINES);
		glVertex2f(width,0); glVertex2f(width,height);
		glVertex2f(0,0); glVertex2f(width,0);
		glVertex2f(0,0); glVertex2f(0,height);
		glVertex2f(0,height); glVertex2f(width,height);
	glEnd();
	};

	Exit2D();
};

GTextBox::GTextBox()
{
	text = "";
	textcolor.r = 1;textcolor.g = 1;textcolor.b = 1;
	text = new char [100];

};

void GTextBox::render(float x ,float y,float height,float width)
{
	y = GetHeight() -y;
	Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(textcolor.r,textcolor.g ,textcolor.b);
	glTranslated(x,y,0);
	glRasterPos2f( 2, 5 );
    PrintText(fontbase, text);

	glBegin(GL_LINES);
		glVertex2f(width,0); glVertex2f(width,height);
		glVertex2f(0,0); glVertex2f(width,0);
		glVertex2f(0,0); glVertex2f(0,height);
		glVertex2f(0,height); glVertex2f(width,height);
	glEnd();
	y = y + height;
	if (GetMouseX() > x && GetMouseX() < x + width && GetMouseY() > GetHeight() - y && GetMouseY() < (GetHeight() - y) + height )
	{
		glColor4f(0 ,0.3f ,0.3f,0.5f);
		enTP();
		RenderPicture(0,0,width,height);
		diTP();

			/*for (i =0;i<255;i++)
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
};

GPB::GPB()
{
	percent = 0;
/*	BorderColor.r = 0.2;
	BorderColor.g = 0.2f;
	BorderColor.b = 0.0*/
	ProgressColor.r = 0;
	ProgressColor.g = 0.5;
	ProgressColor.b = 0.5;
};

void GPB::render(float x, float y,float height,float width)
{
	float pr;
	char*a;
	if (percent > 100) percent = 100;
	if (percent < 0) percent = 0;
//	y = (GetHeight()/2) - (y/2);
//	x = (x/2);
	y = GetHeight() - y;
	pr = percent * (width / 100 );
	Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glTranslated(x,y,0);
	glColor4f(ProgressColor.r ,ProgressColor.g ,ProgressColor.b,0.5f);
	enTP();
	RenderPicture(0,0,pr,height);
	diTP();
	
	glColor3f(0.2f , 0.2f , 0.2f );
	glBegin(GL_LINES);
		glVertex2f(0,0); glVertex2f(0,height);
		glVertex2f(0,height); glVertex2f(width,height);
	glEnd();

	glColor3f(1.0f , 1.0f , 1.0f );
	glBegin(GL_LINES);
		glVertex2f(width,0); glVertex2f(width,height);
		glVertex2f(0,0); glVertex2f(width,0);
	glEnd();



/*	
	glBegin(GL_LINES);
		glVertex2f(width,0); glVertex2f(width,height);
		glVertex2f(0,0); glVertex2f(width,0);

		glVertex2f(0,0); glVertex2f(0,height);
		glVertex2f(0,height); glVertex2f(width,height);
	glEnd();*/
	glColor3f(0,0,0.6f);
	glRasterPos2f( (width/2) - (3*sizeof(percent)) , (height/2)-2 );
    a=new char [4];
	itoa(percent,a,10);
	strcat(a,"%");
	PrintText(fontbase, a);

	Exit2D();

};
/*void GButton::drawthem()
{
Enter2D();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1.0f , 1.0f , 1.0f );
	glRasterPos2f(50,50);
    PrintText(fontbase, Caption);
Exit2D();

}*/
