#include<windows.h>                           
#include<stdio.h>                         
#include<gl/gl.h>                              
#include<gl/glu.h> 
#include "ceffect.h"

void CEffect::LoadBMP(char *bmppath,float sfac,int poss)
{
	float h1,w1;

	mats = new CTexture[1];
	mats[0].LoadBMPFileCK(bmppath,0,0,255,poss);
	w1 = (float)mats[0].imageWidth / 2; //hehe1
	h1 = (float)mats[0].imageHeight / 2; //hehe2
	
	/*
	BBVertek(0) = CLIT(-hehe * scalefactor, -hehe2 * scalefactor, 0 * scalefactor, -1, 0.5, 0#, 1#)
    BBVertek(1) = CLIT(-hehe * scalefactor, hehe2 * scalefactor, 0 * scalefactor, -1, 0.5, 0#, 0#)
    BBVertek(2) = CLIT(hehe * scalefactor, -hehe2 * scalefactor, 0 * scalefactor, -1, 0.5, 1#, 1#)
    BBVertek(3) = CLIT(hehe * scalefactor, hehe2 * scalefactor, 0 * scalefactor, -1, 0.5, 1#, 0#)
	*/
	vexs[0] = -w1 * sfac;
	vexs[1] = -h1 * sfac;
	//vexs[2] = 0 * scalefactor;

	vexs[2] = -w1 * sfac;
	vexs[3] = h1 * sfac;

	vexs[4] = w1 * sfac;
	vexs[5] = -h1 * sfac;
	
	vexs[6] = w1 * sfac;
	vexs[7] = h1 * sfac;
}

void CEffect::Render(float x,float y,float z,CCamera cam)
{

	//glLoadIdentity();
	glTranslatef(x,y,z);
//	glRotatef(cam.myangle * 360,0,1,0);

	glBindTexture(GL_TEXTURE_2D, mats[0].ID);

	glBegin(GL_TRIANGLES);
		
		glTexCoord2f(0,1);
		glVertex3f(vexs[0],vexs[1],0);

		glTexCoord2f(0,0);
		glVertex3f(vexs[2],vexs[3],0);

		glTexCoord2f(1,1);
		glVertex3f(vexs[4],vexs[5],0);


		glTexCoord2f(1,0);
		glVertex3f(vexs[6],vexs[7],0);

	glEnd();
}