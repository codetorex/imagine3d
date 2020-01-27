#include "cvision.h"
#include <stdio.h>
	HDC			hDC=NULL;	
	HGLRC		hRC=NULL;	
	HWND		hWnd=NULL;	
	HINSTANCE	hInstance;	

	bool	keys[256];			
	bool	mouse[2];
	bool	active=TRUE;	
	bool	fullscreen=FALSE;	
	int mx,my;

	int wi;
	int hi;
	int FramesPerSecond;
	

	unsigned int worldfont;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	
HWND VHwnd()
{
	return hWnd;
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)	
{
	if (height==0)										
	{
		height=1;									
	}

	glViewport(0,0,width,height);			

	glMatrixMode(GL_PROJECTION);					
	glLoadIdentity();								

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);					
	glLoadIdentity();								
}

int InitGL(GLvoid)								
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);						
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			
	glClearDepth(1.0f);								
	glEnable(GL_DEPTH_TEST);					
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	


	return TRUE;									
}

bool IsKeyPress(int keyno)
{
	return keys[keyno];
}

int GetWidth()
{
	return wi;
}

int GetHeight()
{
	return hi;
}

void SetKeyPress(int keyno,bool stat)
{
	keys[keyno] = stat;
}

bool IsFullScreen()
{
	return fullscreen;
}

void SetFullScreen(bool valu)
{
	fullscreen = valu;
}

HDC GethDC()
{
	return hDC;
}

bool GetActive()
{
	return active;
}

int GetMouseX()
{
	return mx;
}

int GetMouseY()
{
	return my;
}
bool GetMouseClick(int btn)
{
	return mouse[btn];
}
void SetMouseClick(int btn,bool val)
{
	mouse[btn] = val;
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			
	WNDCLASS	wc;					
	DWORD		dwExStyle;			
	DWORD		dwStyle;		
	RECT		WindowRect;			
	WindowRect.left=(long)0;		
	WindowRect.right=(long)width;	
	WindowRect.top=(long)0;			
	WindowRect.bottom=(long)height;	
	wi = width;
	hi = height;
	fullscreen=fullscreenflag;	

	hInstance			= GetModuleHandle(NULL);			
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	wc.lpfnWndProc		= (WNDPROC) WndProc;			
	wc.cbClsExtra		= 0;								
	wc.cbWndExtra		= 0;								
	wc.hInstance		= hInstance;						
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);		
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);	
	wc.hbrBackground	= NULL;								
	wc.lpszMenuName		= NULL;						
	wc.lpszClassName	= "OpenGL";							

	if (!RegisterClass(&wc))							
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;										
	}
	
	if (fullscreen)									
	{
		DEVMODE dmScreenSettings;							
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);	
		dmScreenSettings.dmPelsWidth	= width;				
		dmScreenSettings.dmPelsHeight	= height;			
		dmScreenSettings.dmBitsPerPel	= bits;					
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		
			}
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;								
			}
		}
	}

	if (fullscreen)												
	{
		dwExStyle=WS_EX_APPWINDOW;							
		dwStyle=WS_POPUP;								
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			
		dwStyle=WS_OVERLAPPEDWINDOW;						
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	

	if (!(hWnd=CreateWindowEx(	dwExStyle,							
								"OpenGL",					
								title,					
								dwStyle |						
								WS_CLIPSIBLINGS |				
								WS_CLIPCHILDREN,				
								0, 0,							
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,							
								NULL,					
								hInstance,						
								NULL)))							
	{
		KillGLWindow();							
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;						
	}

	static	PIXELFORMATDESCRIPTOR pfd=			
	{
		sizeof(PIXELFORMATDESCRIPTOR),			
		1,										
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |					
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,							
		bits,									
		0, 0, 0, 0, 0, 0,						
		0,											
		0,											
		0,											
		0, 0, 0, 0,								
		16,											 
		0,									
		0,										
		PFD_MAIN_PLANE,							
		0,										
		0, 0, 0								
	};
	
	if (!(hDC=GetDC(hWnd)))							
	{
		KillGLWindow();						
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		
	{
		KillGLWindow();							
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if (!(hRC=wglCreateContext(hDC)))			
	{
		KillGLWindow();						
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if(!wglMakeCurrent(hDC,hRC))					
	{
		KillGLWindow();						
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	ShowWindow(hWnd,SW_SHOW);					
//	SetForegroundWindow(hWnd);				
	SetFocus(hWnd);								
	ReSizeGLScene(width, height);			
	
	if (!InitGL())								
	{
		KillGLWindow();				
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}
	return TRUE;							
}

GLvoid KillGLWindow(GLvoid)							
{
	if (fullscreen)									
	{
		ChangeDisplaySettings(NULL,0);			
		ShowCursor(TRUE);							
	}

	if (hRC)										
	{
		if (!wglMakeCurrent(NULL,NULL))			
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))					
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										
	}

	if (hDC && !ReleaseDC(hWnd,hDC))				
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;									
	}

	if (hWnd && !DestroyWindow(hWnd))				
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;									
	}

	if (!UnregisterClass("OpenGL",hInstance))		
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;							
	}
}

LRESULT CALLBACK WndProc(	HWND	hWnd,		
							UINT	uMsg,		
							WPARAM	wParam,		
							LPARAM	lParam)		
{
	switch (uMsg)								
	{
		case WM_ACTIVATE:						
		{
			if (!HIWORD(wParam))				
			{
				active=TRUE;				
			}
			else
			{
				active=FALSE;					
			}

			return 0;						
		}

		case WM_SYSCOMMAND:					
		{
			switch (wParam)				
			{
				case SC_SCREENSAVE:				
				case SC_MONITORPOWER:		
				return 0;						
			}
			break;								
		}

		case WM_CLOSE:							
		{
			PostQuitMessage(0);				
			return 0;						
		}

		case WM_KEYDOWN:						
		{
			keys[wParam] = TRUE;			
			return 0;						
		}

		case WM_KEYUP:							
		{
			keys[wParam] = FALSE;				
			return 0;							
		}

		case WM_LBUTTONDOWN:
		{
			mouse[0] = true;
			return 0;
		}

		case WM_LBUTTONUP:
		{
			mouse[0] = false;
			return 0;
		}

		case WM_RBUTTONDOWN:
		{
			mouse[1] = true;
			return 0;
		}

		case WM_RBUTTONUP:
		{
			mouse[1] = false;
			return 0;
		}

		case WM_MOUSEMOVE:
		{
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			return 0;
		}

		case WM_SIZE:							
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  
			return 0;							
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


unsigned int CreateFont(char *fontName, int Size)
{
   HFONT hFont;
   unsigned int base;

   base = glGenLists(96);

   if(stricmp(fontName, "symbol")==0)
      {
         hFont = CreateFont(Size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                            SYMBOL_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                            ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, fontName);
      }
   else
      {
         hFont = CreateFont(Size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                            ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                            ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, fontName);
      }

   if(!hFont)
      return 0;

   SelectObject(hDC, hFont);
   wglUseFontBitmaps(hDC, 32, 96, base);

   return base;
}


void PrintText(unsigned int base, char *string)
{
   if((base == 0 || string == NULL))
      return;

   glPushAttrib(GL_LIST_BIT);
      glListBase(base - 32);
      glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);
   glPopAttrib();
}


void ClearGLFont(unsigned int base)
{
   if(base != 0)
      glDeleteLists(base, 96);
}

float fCord (bool iswi,int x)
{
	float da;
	if (iswi == true) 
	{ 
		da = (float)(x / wi) ;
	}else{
		da = (float)(x / hi) ;
	};
	return da;
}

void DrawedFrame()
{
   static float FPS = 0.0f;
   float nextSecond = 0.0f;
   static float prevSecond = 0.0f;
   FPS++;
   nextSecond = GetTickCount() * 0.001f;				
   if(nextSecond - prevSecond > 1.0f)
      {
			prevSecond = nextSecond;
			FramesPerSecond = int(FPS);
			FPS = 0;
      }
}

int GetFPS()
{
return FramesPerSecond;
}

void DrawFPS(unsigned int font)
{
	char last[10];
	itoa(FramesPerSecond,last,10);
	strcat(last," FPS");
	glColor3f(0.905f, 0.682f, 0.1607f);
    glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.0f);
    glRasterPos2f(-0.53f,0.38f);
    PrintText(font, last);
}

void EnableColorKeyT()
{
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
};

void EnableSphereMap()
{

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glEnable(GL_TEXTURE_GEN_S);     // Enable spherical
	glEnable(GL_TEXTURE_GEN_T);     // Environment Mapping,

};

void RenderPlane(float x1,float y1,float x2,float y2)
{
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(x1, y1, 0.0f);		
		glTexCoord2f(1.0f, 1.0f); 	glVertex3f(x2, y1, 0.0f);			
		glTexCoord2f(1.0f, 0.0f);  	glVertex3f(x2, y2, 0.0f);			
		glTexCoord2f(0.0f, 0.0f); 	glVertex3f(x1, y2, 0.0f);				
	glEnd();

};


void RenderPicture(float x1,float y1,float height,float width)
{
	float x2,y2;
	x2 = x1 + height;
	y2 = y1 + width;
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(x1, y1, 0.0f);		
		glTexCoord2f(1.0f, 1.0f); 	glVertex3f(x2, y1, 0.0f);			
		glTexCoord2f(1.0f, 0.0f);  	glVertex3f(x2, y2, 0.0f);			
		glTexCoord2f(0.0f, 0.0f); 	glVertex3f(x1, y2, 0.0f);				
	glEnd();

};

void enTP()
{
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);	
}

void diTP()
{
	glDisable(GL_BLEND);
	glColor4f(1.0f,1.0f,1.0f,1.0f);			
}

void Enter2D()	
{
	glDisable(GL_DEPTH_TEST);						
	glMatrixMode(GL_PROJECTION);					
	glPushMatrix();									
	glLoadIdentity();									
	glOrtho(0,GetWidth(),GetHeight(),0,-1,1);		
	glMatrixMode(GL_MODELVIEW);						
	glPushMatrix();									
}


void Exit2D()
{
	glMatrixMode(GL_PROJECTION);					
	glPopMatrix();								
	glMatrixMode(GL_MODELVIEW);						
	glPopMatrix();									
	glEnable(GL_DEPTH_TEST);						
}

void SetDefFont(unsigned int font)
{
	worldfont = font;
};

unsigned int GetDefFont()
{
	return worldfont;
};

/*
class CTimer
{
	int		st;				// started ticks
public:
	CTimer();
	void	start(int le);	// starter
	bool	en;				// enabled
	int		le;				// length
	float	gf();			// get float
	int		gi();			// get integer
};
*/
CTimer::CTimer()
{
	en = false;
}

void CTimer::start(int cle)
{
	st = GetTickCount();
	le = cle;
	en = true;
}

int CTimer::gi()
{
	return GetTickCount()-st;
}

float CTimer::gf()
{
	return (float)gi() /(float)le ;
}