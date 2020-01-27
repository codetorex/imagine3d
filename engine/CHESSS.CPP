
#include "cvision.h"
#include "ctexture.h"
#include "ccamera.h"
#include "cphysics.h"
#include "cgui.h"
#include "array.h"
//#include "cmusic.h"
#include "cbillboard.h"

#include "cmodel.h"
#include "ceffect.h"
#include "cpak.h"
#include "cvector.h"

#include "cbitmap.h"

#include "chess.h"

//#include "cobject.cpp"
//#include "test.h"

#include <string.h>
#include <stdio.h>




void LoadData();
void InProgress(char* ho);

GLfloat		rtri;					
GLfloat		rquad;					


GLfloat		xrot;													

unsigned int texter;
CTexture tex1;
CTexture refr;
CTexture lod;
CCamera Camera;
CTexture Bos;
BOOL	loaded=false;
bool	teste=true;
CTexture inativa;
GLabel www;
GWindow frm;
GProgressBar loda;
bool oto=false;



IModel shw; // table

IModel pawn;
IModel queen;
IModel rook;
IModel knight;
IModel king;
IModel bishop;

unsigned int white;
unsigned int black;

char m[64];

	DWORD	curtime;
	DWORD	animtime;
	float	progress;
float k;
void DrawGUI();

GCheckBox mycb;
GCheckBox hitb;
GCheckBox ffly;
GCheckBox ana;
GSlider mys;
GButton gb;
GLabel haha;

GButton ta[64];
int lcc=0;
bool gcon;

bool a=false;
char sx,sy,dx,dy = 0;
void DrawGUI()
{
	glDisable(GL_LIGHTING);
GBackGrd(0,400,200,-200);
for (int y=0;y<8;y++)
{
	char test[256];
	for(int x=0;x<8;x++)
	{
		sprintf(test,"    %s",N(m[P(x,y)]));
		ta[P(x,y)].Caption = test;
		ta[P(x,y)].render( 10+(15*x),420+(15*(8-y)),14,14);

		sprintf(test,"sx: %i sy: %i dx:%i dy:%i",sx,sy,dx,dy);
		haha.caption = test;
		haha.render(10,580,15,50);
	}
}

for (int i=0;i<64;i++)
{
	if (ta[i].pressed)
	{
		sx = GX(i);
		sy = GY(i);
	}
	if (ta[i].pressed2)
	{
		dx = GX(i);
		dy = GY(i);
		if (IsValid(m,sx,sy,dx,dy))
		{
			m[P(dx,dy)] = m[P(sx,sy)];
			m[P(sx,sy)] = BOS;
			sx = dx;
			sy = dy;
		}
	}
}
gb.Caption = "Reset";
gb.render(10,560,15,50);
if (gb.pressed) Start(m);
/*mycb.style = 3;
mycb.caption = "Orginal Model";
mycb.render(10,420);
hitb.style = 3;
hitb.caption = "Fill";
hitb.render(10,440);
ffly.style = 3;
ffly.caption = "Wireframe";
ffly.render(10,460);
ana.style = 3;
ana.caption = "Animation";
ana.render(10,480);
mys.min = -50;
mys.max = 50;
mys.render(10,500,80,10);
gb.Caption = "Take";
gb.render(10,520,15,50);*/

GCursor();
			glEnable(GL_LIGHTING);

}

float tx,ty;
float rs=2;
GLfloat diffuse_light2[4];
int lcas=0;
int pa=0;
int DrawGLScene(GLvoid)									
{
	if (teste)
	{
		//if ((GetTickCount() - curtime)> 5000) teste=false;
		if (loda.percent == 100) teste=false;
		progress = (float)((GetTickCount() - curtime) * 0.001);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glLoadIdentity();

		Enter2D();
		glTranslated(0,600,0);
		glBindTexture(GL_TEXTURE_2D, tex1.ID );
		RenderPicture(0,0,800,-600);
		Exit2D(); 
		glLoadIdentity();
		www.caption = "textures/1.bmp";
		www.render (260,445,14,299,false);
		loda.render(260,400,-30,300);

		glBindTexture(GL_TEXTURE_2D, 0 );
		glColor3f(1,1,1);
		//GConsole();
		
		if ((!loaded))
		{
				LoadData();
		};
		
	}else
	{
		if(!IsKeyPress(VK_TAB)) Camera.GetInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glLoadIdentity();								
		glEnable(GL_TEXTURE_2D);
		
		Camera.render();


		glBindTexture(GL_TEXTURE_2D, 0);

			diffuse_light2[0] = rs;
			diffuse_light2[1] = rs;
			diffuse_light2[2] = rs;
			diffuse_light2[3] = 1;
			GLfloat position_light2[] = { -0.122f , 3.736f , 0.118f  , 1.0f };
			GLfloat linearAttenuation_light2[] = { 0.02f };
			glLightfv( GL_LIGHT2, GL_DIFFUSE, diffuse_light2 );
			glLightfv( GL_LIGHT2, GL_POSITION, position_light2 );
			glLightfv( GL_LIGHT2, GL_LINEAR_ATTENUATION , linearAttenuation_light2 );
			glLightfv( GL_LIGHT2, GL_QUADRATIC_ATTENUATION , linearAttenuation_light2 );
			glEnable(GL_LIGHT2);


			glEnable(GL_LIGHTING);
			if (hitb.value)
			{
					shw.Render();
			vector3f laz,laz2,laz3;
			laz.set(Camera.xView,Camera.yView,Camera.zView);
			laz2.set(Camera.xPos,Camera.yPos,Camera.zPos);
			laz3 = eline (laz2,laz,3);
			glBegin (GL_TRIANGLES);
			glColor3f(1,1,1);
				glVector3f(laz3);
				glVector3f(laz2);
				glVector3f(laz);

			glEnd();

					for (int y=0;y<8;y++)
					{
						for(int x=0;x<8;x++)
						{
							tx = -2.9f + (x*0.85f);
							ty = 3-(y*0.85f);
							
							switch (m[P(x,y)])
							{
							case BPIYON:
								pawn.TextureCache[0].ID = white;
								pawn.CopyRender(mv3f(tx,0,ty));
								break;
							case SPIYON:
								pawn.TextureCache[0].ID = black;
								pawn.CopyRender(mv3f(tx,0,ty));
								break;
							case BAT:
								knight.TextureCache[0].ID = white;
								knight.CopyRender(mv3f(tx,0,ty));
								break;
							case SAT:
								knight.TextureCache[0].ID = black;
								knight.CopyRender(mv3f(tx,0,ty));
								break;
							case BFIL:
								bishop.TextureCache[0].ID = white;
								bishop.CopyRender(mv3f(tx,0,ty));
								break;
							case SFIL:
								bishop.TextureCache[0].ID = black;
								bishop.CopyRender(mv3f(tx,0,ty));
								break;
							case BKALE:
								rook.TextureCache[0].ID = white;
								rook.CopyRender(mv3f(tx,0,ty));
								break;
							case SKALE:
								rook.TextureCache[0].ID = black;
								rook.CopyRender(mv3f(tx,0,ty));
								break;
							case SVEZIR:
								queen.TextureCache[0].ID = black;
								queen.CopyRender(mv3f(tx,0,ty));
								break;
							case BVEZIR:
								queen.TextureCache[0].ID = white;
								queen.CopyRender(mv3f(tx,0,ty));
								break;
							case BSAH:
								king.TextureCache[0].ID = white;
								king.CopyRender(mv3f(tx,0,ty));
								break;
							case SSAH:
								king.TextureCache[0].ID = black;
								king.CopyRender(mv3f(tx,0,ty));
								break;


							}
						}
					}
					//queen.Render();
					//queen.Wireframe();

			}
		glLoadIdentity();			
		glDisable(GL_LIGHTING);
			char sz[100];
			
			sprintf(sz,"x: %g y: %g z: %g",Camera.xPos,Camera.yPos,Camera.zPos);
			www.caption = sz;
			www.render( 10,50,14,400,false);



			if(IsKeyPress(VK_TAB)) {DrawGUI();}
			if (gcon) { GConsole(); }
			if(IsKeyPress(192))
			{
				if (GetTickCount() -lcc > 100)
				{
					gcon = !gcon;
					lcc = GetTickCount();
				};
			};
		
			

		if(IsKeyPress(VK_HOME))
		{
			if (oto) {oto = false;} else {oto = true;}	
		};
		if(IsKeyPress(VK_LEFT))  xrot+=3;
		if(IsKeyPress(VK_RIGHT)) xrot-=3;
	}
		
		DrawFPS(texter);
		DrawedFrame();
		glColor3f(1.0f, 1.0f, 1.0f);

	return TRUE;			
}

 
int WINAPI WinMain(	HINSTANCE	hInstance,			
					HINSTANCE	hPrevInstance,	
					LPSTR		lpCmdLine,			
					int			nCmdShow)	
{
	MSG		msg;								
	BOOL	done=FALSE;

	if (!CreateGLWindow("Imagine 3D",800,600,16,true))
	{
		return 0;							
	}	
		CTexture cb1,cb2,cte1;

	xrot = 0;
	texter = CreateFont ("Tahoma",12);
	loda.percent = 20;


	www.textcolor.r = 1;www.textcolor.g = 1;www.textcolor.b = 1;  
	curtime = GetTickCount();
	glEnable(GL_TEXTURE_2D);
	GDefFont(texter);
	GSmaFont(CreateFont ("Arial",10));

	lcc = GetTickCount();
	IBitmap bayrak,guim;
	bayrak.createbitmap(192,128);
	bayrak.turkbayragi();
	bayrak.gettexid();
	//guim.createbitmap(32,32);
	//guim.gettexid(true);
	tex1.ID = bayrak.ID;

	loda.texture.LoadBMPFile( "loading.bmp");
	cte1.LoadBMPFileCK("gui/arrow.bmp",0,0,255,0);

	cb1.LoadBMPFile("gui/c1.bmp");
	cb2.LoadBMPFile("gui/c2.bmp");
	hitb.value = true;
	mycb.value = true;

	GCBox(cb1.ID,cb2.ID);
	GCTex(cte1.ID);

	GSCur(true);
	GCInit();

    Camera.SetCamera( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    ShowCursor(false);
	while(!done)								
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)			
			{
				done=TRUE;							
			}
			else								
			{
				TranslateMessage(&msg);			
				DispatchMessage(&msg);			
			}
		}
		else									
		{
			if (GetActive())						
			{
				if (IsKeyPress(VK_ESCAPE))			
				{
					done=TRUE;					
				}
				else					
				{

					DrawGLScene();					
					SwapBuffers(GethDC());		

				}
			}
		}
	}

	//stopmusic();
	KillGLWindow();				
	return (msg.wParam);		
}

void LoadData()
{
	InProgress("tree.im3");
	shw.LoadScale.set(0.05f,0.05f,0.05f);
	shw.LoadIM3("chess/board.im3",0);
	shw.LoadTexturesA();
	IBitmap pro1,pro2;

	Start(m);

	pawn.LoadScale.set(0.05f,0.05f,0.05f);
	queen.LoadScale.set(0.05f,0.05f,0.05f);
	rook.LoadScale.set(0.05f,0.05f,0.05f);
	knight.LoadScale.set(0.05f,0.05f,0.05f);
	king.LoadScale.set(0.05f,0.05f,0.05f);
	bishop.LoadScale.set(0.05f,0.05f,0.05f);

	pawn.LoadIM3("chess/pawn.im3",0);
	queen.LoadIM3("chess/queen.im3",0);
	rook.LoadIM3("chess/rook.im3",0);
	knight.LoadIM3("chess/knight.im3",0);
	king.LoadIM3("chess/king.im3",0);
	bishop.LoadIM3("chess/bishop.im3",0);


//	shw.PrepareTexture(2);
	//IBitmap loa;

	//loa.createbitmap(256,256);
//	pro1.createbitmap(192,128);
	pro1.createbitmap(128,128);
	pro2.createbitmap(128,128);


	//pro1.loadpal("pal.raw");
	pro1.pnoise(GetTickCount()/4000.0f,4);
	pro2.pnoise(GetTickCount()/4000.0f,16);
	pro1.blend(pro2);
	pro2.pnoise(GetTickCount()/4000.0f,8);
	pro1.blend(pro2);
	pro2.pnoise(GetTickCount()/4000.0f,32);
	pro1.blend(pro2);
//	pro2.pnoise(GetTickCount()/4000.0f,64);
	pro1.blend(pro2);


	//pro1.loadpal("pal.raw");
	//pro1.recolor();

	pro1.gettexid();
	white = pro1.ID;

	pro2.fillall(m24b(50,50,50));
	pro2.blend(pro1);
	pro2.gettexid();
	black = pro2.ID;

white = shw.TextureCache[0].ID;
black = shw.TextureCache[1].ID;
//	shw.TextureCache[0].ID = white;
//	shw.TextureCache[1].ID = black;


/*	pawn.TextureCache[0].ID = pro1.ID;
	queen.TextureCache[0].ID = pro1.ID;
	rook.TextureCache[0].ID = pro1.ID;
	knight.TextureCache[0].ID = pro1.ID;
	king.TextureCache[0].ID = pro1.ID;
	bishop.TextureCache[0].ID = pro1.ID;*/

	//pro1.drawstar(256,256,128,5,m24b(255,255,255),true);
	//pro1.drawcirc(256,256,128,m24b(255,255,255),false);

	//pro1.turkbayragi();

	//pro2.loadpal("pal.raw");
	//pro2.pnoise(GetTickCount()/4000.0f,16);
	//pro1.loadbmp("8.bmp");
	//pro1.deneme();
	/*pro1.pnoise(GetTickCount()/4000.0f,4);
//	loa.pal = pro1.pal; 
	//loa.loadpal("pal.raw");
	//loa.pnoise(GetTickCount()/4000.0f,8);
	pro2.pnoise(GetTickCount()/4000.0f,8);
	pro1.blend(pro2);
	pro2.pnoise(GetTickCount()/4000.0f,16);
	pro1.blend(pro2);
	pro2.pnoise(GetTickCount()/4000.0f,32);
	pro1.blend(pro2);
	pro2.sinplasma(256,3);
	pro1.blend(pro2);
	
	pro1.loadpal("pal.raw");
	pro1.recolor();*/




	//pro1.addive(loa);
	//loa.pnoise(GetTickCount()/4000.0f,16);
	//pro1.addive(loa);
	//loa.randompal();
	//pro1.randompal();
	//loa.cellular(20,mono(255),3,true);
	//pro1.cellular(20,mono(255),0,false);
	//pro1.addive(loa);

	//pro1.sinplasma(256,10);
	//pro1.blur();
	//pro1.emboss();

	//loa.cellular(20,mono(255),0,false);
	//pro1.addive(loa);
	//pro1.emboss();
	
	//pro1.emboss();
	//pro1.writebmp("c://dens.bmp");

	/*pro1.centergradient(120);
	pro1.emboss();*/

	//pro2.cellular(20,m24b(214,255,255),0,true);
	//pro2.edged();

//	pro1.gettexid();
//	pro2.gettexid();

//	shw.TextureCache[0].ID = tex1.ID;
//	shw.TextureCache[1].ID = pro1.ID;

	



	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );   
	GLfloat ambient_lightModel[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_lightModel );

	loda.percent = 100;
	loaded = true;
};

void InProgress(char* ho)
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glLoadIdentity();

		Enter2D();
		glTranslated(0,600,0);
		glBindTexture(GL_TEXTURE_2D, tex1.ID );
		RenderPicture(0,0,800,-600);
		Exit2D(); 
		www.caption = ho;
		www.render (260,445,14,299,false);
		loda.percent++;
		loda.render(260,400,-30,300);

		DrawFPS(texter);
		DrawedFrame();
		glColor3f(1.0f, 1.0f, 1.0f);
		SwapBuffers(GethDC());
}