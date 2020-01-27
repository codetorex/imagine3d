#ifndef CVISION_H
#define CVISION_H


#include <windows.h>	
#include <gl\gl.h>			
#include <gl\glu.h>			
#include <gl\glaux.h>


class CTimer
{
public:
	int		st;				// started ticks
	CTimer();
	void	start(int cle);	// starter
	bool	en;				// enabled
	int		le;				// length
	float	gf();			// get float
	int		gi();			// get integer
};

void ReSizeGLScene(GLsizei width, GLsizei height);
int InitGL(GLvoid);
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);
void KillGLWindow(GLvoid);
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM	wParam,LPARAM lParam);
bool IsKeyPress(int keyno);
void SetKeyPress(int keyno,bool stat);
bool IsFullScreen();
void SetFullScreen(bool valu);
HDC GethDC();
bool GetActive();
float fColor (char ccode);
unsigned int CreateFont(char *fontName, int Size);
void PrintText(unsigned int base, char *string);
float fCord (bool iswi,int x);
void DrawedFrame();
int GetFPS();
void DrawFPS(unsigned int font);
void EnableColorKeyT();
void EnableSphereMap();
void RenderPlane(float x1,float y1,float x2,float y2);
void RenderPicture(float x1,float y1,float height,float width);
int GetWidth();
int GetHeight();
int GetMouseX();
int GetMouseY();
void enTP();
void diTP();
bool GetMouseClick(int btn);
void SetMouseClick(int btn,bool val);
void Enter2D();
void Exit2D();
unsigned int GetDefFont();
void SetDefFont(unsigned int font);
HWND VHwnd();

#endif
