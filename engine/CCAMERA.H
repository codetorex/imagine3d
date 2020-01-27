
#ifndef CCAMERA_H
#define CCAMERA_H

#include "cvector3f.h"
#include "cmatrix4x4f.h"
#include <math.h>
#include <windows.h>
#include <stdio.h>
#include "cvision.h"

#define	Q_PI	3.14159265358979323846f
#define	Q_360	Q_PI*2
#define	Q_90	Q_PI/2



/*
class CCamera
{
private:
	float elapsedtime;
	float curtime;
	float lasttime;

	void UpdateMatrix();
	POINT  LastMousePos;
	POINT  CurMousePos;

public:
	CCamera();
	void GetInput();	
	bool mousing;
	float movespeed;
	float xPos,yPos,zPos;
	float xView,yView,zView;

	vector3f vEye;
	vector3f vLook;
	vector3f vUp;
	vector3f vRight;

	void SetCamera (float cx,float cy,float cz,float lx,float ly,float lz);
	void render();

};


*/

#include<math.h>                      
#include<windows.h>     

#define UP              0.1f          
#define DOWN            -0.1f    
#define LEFT            0.3f          
#define RIGHT           -0.3f         
#define STRAFE_LEFT     -0.1f       
#define STRAFE_RIGHT    0.1f      

#define GET_COS(a, b)   a = (float)cos(b)
#define GET_SINE(a, b)  a = (float)sin(b)


class CCamera
{
private:
	float ltim;
	float etim;
   public:
      CCamera();                                   
		void render();
		void rendertps();

		void GetInput();

      void SetCamera(float x, float y, float z,     
                     float xv, float yv, float zv,
                     float xu, float yu, float zu);

      void MoveCamera(float direction);               
      void UpdateCamera(float xDir, float yDir,
                        float zDir, float dir);     
      void StrafeCam(float direction);
      void CalculateStrafe();                         
      void RotateCamera(float AngleDir, float xSpeed, 
                        float ySpeed, float zSpeed);
      void RotateByMouse(int mousePosX, int mousePosY,
                         int midX, int midY);         

      float xPos, yPos, zPos;                      
      float xView, yView, zView;                     
      float xUp, yUp, zUp;                    
      float xStrafe, yStrafe, zStrafe;                
      float currentRotationAngle;
   float xAxis , yAxis , zAxis ;
   	float xLookDirection, yLookDirection, zLookDirection;


};


/*
class CCamera // First Person, Free Camera
{
private:


public:
	CCamera();
	float CamAngle,CamPitch;
	float xPos,yPos,zPos;
	float xView,yView,zView;
	float AngleConv;

	void GetInput();
	void UpdateCamera();

}
*/
#endif


