

#include "cvision.h"
#include "ctexture.h"
#include "ccamera.h"
#include "cphysics.h"
#include "gui.h"
#include "array.h"
#include "stack.h"
//#include "cmusic.h"
#include "cbillboard.h"

#include "cmodel.h"
#include "ceffect.h"
#include "cpak.h"
#include "cvector.h"

#include "cbitmap.h"

//#include "chess.h"
#include "resource.h"

#include "psprite.h"
//#include "cobject.cpp"
//#include "test.h"

#include <string.h>
#include <stdio.h>
#include "gl_arb_multitexture.h"
#include "gl_arb_vertex_program.h"

#include "parallax.h"
#include "mdlmodel.h"
#include "tileeditor.h"
#include "cobject.h"

CBBoard bor;
TMDLModel mds;

IModel envs;

IModel box;
ITile terra;
CTexture chrom;

void LoadData();
void InProgress(char* ho);

GLfloat		rtri;					
GLfloat		rquad;					


GLfloat		xrot;													

CTexture tex1;
CTexture refr;
CTexture lod;
CCamera Camera;
CTexture Bos;
BOOL	loaded=false;
bool	teste=true;
CTexture inativa;

bool oto=false;


//IModel tree;
//IModel scen;
//IModel amele;

IModel shw;
//STest shw;

//SModel super;
//SModel sup2;

char m[64]; // satranc masasi

IBitmap pro1,pro2;

//FModel inser;

char proje[60];


	DWORD	curtime;
	DWORD	animtime;
	float	progress;
float k;
void DrawGUI();
void InitGUI();

CPak datt;

PSprite ssys;
CBBoard lig;

int grad,lamp;
plxmap plxtest;
//CBBoard bbs;

int lcc=0;
bool gcon;
GWindow mwin;
GButton but;
GButton but2;
GSlider sli;
GLabel	nlb;
GCheckBox gcb;
GTextbox gtb;
GLabel	frps;


// Texture Browser
GWindow TBrowser;
GSlider	TBSlid;
GTexture TBTex;

void DrawGUI()
{

	mwin.caption = "burak";
	mwin.render();
	but2.caption = "SS";
	but2.render();
	nlb.caption = "burak";
	nlb.render();
	sli.min = -50;
	sli.max = 50;
	sli.render();
	gcb.caption = "burak";
	gcb.render();
	gtb.render();

TBrowser.caption = "Texture Browser";
TBrowser.render();

TBSlid.min = 0;
TBSlid.max = 25;
TileEditor::RunTileEditor();
TBTex.texid = TBSlid.value;
TBSlid.render();
TBTex.render();
TileEditor::RunTileEditor();
	//GConsole();
	GCursor();
}
	CTexture cb1;
float xr,yr,zr;
void InitGUI()
{
	GCInit();
	static unsigned int t1,t2,t3;
	mds.Init("v_deagle_r.mdl");
	mds.SetSequence(0);
	
	cb1.LoadBMPFile("gui/c1.bmp");
	t1 = cb1.ID;
	cb1.LoadBMPFile("gui/c2.bmp");
	t2 = cb1.ID;
	cb1.LoadBMPFileCK("gui/arrow.bmp",0,0,255);
	//cb1.LoadBMPFile("gui/arrow.bmp");
	t3 = cb1.ID;

	StartGUI( CreateFont ("Lucida Console",10),CreateFont("Arial",10),t1,t2,t3);
	GSCur(true);
	CHandle(&frps.ghand,5,5,100,15,true,0);
	frps.textclr = m24b(255,255,255);
	CHandle(&mwin.ghand,100,100,100,100,true,0);
	CHandle(&but2.ghand,4,20,50,12,true,&mwin.ghand);
	CHandle(&sli.ghand,5,34,90,10,true,&mwin.ghand);
	CHandle(&nlb.ghand,5,48,90,10,true,&mwin.ghand);
	CHandle(&gcb.ghand,5,68,90,10,true,&mwin.ghand);
	CHandle(&gtb.ghand,5,75,90,15,true,&mwin.ghand);
	
	CHandle(&TBrowser.ghand,10,10,137,165,true,0);
	CHandle(&TBSlid.ghand,5,20,120,10,true,&TBrowser.ghand);
	CHandle(&TBTex.ghand,5,32,128,128,true,&TBrowser.ghand);


	TileEditor::InitTileEditor();

	GCAdd("Gui Initialized.");
	ssys.InitExtension();
	ssys.maxsize = 10;
	bor.autogetcampos = true;
	xr = -1;yr = 0.5f; zr = 1;


}
					float angs;
float rs=2;
GLfloat diffuse_light2[4];
int lcas=0;
int pa=0;

int DrawGLScene(GLvoid)									
{

	if (teste)
	{
		//if ((GetTickCount() - curtime)> 5000) teste=false;
//		if (loda.percent == 100) teste=false;
		teste= false;
		progress = (float)((GetTickCount() - curtime) * 0.001);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glLoadIdentity();

		Enter2D();
		glTranslated(0,600,0);
		glBindTexture(GL_TEXTURE_2D, tex1.ID );
		RenderPicture(0,0,800,-600);
		Exit2D(); 
		glLoadIdentity();
//		www.caption = "textures/1.bmp";
//		www.render (260,445,14,299,false);
//		loda.render(260,400,-30,300);

		glBindTexture(GL_TEXTURE_2D, 0 );
		glColor3f(1,1,1);
		//GConsole();
		
		if ((!loaded))
		{
				LoadData();
		};
		
	}else
	{//&& GetMouseClick(0) == true
		if(!IsKeyPress(VK_TAB) ) Camera.GetInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glLoadIdentity();								
		glEnable(GL_TEXTURE_2D);
		//if(!ffly.value) Camera.vEye.y = mys.value * 0.1f;

		
		Camera.render();


		//glShadeModel(GL_FLAT);
		glBindTexture(GL_TEXTURE_2D, 0);
/*			if (GetTickCount() - lcas > 10)
			{
				rs = 0;
				rs = ((rand()%29) +1) / ((rand()%99)+1);
				rs += 0.6f;
				mys.value = rs * 10;
				lcas = GetTickCount();
			}*/
			diffuse_light2[0] = rs;
			diffuse_light2[1] = rs;
			diffuse_light2[2] = rs;
			diffuse_light2[3] = 1;

			//GLfloat diffuse_light2[] = { rs, rs, rs, 1.0f };
			//mys.value = rs * 10;
			//GLfloat position_light2[] = {envs.IM3Lights[0].lmatrix[9]* 0.01f,envs.IM3Lights[0].lmatrix[11] * 0.01f,-envs.IM3Lights[0].lmatrix[10]* 0.01f,1.0f };
			GLfloat position_light2[] = {Camera.xPos,Camera.yPos,Camera.zPos,1.0f };

			//GLfloat position_light2[] = {Camera.xPos,Camera.yPos,Camera.zPos,1.0f };
			GLfloat linearAttenuation_light2[] = { 0.02f };
			glLightfv( GL_LIGHT2, GL_DIFFUSE, diffuse_light2 );
			glLightfv( GL_LIGHT2, GL_POSITION, position_light2 );
			glLightfv( GL_LIGHT2, GL_LINEAR_ATTENUATION , linearAttenuation_light2 );
			glLightfv( GL_LIGHT2, GL_QUADRATIC_ATTENUATION , linearAttenuation_light2 );
		//glEnable( GL_LIGHT0 );
		//glEnable( GL_LIGHT1 );

/*
			
			int gen=10;
			int stepsize = 360/gen;
			float pi = 3.1415926535f;

			for (float i = 0;i<361;i+=stepsize)
			{
				glBegin(GL_POINTS);
					glVertex3f(sin((i/180)*pi),0,cos((i/180)*pi));
				glEnd();
				
				for(float j =i;j < 361;j+=stepsize)
				{
					glBegin(GL_LINES);
						glVertex3f(sin((i/180)*pi),0,cos((i/180)*pi));
						glVertex3f(sin((j/180)*pi),0,cos((j/180)*pi));
					glEnd();
				}
			}*/
			

			/*
			glBegin(GL_POINTS);
				glVertex3f(1,1,1);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(0,0,0);glVertex3f(1,0,0);
				glVertex3f(0,0,0);glVertex3f(0,0,1);
				glVertex3f(0,0,1);glVertex3f(1,0,1);
				glVertex3f(1,0,1);glVertex3f(1,0,0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(1,1,1);glVertex3f(0,0,0);
				glVertex3f(1,1,1);glVertex3f(0,0,1);
				glVertex3f(1,1,1);glVertex3f(1,0,1);
				glVertex3f(1,1,1);glVertex3f(1,0,0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(0,0,0);glVertex3f((2*0)-1,(2*0)-1,(2*0)-1);
				glVertex3f(0,0,1);glVertex3f((2*0)-1,(2*0)-1,(2*1)-1);
				glVertex3f(1,0,1);glVertex3f((2*1)-1,(2*0)-1,(2*1)-1);
				glVertex3f(1,0,0);glVertex3f((2*1)-1,(2*0)-1,(2*0)-1);
			glEnd();*/
		


			/*glPushMatrix();
			
			
			glPopMatrix();*/

			//super.Render();
			//super.RenderA();
//			if (hitb.value)
//			{
	/*			if (ana.value)
				{
					super.RenderA();
				}
				else
				{*/
					//super.cf = mys.value;
					//shw.IM3Header.shadowface = false;

					//terra.Wireframe();

			glEnable( GL_LIGHT2 );
			glEnable( GL_LIGHTING );
					glColor3f(1,1,1);
				
					//terra.RenderTerrain();
					//terra.RenderFaces();
					//terra.Render();
					shw.BumpCache[0].light_pos.set(sin((xrot*3.14f)/180)*40,2,cos((xrot*3.14f)/180)*40);
					//shw.BumpCache[0].light_pos.set(200,2,200);
					//shw.Render();
					///hw.BumpCache[0].light_pos.set(shw.IM3Lights[0].lmatrix[9],-shw.IM3Lights[0].lmatrix[11],shw.IM3Lights[0].lmatrix[10]);
//					shw.BumpCache[0].Disable();
					glPushMatrix();
					glScalef(0.1f,0.1f,0.1f);
					glTranslatef(1,0,0);
					shw.Render();
					glPopMatrix();

					glColor3ub(128,255,128);
					lig.camPos = mv3f(Camera.xPos,Camera.yPos,Camera.zPos);
					lig.texid = lamp;
					//lig.render(mv3f(shw.IM3Lights[0].lmatrix[9]*0.05f,shw.IM3Lights[0].lmatrix[11]*0.05f,-shw.IM3Lights[0].lmatrix[10]*0.05f),0.2f);
					//lig.render(mv3f(sin((xrot*3.14f)/180)*4,2,cos((xrot*3.14f)/180)*4),0.5f);
					glEnable( GL_LIGHTING );
					glDisable( GL_LIGHTING );

					glPushMatrix();
					glPushAttrib(GL_TEXTURE_BIT);
					
					EnableSphereMap();
						glBindTexture(GL_TEXTURE_2D, chrom.ID);  // Bind the Texture to the object
						glScalef(0.01f,0.01f,0.008f);
						glScalef(2,2,2);
						glColor3ub(255,255,255);
						box.RenderFaces();
					glPopAttrib();

					glPopMatrix();

					//envs.Render();
					//envs.Wireframe();
			glDisable( GL_LIGHT2 );
			glDisable( GL_LIGHTING );

					
					ssys.StartSprite();
					glColor3ub(128,255,128);
					//shw.BumpCache[0].light_pos.set(Camera.xPos,Camera.yPos,Camera.zPos);
					ssys.maxsize = 5;
					glVector3f(shw.BumpCache[0].light_pos*0.1);
/*					for (int i=0;i<terra.IM3Mesh[0].vertcount;i++)
					{
						glVertex3f(terra.IM3Mesh[0].mx[i],terra.IM3Mesh[0].my[i],terra.IM3Mesh[0].mz[i]);
					}
*/
					ssys.EndSprite();
					glBegin(GL_LINES);
					for (int i=0;i<envs.tco;i++)
					{
						glVertex3f(envs.zx[i],envs.zy[i],envs.zz[i]);
						glVertex3f(envs.zx[i+1],envs.zy[i+1],envs.zz[i+1]);

					}
					glEnd();

					//terra.Wireframe();

			//terra.Wireframe();
					//terra.RenderFaces();

					/*glColor3ub(128,255,128);
					glBegin(GL_LINES);
						for (float x=-10;x<10;x+=0.5)
						{
							glVertex3f(x,0,-10);glVertex3f(x,0,10);
						}
						for (x=-10;x<10;x+=0.5)
						{
							glVertex3f(-10,0,x);glVertex3f(10,0,x);
						}
					glEnd();*/

					
					if (IsKeyPress('Y')) xr+=0.5f;
					if (IsKeyPress('U')) xr-=0.5f;

					if (IsKeyPress('H')) yr+=0.5f;
					if (IsKeyPress('J')) yr-=0.5f;

					if (IsKeyPress('N')) zr+=0.5f;
					if (IsKeyPress('M')) zr-=0.5f;


					glLoadIdentity();

					glPushMatrix();
						//bor.matrixset(mv3f(Camera.xView,Camera.yView,Camera.zView),mv3f(0,-1,0));
						//glTranslatef(Camera.xPos,Camera.yPos,Camera.zPos);
					glTranslatef(0,0,-0.6f);	
					glRotatef(-90,1,0,0);
					glRotatef(0,0,1,0);
					glRotatef(90,0,0,1);
						//glRotatef((angs*180)/3.14f,0,0,1);
						//glRotatef((Camera.zAxis*180)/3.14f,0,1,0);

						glScalef(0.07f,0.07f,0.07f);
						mds.DrawModel();
					glPopMatrix();

					//glDisable(GL_LIGHTING);
					//shw.Shadow2(Camera.xView  , Camera.yView  , Camera.zView);
					//glEnable( GL_LIGHTING );
					//shw.Shadow();
					//shw.Axis();
					//shw.Shadow();
				//}
//			}

/*			if(mycb.value)
			{
				sup2.Render();
			}*/

			//super.cf = mys.value;
			
			//super.RenderHitBox();
			//super.Axis();
			//scen.Axis();

//			if (ffly.value) super.Wireframe();
//			if (ffly.value) sup2.Wireframe();
			//amele.CopyRender(mv3f(Camera.xView,0,Camera.zView));
			//amele.Render();

			//tree.Render();
			/*tree.CopyRender(mv3f(-10.7f,-3,-17.8132f));
			tree.CopyRender(mv3f(2.26654f,-0.32f,-6.67297f));
			tree.CopyRender(mv3f(16.67f,-0.324f,-15.3708f));*/

//		env.Render(hitb.value);
		//glDisable( GL_LIGHTING );

		
/*	float n;
	k = k + 0.02f;
	n = sin(k)/20;
*/
				
//				bbs.render(mv3f(0,1,0));

		glLoadIdentity();			

			char sz[100];
			
			sprintf(sz,"x: %g y: %g z: %g",Camera.xPos,Camera.yPos,Camera.zPos);
//			www.caption = sz;
//			www.render( 10,50,14,400,false);

/*			pa ++;
			if (pa == 511) pa = 0;
			sprintf(sz,"p: %i",getp(pa));
			www.caption = sz;
			www.render( 10,70,14,400,false);*/
			
			/*
			sprintf(sz,"rx: %g ry: %g rz: %g",Camera.vRight.x,Camera.vRight.y,Camera.vRight.z);
			www.caption = sz;
			www.render( 10,60,14,400,false);*/

			/*sprintf(sz,"z: %g",Camera.vEye.z);
			www.caption = sz;
			www.render( 10,60,14,75,true);*/
			//if (mycb){a=1;}else{a=0;}
			//if (oto){b=1;}else{b=0;}
			//sprintf(sz,"t: %i o: %i",ok,oto);
			//www.caption = sz;
			//www.render( 10,495,14,75,true);


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
		
	
		if(IsKeyPress(VK_INSERT))
		{
			/*
			FILE* aa=0;
			aa = fopen("c://aa.txt","at");
			fprintf(aa,"(%ff,%ff,%ff)(%ff,%ff,%ff)\n",Camera.xPos,Camera.yPos,Camera.zPos,Camera.xView,Camera.yView,Camera.zView);
			fclose(aa);
		*/
		/*
			inser.AddL(MV(Camera.xView,Camera.yView,Camera.zView),xrot);
			*/
			
			
		//reco.Insert_Waypoint(Camera.xPos,Camera.yPos,Camera.zPos);
		}
		

		if(IsKeyPress(VK_HOME))
		{
			if (oto) {oto = false;} else {oto = true;}	
		};
		xrot+=1;
		//if(IsKeyPress(VK_LEFT))xrot+=0.1f;
		//if(IsKeyPress(VK_RIGHT)) xrot-=3;
	}
		
		sprintf(frps.caption,"FPS: %i x: %g y: %g z: %g xr: %g yr: %g zr: %g",GetFPS(),Camera.xPos,Camera.yPos,Camera.zPos,xr,yr,zr);
		frps.render();
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

	IBitmap sbitmap;

	/*sbitmap.createbitmap(512,512);
	sbitmap.cellular(5,m24b(255,255,255));
	sbitmap.writebmp("tuh.bmp");
	//sbitmap.loadbmp("test-s.bmp");
	//sbitmap.resize(512,512);

	return 0;*/
/*	CTexture asdf;
	asdf.CreateImage(256,256,24);
	asdf.SetColor(4,4,244,244,244);
	asdf.WriteTGA("c:/burak.tga",256,256,asdf.image);
*/

	//return 0;
	if (!CreateGLWindow("Imagine 3D",800,600,16,false))
	{
		return 0;							
	}	

	//EnableSphereMap();

	xrot = 0;
//	loda.percent = 20;

//	datt.OpenPak("data.dat");

//	www.textcolor.r = 1;www.textcolor.g = 1;www.textcolor.b = 1;  
	curtime = GetTickCount();
	glEnable(GL_TEXTURE_2D);
//	GDefFont(texter);
//	GSmaFont(CreateFont ("Arial",10));

//	tex1.LoadBMPFile(proje,mar.ReturnPos("textures/imagine2.bmp"));
//	loda.texture.LoadBMPFile(proje,mar.ReturnPos("textures/loading.bmp"));

/*	tex1.LoadBMPFile("data.dat",datt.ReturnPos("imagine2.bmp"));
	loda.texture.LoadBMPFile("data.dat",datt.ReturnPos("loading.bmp"));

	cb1.LoadBMPFile("data.dat",datt.ReturnPos("c1.bmp"));
	cb2.LoadBMPFile("data.dat",datt.ReturnPos("c2.bmp"));
	cte1.LoadBMPFileCK("data.dat",0,0,255,datt.ReturnPos("arrow.bmp"));*/

	IBitmap bayrak,guim;
	bayrak.createbitmap(192,128);
	bayrak.turkbayragi();
	bayrak.gettexid();
	//tex1.LoadBMPFile("imagine2.bmp");
//	tex1.ID = guim.ID;

//	loda.texture.LoadBMPFile("loading.bmp");

//	hitb.value = true;
//	mycb.value = true;
//	bbs.texid = cb2.ID;
//	bbs.autogetcampos = false;

//	GCBox(cb1.ID,cb2.ID);
//	GCTex(cte1.ID);
//	GCInit();

	InitGUI();

	//playmusic();
//	Camera.setcamera(0,0,5,0,0,-1);
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


			/*
			if (IsKeyPress(VK_F1))					
			{
				SetKeyPress(VK_F1, false);			
				KillGLWindow();						
				SetFullScreen(!IsFullScreen());		
				if (!CreateGLWindow("Imagine 3D",800,600,16,IsFullScreen()))
				{
					return 0;					
				}
				texter = CreateFont ("Arial",12);

			}*/

		}
	}

	//stopmusic();
	KillGLWindow();				
	return (msg.wParam);		
}

void LoadData()
{
	InProgress("tree.im3");
	SetUp_GL_ARB_multitexture();
	SetUp_GL_ARB_vertex_program();

/*	plxtest.vertexp = lfprogram("programs/bump_and_parallax.vp");
	plxtest.fragmep = lfprogram("programs/bump_and_parallax.fp");
	cb1.LoadBMPFile("rockwall.bmp");
	plxtest.basemap = cb1.ID;
	cb1.LoadBMPFile("rockwall_normal.bmp");
	plxtest.normmap = cb1.ID;
	cb1.LoadBMPFile("rockwall_height.bmp");
	plxtest.heigmap = cb1.ID;*/

/*	scen.LoadScale.set(0.05f,0.05f,0.05f);
	scen.LoadIM3("basemesh.im3",0);
	
	//scen.BoneSystem.LoadIMB("walk.im3",0);	
	scen.LoadTexturesA();*/
//	super.LoadScale.set(1,1,1);
/*	super.LoadScale.set(0.05f,0.05f,0.05f);
//	super.LoadIM3("data.dat",datt.ReturnPos("basemesh.im3"));
	super.LoadIM3("basemesh.im3",0);
	super.LoadTexturesA();
	super.PrepareAnim(1);
//	super.IM3Anims[0].LoadIMB("data.dat",datt.ReturnPos("walk.im3"));
	super.IM3Anims[0].LoadIMB("walk.im3",0);
	super.animid = 0;
	super.loadedanims = 1;
	super.AttachBones();
	sup2.LoadScale.set(0.05f,0.05f,0.05f);
//	sup2.LoadIM3("data.dat",datt.ReturnPos("basemesh.im3"));
	sup2.LoadIM3("basemesh.im3",0);
	sup2.LoadTexturesA();*/
/*	envs.LoadIM3("try.IM3",0);
	envs.PrepareTexture(4);
	envs.TextureCache[0].ID = 0;
	envs.TextureCache[1].ID = 0;
	envs.TextureCache[2].ID = 0;
	envs.TextureCache[3].ID = 0;
	envs.Scale(mv3f(0.01f,0.01f,0.01f));
	envs.CalculateLightMaps();
*/
	box.LoadIM3("burak.im3",0);
	chrom.LoadBMPFile("Chrome.bmp",0);
	//box.Scale(mv3f(0.01f,0.01f,0.008f));
						//glScalef(0.01f,0.01f,0.008f);

	shw.bumptexs = true;
	shw.LoadIM3("bump2.im3",0);
//	shw.RescIM3(MAKEINTRESOURCE(IDR_IM31));
	shw.LoadTexturesA();
	//shw.Scale(mv3f(0.05f,0.05f,0.05f));


	shw.CalculateTangentSpace();
//	shw.PrepareTexture(2);
	IBitmap loa;

	loa.createbitmap(64,64);
	loa.fillall(m24b(0,0,0));
//	loa.wideline(32,1,32,64,5,mono(255));
//	loa.wideline(1,32,64,32,5,mono(255));

	loa.centergradient(32);
	loa.gettexid();
	ssys.texid = loa.ID;

	cb1.LoadBMPFile("lamp.bmp");
	lamp = cb1.ID;



/*	IBitmap bs;
	bs.loadbmp("terrain.bmp");
	terra.CreateTile(bs);
	terra.CalculateNormals();
	terra.Scale(mv3f(1,1.5f,1));
	terra.PrepareTexture(1);
	//terra.TextureCache[0].ID = 0;
	terra.TextureCache[0].LoadBMPFile("terrain-texture3.bmp");
	*/
	//terra.IM3Header.vertexlights = false;
	//terra.bumptexs = false;
	//terra.Scale(mv3f(0.1f,0.1f,0.1f));
	
	//terra.Scale(mv3f(3,3,3));
	/*
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
*/

//	loa.createbitmap(640,480);
//	pro1.createbitmap(192,128);
	//pro2.createbitmap(256,256);
	/*
	loa.loadbmp("ae.bmp");
	loa.loadpal("pal.raw");
	loa.monochrome();
	loa.emboss();
	loa.edged();
	loa.gettexid();
	loa.writebmp("burakspec.bmp");
*/

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

//	shw.TextureCache[0].ID = loa.ID;
	
//	shw.TextureCache[1].ID = pro1.ID;

	

/*
	char asg[100];
	sprintf(asg,"/ %f   %f   %f \\",super.IM3Anims[0].IMBBones[0].frames[0].m[0],super.IM3Anims[0].IMBBones[0].frames[0].m[1],super.IM3Anims[0].IMBBones[0].frames[0].m[2]);
	GCAdd(asg);
	sprintf(asg,"| %f   %f   %f |",super.IM3Anims[0].IMBBones[0].frames[0].m[3],super.IM3Anims[0].IMBBones[0].frames[0].m[4],super.IM3Anims[0].IMBBones[0].frames[0].m[5]);
	GCAdd(asg);
	sprintf(asg,"| %f   %f   %f |",super.IM3Anims[0].IMBBones[0].frames[0].m[6],super.IM3Anims[0].IMBBones[0].frames[0].m[7],super.IM3Anims[0].IMBBones[0].frames[0].m[8]);
	GCAdd(asg);
	sprintf(asg,"\\ %f   %f   %f /",super.IM3Anims[0].IMBBones[0].frames[0].m[9],super.IM3Anims[0].IMBBones[0].frames[0].m[10],super.IM3Anims[0].IMBBones[0].frames[0].m[11]);
	GCAdd(asg);
*/
	



/*	tree.LoadScale.set(0.02f,0.02f,0.02f);
	tree.LoadIM3("data/models/Tree02.im3",0);
	tree.LoadTexturesA();

	scen.LoadScale.set(0.01f,0.01f,0.01f);
	scen.LoadIM3("data/models/Scene01.im3",0);
	scen.LoadTexturesA();

	amele.LoadScale.set(0.005f,0.005f,0.005f);
	amele.LoadIM3("data/models/adam.im3",0);
	amele.LoadTexturesA();*/

//	env.SetTextures(2);
	//env.ct1[0].LoadBMPFileCK(proje,0,0,255,mar.ReturnPos("textures/1.bmp"));
	//env.ct1[1].LoadBMPFileCK(proje,0,0,255,mar.ReturnPos("textures/2.bmp"));
//	env.ct1[0].LoadBMPFile("8.bmp");
	//env.ct1[1].LoadBMPFile("12.bmp");
//	env.ct1[1].ID = 0;
//	env.LoadIMO("light.im3",0);

	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );   
/*
	GLfloat diffuse_light0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position_light0[] = { 0.5f, -0.5f, -0.5f, 0.0f };
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse_light0 );
	glLightfv( GL_LIGHT0, GL_POSITION, position_light0 );

	// Set light 1 to be a simple, faint grey directional light so 
    // the walls and floor are slightly different shades of grey
	GLfloat diffuse_light1[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat position_light1[] = { 0.3f, -0.5f, 0.2f, 0.0f };
	//GLfloat position_light1[] = { 0.3f, -0.5f, -0.2f, 0.0f };
	glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse_light1 );
	glLightfv( GL_LIGHT1, GL_POSITION, position_light1 );

*/
	GLfloat ambient_lightModel[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//GLfloat ambient_lightModel[] = { 0.55f, 0.55f, 0.55f, 1.0f };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_lightModel );

//	loda.percent = 100;
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
//		www.caption = ho;
//		www.render (260,445,14,299,false);
//		loda.percent++;
//		loda.render(260,400,-30,300);

		//DrawFPS(texter);
		DrawedFrame();
		glColor3f(1.0f, 1.0f, 1.0f);
		SwapBuffers(GethDC());
}