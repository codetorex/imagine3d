

#ifndef CTEXTURE_H
#define CTEXTURE_H

#include<windows.h>                           
#include<stdio.h>                         
#include <gl\gl.h>			
#include <gl\glu.h>			

#define BITMAP_ID 0x4D42	                    


class CTexture
{
   public:
      CTexture();                              
      ~CTexture();                           

      bool LoadBMPFile(char *file,int posit=0);        
	  bool LoadBMPFileCK(char *file,GLubyte ra,GLubyte ga,GLubyte ba,int posit=0);
      bool LoadTGAFile(char *file);            
      bool LoadPCXFile(char *file);
	  void LoadTEXFile(char *file,int posit=0);

      bool CreateImage(int w, int h, int b);  
	  void EnvironmentMap(int w, int h);

      inline void GetColor(unsigned int x,
                           unsigned int y,
                           unsigned char *pR,
                           unsigned char *pG,
                           unsigned char *pB);
      void SetColor(unsigned int x,
                           unsigned int y,
                           unsigned char r,
                           unsigned char g,
                           unsigned char b); 
      bool WriteBMP(char *file, int width, int height,
                    unsigned char *output);   
      bool WriteTGA(char *file, short int width, short int height,
                    unsigned char *outImage);
      void SaveBMPScreenShot(char *filename,
                             int w, int h);    
      void SaveTGAScreenShot(char *filename,
                             int w, int h);    

      void FreeImage();                        

      unsigned int ID;                       
      int imageWidth;                           
      int imageHeight;                      

      void GenerateTexture();              
	  unsigned char *LoadBitmap(char *file, BITMAPINFOHEADER *bitmapInfoHeader,int positi);
	  unsigned char *LoadBitmapCK(char *file, BITMAPINFOHEADER *bitmapInfoHeader,int positi,GLubyte ra,GLubyte ga,GLubyte ba);
      bool LoadTGA(char *file);        
      bool LoadPcx(char *file);        

      unsigned char *image;             
      unsigned char *palette;          
      bool textureExist;                
      int type;                      
};
void ATMem(int howmuch);
int GTMem();

#endif

