
#include "cvision.h"
#include"CCamera.h"
/*
class CCamera
{
private:
	int lx,ly;
	int cx,cy;
	int ltim;
	int etim;

public:
	CCamera();
	void getinput();
	float speedf;
	vector3f vEye;
	vector3f vLook;
	vector3f vUp;

	void setcamera( float cx,float cy,float cz,float lx,float ly,float lz );
	void render();
};

CCamera::CCamera()
{
	lx = ly = cx = cy = ltim = etim = 0;
}

void getinput()
{
	cx = GetMouseX();
	cy = GetMouseY();
	etim = GetTickCount() - ltim;
	ltim = GetTickCount();

	int xdif = ( cx - lx);
	int ydif = ( cy - ly);

	if (xdif != 0)
	{
		
	}
	if (ydif != 0)
	{
		
	}
}*/

/*
CCamera::CCamera()
{
	mousing = true;
	movespeed = 25.0f;
	elapsedtime = 1;
	lasttime = 2;
	vEye.set(0.0f, 0.0f, 5.0f);   // Eye Position
	vLook.set(0.0f, 0.0f, -1.0f); // Look Vector
	vUp.set(0.0f, 1.0f, 0.0f);    // Up Vector
	vRight.set(1.0f, 0.0f, 0.0f); // Right Vector
	LastMousePos.x = 0;
	LastMousePos.y = 0;
}

void CCamera::GetInput()
{
	POINT mousePosit;
	GetCursorPos( &mousePosit );
	//ScreenToClient(VHwnd(), &mousePosit );

	CurMousePos.x = mousePosit.x;
	CurMousePos.y = mousePosit.y;

	matrix4x4f matRotation;

	if ( mousing )
	{
		int nXDiff = ( CurMousePos.x - LastMousePos.x);
		int nYDiff = ( CurMousePos.y - LastMousePos.y);

		if (nYDiff != 0)
		{
            matRotation.rotate( -(float)nYDiff / 3.0f, vRight );
            matRotation.transformVector( &vLook );
            matRotation.transformVector( &vUp );
		}
		if ( nXDiff != 0 )
		{
            matRotation.rotate( -(float)nXDiff / 3.0f, vector3f(0.0f, 1.0f, 0.0f) );
            matRotation.transformVector( &vLook );
            matRotation.transformVector( &vUp );

		}
	}

	LastMousePos.x = 400;
	LastMousePos.y = 300;
	SetCursorPos(400,300);

	vector3f tmpLook = vLook;
	vector3f tmpRight = vRight;

	if(IsKeyPress(VK_UP))		vEye -= tmpLook*-movespeed*elapsedtime;
	if(IsKeyPress(VK_DOWN))		vEye += (tmpLook*-movespeed)*elapsedtime;
	if(IsKeyPress(VK_LEFT))		vEye -= (tmpRight*movespeed)*elapsedtime;
	if(IsKeyPress(VK_RIGHT))	vEye += (tmpRight*movespeed)*elapsedtime;
	if(IsKeyPress(VK_PRIOR))	vEye.y += movespeed*elapsedtime; 
	if(IsKeyPress(VK_NEXT))		vEye.y -= movespeed*elapsedtime;


}


void CCamera::UpdateMatrix()
{
	matrix4x4f view;
	view.identity();

	vLook.normalize();

	vRight = cross(vLook, vUp);
	vRight.normalize();

	vUp = cross(vRight, vLook);
	vUp.normalize();

	view.m[0] =  vRight.x;
	view.m[1] =  vUp.x;
	view.m[2] = -vLook.x;
	view.m[3] =  0.0f;

	view.m[4] =  vRight.y;
	view.m[5] =  vUp.y;
	view.m[6] = -vLook.y;
	view.m[7] =  0.0f;

	view.m[8]  =  vRight.z;
	view.m[9]  =  vUp.z;
	view.m[10] = -vLook.z;
	view.m[11] =  0.0f;

	view.m[12] = -dot(vRight, vEye);
	view.m[13] = -dot(vUp, vEye);
	view.m[14] =  dot(vLook, vEye);
	view.m[15] =  1.0f;

	glMultMatrixf( view.m );
}

void CCamera::render()
{
	elapsedtime = (GetTickCount() - lasttime)*0.000000001f;
	lasttime = curtime;

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	UpdateMatrix();
	xView = vLook.x;
	yView = vLook.y;
	zView = vLook.z;
	xPos = vEye.x;
	yPos = vEye.y;
	zPos = vEye.z;
}
void CCamera::setcamera (float cx,float cy,float cz,float lx,float ly,float lz)
{
	vEye.x = cx;
	vEye.y = cy;
	vEye.z = cz;

	vLook.x = lx;
	vLook.y = ly;
	vLook.z = lz;

}

*/


		int ScreenWidth = 800;
		int ScreenHeight = 600;


FILE *dosya;

CCamera::CCamera()
{
   // Initialize variables...
   xPos = yPos = zPos = 0;
   xView = yView = zView = 0;
   xUp = yUp = zUp = 0;
   xStrafe = yStrafe = zStrafe = 0;
}



void CCamera::render()
{
   gluLookAt(xPos, yPos, zPos,xView, yView, zView,xUp, yUp, zUp);
//gluLookAt(xPos, yPos, zPos,xView+xPos, yView+yPos, zView+zPos,xUp, yUp, zUp);
}
void CCamera::rendertps()
{
   gluLookAt(xView,yView,zView ,xPos,yPos ,zPos ,xUp, yUp, zUp);
//gluLookAt(xPos, yPos, zPos,xView+xPos, yView+yPos, zView+zPos,xUp, yUp, zUp);
}


void CCamera::GetInput()
{
	etim = 0.4f + (GetTickCount() - ltim)*0.04f;
	ltim = GetTickCount();

   int w = ScreenWidth >> 1;
   int h = ScreenHeight >> 1;

   if(IsKeyPress('W'))
      MoveCamera(UP*etim);                   

   if(IsKeyPress('S'))
      MoveCamera(DOWN*etim);                   

   if(IsKeyPress('A'))
      StrafeCam(STRAFE_LEFT*etim);              

   if(IsKeyPress('D'))
      StrafeCam(STRAFE_RIGHT*etim);  
   if(GetMouseClick(0))
   {
		yPos+=0.1f * etim;
		yView+=0.1f *etim;
   }

   if(GetMouseClick(1))
   {
		yPos-=0.1f*etim;
		yView-=0.1f*etim;
   }
	

   if(IsKeyPress(VK_PRIOR))					// :P Up camera yap
   {
		yPos+=0.1f * etim;
		yView+=0.1f *etim;
   };

   if(IsKeyPress(VK_NEXT))					// :P down plz
   {
		yPos-=0.1f*etim;
		yView-=0.1f*etim;
   };

 //  if(IsKeyPress(VK_INSERT))				// :p Give Me THE CORDÝNATES PLZ
 //  {
//		dosya = fopen("cords.dat","w+t");
//		fprintf(dosya,"CORDS: %f\t%f\t%f",xPos,yPos,zPos);
//   };



   POINT mousePos;
	GetCursorPos(&mousePos);

   RotateByMouse(mousePos.x, mousePos.y, w, h);

   SetCursorPos(w, h);
}

void CCamera::SetCamera(float x, float y, float z,
                        float xv, float yv, float zv,
                        float xu, float yu, float zu)
{
   xPos = x;   yPos = y;   zPos = z;
   xView = xv; yView = yv; zView = zv;
   xUp = xu;   yUp = yu;   zUp = zu;
}


void CCamera::MoveCamera(float direction)
{
   float xLookDirection = 0, yLookDirection = 0, zLookDirection = 0;

   xLookDirection = xView - xPos;
	yLookDirection = yView - yPos;
	zLookDirection = zView - zPos;

   float dp = 1 /(float)sqrt(xLookDirection * xLookDirection + yLookDirection * yLookDirection +
                             zLookDirection * zLookDirection);
   xLookDirection *= dp;
   yLookDirection *= dp;
   zLookDirection *= dp;

   UpdateCamera(xLookDirection, yLookDirection, zLookDirection, direction);

}


void CCamera::UpdateCamera(float xDir, float yDir, float zDir, float dir)
{
	xPos += xDir * dir;
	zPos += zDir * dir;

	xView += xDir * dir;
	zView += zDir * dir;
}


void CCamera::StrafeCam(float direction)
{
   CalculateStrafe();                      
   UpdateCamera(xStrafe, yStrafe, zStrafe, direction);  
}


void CCamera::CalculateStrafe()
{
   float xDir = 0, yDir = 0, zDir = 0;
   float xCross = 0, yCross = 0, zCross = 0;

   xDir = xView - xPos;
	yDir = yView - yPos;
	zDir = zView - zPos;

   float dp = 1 /(float)sqrt(xDir * xDir + yDir * yDir + zDir * zDir);
   xDir *= dp;
   yDir *= dp;
   zDir *= dp;

   xCross = (yDir * zUp) - (zDir * yUp);
   yCross = (zDir * xUp) - (xDir * zUp);
   zCross = (xDir * yUp) - (yDir * xUp);

   xStrafe = xCross;
   yStrafe = yCross;
   zStrafe = zCross;
}


void CCamera::RotateCamera(float AngleDir, float xSpeed, float ySpeed, float zSpeed)
{
	float xNewLookDirection = 0, yNewLookDirection = 0, zNewLookDirection = 0;
	xLookDirection = 0; yLookDirection = 0; zLookDirection = 0;
   float CosineAngle = 0, SineAngle = 0;

	GET_COS(CosineAngle, AngleDir);
   GET_SINE(SineAngle, AngleDir);

   xLookDirection = xView - xPos;
	yLookDirection = yView - yPos;
	zLookDirection = zView - zPos;

   float dp = 1 /(float)sqrt(xLookDirection * xLookDirection + yLookDirection * yLookDirection +
                             zLookDirection * zLookDirection);
   xLookDirection *= dp;
   yLookDirection *= dp;
   zLookDirection *= dp;

	xNewLookDirection = (CosineAngle + (1 - CosineAngle) * xSpeed) * xLookDirection;
	xNewLookDirection += ((1 - CosineAngle) * xSpeed * ySpeed - zSpeed * SineAngle)* yLookDirection;
	xNewLookDirection += ((1 - CosineAngle) * xSpeed * zSpeed + ySpeed * SineAngle) * zLookDirection;

	yNewLookDirection = ((1 - CosineAngle) * xSpeed * ySpeed + zSpeed * SineAngle) * xLookDirection;
	yNewLookDirection += (CosineAngle + (1 - CosineAngle) * ySpeed) * yLookDirection;
	yNewLookDirection += ((1 - CosineAngle) * ySpeed * zSpeed - xSpeed * SineAngle) * zLookDirection;

	zNewLookDirection = ((1 - CosineAngle) * xSpeed * zSpeed - ySpeed * SineAngle) * xLookDirection;
	zNewLookDirection += ((1 - CosineAngle) * ySpeed * zSpeed + xSpeed * SineAngle) * yLookDirection;
	zNewLookDirection += (CosineAngle + (1 - CosineAngle) * zSpeed) * zLookDirection;
	//myangle = (zView - zPos) / 4*(xView-xPos);
	xView = xPos + xNewLookDirection;
	yView = yPos + yNewLookDirection;
	zView = zPos + zNewLookDirection;
}


void CCamera::RotateByMouse(int mousePosX, int mousePosY, int midX, int midY)
{
	float yDirection = 0.0f;        
	float yRotation = 0.0f;   

	if((mousePosX == midX) && (mousePosY == midY))
      return;

	yDirection = (float)((midX - mousePosX)) / 1000.0f;		
	yRotation = (float)((midY - mousePosY)) / 1000.0f;		

	currentRotationAngle -= yRotation;  

	if(currentRotationAngle > 1.0f)
      {
		   currentRotationAngle = 1.0f;
         return;
      }

	if(currentRotationAngle < -1.0f)
		{
         currentRotationAngle = -1.0f;
         return;
      }

   float xDir = 0, yDir = 0, zDir = 0;
   xAxis = 0;yAxis = 0;zAxis = 0;

   xDir = xView - xPos;
	yDir = yView - yPos;
	zDir = zView - zPos;

   xAxis = (yDir * zUp) - (zDir * yUp);
   yAxis = (zDir * xUp) - (xDir * zUp);
   zAxis = (xDir * yUp) - (yDir * xUp);

   float len = 1 /(float)sqrt(xAxis * xAxis + yAxis * yAxis + zAxis * zAxis);
   xAxis *= len;
   yAxis *= len;
   zAxis *= len;

   RotateCamera(yRotation, xAxis, yAxis, zAxis);
   RotateCamera(yDirection, 0, 1, 0);
}


