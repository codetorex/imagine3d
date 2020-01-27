
#include "opts.h"
#include"CTexture.h"
#include<math.h>
#include "gui.h"
int texturemem;
void ATMem(int howmuch)
{
	texturemem += howmuch;
}

int GTMem()
{
	return texturemem;
}

CTexture::CTexture()
{
  image = 0;
  palette = 0;
  textureExist = false;
  type = 0;
  imageWidth = 0;
  imageHeight = 0;
  ID = 0;
}


CTexture::~CTexture()
{
   FreeImage();                  
   glDeleteTextures(1, &ID);    
}

void CTexture::LoadTEXFile(char *file,int posit)
{
	char typ;
	FILE *pFile;
	unsigned char *texturedata;
	long imgsize;
	
	if(textureExist)
      FreeImage();

	pFile = fopen(file,"rb");
	fseek(pFile,posit,0);
	fread(&imageWidth, sizeof(long), 1, pFile);
	fread(&imageHeight, sizeof(long), 1, pFile);
	fread(&typ, sizeof(char), 1, pFile);

	if (typ == 1)
	{
		imgsize = imageWidth * imageHeight * 4;
		type = GL_RGBA;
	}
	else
	{
		imgsize = imageWidth * imageHeight * 3;
		type = GL_RGB;
	}
	texturedata = new unsigned char[imgsize];
	fread(texturedata,sizeof(unsigned char),imgsize,pFile);
	image = texturedata;
	GenerateTexture();
	textureExist = true;
}

bool CTexture::LoadBMPFile(char *file,int posit)
{
	BITMAPINFOHEADER biHeader;    
   if(textureExist)
      FreeImage();

	image = LoadBitmap(file, &biHeader,posit);

	if(image == 0)
	   {
         return false;
	   }


   imageWidth = biHeader.biWidth;
   imageHeight = biHeader.biHeight;

   GenerateTexture();

#ifndef DISABLEGUI
	char farg[100];
	sprintf(farg,"Texture Load %i: %s",ID,file);//,GTMem());
	GCAdd(farg);
#endif

   textureExist = true;

   return true;
}

bool CTexture::LoadBMPFileCK(char *file,GLubyte ra,GLubyte ga,GLubyte ba,int posit)
{
	BITMAPINFOHEADER biHeader;    

   if(textureExist)
      FreeImage();

	image = LoadBitmapCK(file, &biHeader,posit,ra,ga,ba);

	if(image == 0)
	   {
         return false;
	   }

   imageWidth = biHeader.biWidth;
   imageHeight = biHeader.biHeight;

   GenerateTexture();
#ifndef DISABLEGUI
	char farg[100];
	sprintf(farg,"Texture Load %i: %s",ID,file);//,GTMem());
	GCAdd(farg);
#endif

   textureExist = true;

   return true;
}

bool CTexture::LoadTGAFile(char *file)
{
   if(textureExist)
      FreeImage();

   if(!LoadTGA(file))
      return false;

	if(image == 0)
	   {
         return false;
	   }

   GenerateTexture();

   textureExist = true;

   return true;
}


bool CTexture::LoadPCXFile(char *file)
{
   if(textureExist)
      FreeImage();

   if(!LoadPcx(file))
      return false;

	if(image == 0)
	   {
         return false;
	   }

   GenerateTexture();

   textureExist = true;

   return true;
}


void CTexture::GenerateTexture()
{
	int isize=3;
	isize*=imageWidth;
	isize*=imageHeight;
	ATMem(isize);

	glGenTextures(1, &ID);
   
   glBindTexture(GL_TEXTURE_2D, ID);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTexImage2D(GL_TEXTURE_2D, 0, type, imageWidth, imageHeight, 
                0, type, GL_UNSIGNED_BYTE, image);
   gluBuild2DMipmaps(GL_TEXTURE_2D, type, imageWidth, imageHeight,
                     type, GL_UNSIGNED_BYTE, image);
}


bool CTexture::LoadTGA(char* file)
{
   FILE *pfile;
   unsigned char tempColor;   
	unsigned char uselessChar; 
	short int	  uselessInt;	
   int colorMode;            
	long tgaSize;		        
	long index;                
   unsigned char imageTypeCode;
   unsigned char bitCount;
	

	pfile = fopen(file, "rb");

	if (!pfile)
		return false;

	fread(&uselessChar, sizeof(unsigned char), 1, pfile);
	fread(&uselessChar, sizeof(unsigned char), 1, pfile);
	
	fread(&imageTypeCode, sizeof(unsigned char), 1, pfile);

	if ((imageTypeCode != 2) && (imageTypeCode != 3))
	   {
		   fclose(pfile);
		   return false;
	   }


	fread(&uselessInt, sizeof(short int), 1, pfile);
	fread(&uselessInt, sizeof(short int), 1, pfile);
	fread(&uselessChar, sizeof(unsigned char), 1, pfile);
	fread(&uselessInt, sizeof(short int), 1, pfile);
	fread(&uselessInt, sizeof(short int), 1, pfile);


	fread(&imageWidth, sizeof(short int), 1, pfile);
	fread(&imageHeight, sizeof(short int), 1, pfile);

	fread(&bitCount, sizeof(unsigned char), 1, pfile);

   fread(&uselessChar, sizeof(unsigned char), 1, pfile);

	colorMode = bitCount / 8;

	tgaSize = imageWidth * imageHeight * colorMode;

   image = new unsigned char[sizeof(unsigned char) * tgaSize];

	fread(image, sizeof(unsigned char), tgaSize, pfile);
	
	for (index = 0; index < tgaSize; index += colorMode)
	   {
		   tempColor = image[index];
		   image[index] = image[index + 2];
		   image[index + 2] = tempColor;
	   }

	fclose(pfile);

   if(bitCount == 32)
      type = GL_RGBA;
   else
      type = GL_RGB;

	return true;
}


unsigned char* CTexture::LoadBitmapCK(char *file, BITMAPINFOHEADER *bitmapInfoHeader,int positi,GLubyte ra,GLubyte ga,GLubyte ba)
{
	FILE *pFile;                 
	BITMAPFILEHEADER	header;  
	GLubyte lr,lg,lb,la;
	unsigned char *textureData;   
	unsigned int RGBASize;


	pFile = fopen(file, "rb");   

	if(pFile == 0) return NULL; 

	fseek(pFile,positi,0);
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);
	
	if(header.bfType != BITMAP_ID)
	   {
		   fclose(pFile);
		   return 0;
	   }

	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

   if(bitmapInfoHeader->biSizeImage == 0)
      bitmapInfoHeader->biSizeImage = bitmapInfoHeader->biWidth * bitmapInfoHeader->biHeight * 3;
	RGBASize = bitmapInfoHeader->biWidth * bitmapInfoHeader->biHeight * 4;
	fseek(pFile, positi + header.bfOffBits, SEEK_SET);

	textureData = new unsigned char[RGBASize];

	if(!textureData)
	   {
		   delete[] textureData;
		   fclose(pFile);
		   return 0;
	   }

	for (unsigned long y=0; y < RGBASize; y+=4)
	{
		fread(&lb, 1, 1, pFile);
		fread(&lg, 1, 1, pFile);
		fread(&lr, 1, 1, pFile);
			if ( lr == ra && lg == ga && lb == ba)
			{
				la = 0;
			}else{
				la = 255;	
			};
		textureData[y]		= lr;
		textureData[y+1]	= lg;
		textureData[y+2]	= lb;
		textureData[y+3]	= la;
	};

	if(textureData == 0)
	   {
		   fclose(pFile);
		   return 0;
	   }


	type = GL_RGBA;

	fclose(pFile);  
	return textureData;  
}

unsigned char* CTexture::LoadBitmap(char *file, BITMAPINFOHEADER *bitmapInfoHeader,int positi)
{
	FILE *pFile;                
	BITMAPFILEHEADER	header;    

	unsigned char *textureData;  

 
	unsigned char textureColors;

	pFile = fopen(file, "rb");   

	if(pFile == 0) return NULL;   


	fseek(pFile,positi,0);
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);
	
	if(header.bfType != BITMAP_ID)
	   {
		   fclose(pFile);
		   return 0;
	   }

	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

   if(bitmapInfoHeader->biSizeImage == 0)
      bitmapInfoHeader->biSizeImage = bitmapInfoHeader->biWidth * bitmapInfoHeader->biHeight * 3;

	fseek(pFile, positi + header.bfOffBits, SEEK_SET);

	textureData = new unsigned char[bitmapInfoHeader->biSizeImage];

	if(!textureData)
	   {
		   delete[] textureData;
		   fclose(pFile);
		   return 0;
	   }

	fread(textureData, 1, bitmapInfoHeader->biSizeImage, pFile);

	if(textureData == 0)
	   {
		   fclose(pFile);
		   return 0;
	   }

	for(int index = 0; index < (int)bitmapInfoHeader->biSizeImage; index+=3)
	   {
		   textureColors = textureData[index];
		   textureData[index] = textureData[index + 2];
		   textureData[index + 2] = textureColors;
	   }

	type = GL_RGB;

	fclose(pFile);     
	return textureData;  
}

bool CTexture::LoadPcx(char *file)
{
   FILE *fp = 0;
   int temp = 0;
   int index = 0;
   int numRepeat = 0;
   unsigned char xMin = 0;
	unsigned char yMin = 0;
	unsigned char xMax = 0;
	unsigned char yMax = 0;

   if(file == 0) return false;

   fp = fopen(file, "rb");

   if(!fp) return 0;

   temp = getc(fp);

   if(temp != 10)
      {
         fclose(fp);
         return false;
      }

   temp = getc(fp);

   if(temp != 5)
      {
         fclose(fp);
         return false;
      }

   fgetc(fp);
   fgetc(fp);

   xMin = fgetc(fp); xMin |= fgetc(fp) << 8;
   yMin = fgetc(fp); yMin |= fgetc(fp) << 8;
   xMax = fgetc(fp); xMax |= fgetc(fp) << 8;
   yMax = fgetc(fp); yMax |= fgetc(fp) << 8;

   imageWidth = xMax - xMin + 1; imageHeight = yMax - yMin + 1;

   image = new unsigned char[imageWidth * imageHeight];

   fseek(fp, 128, SEEK_SET);

   while(index < (imageWidth * imageHeight))
      {
         temp = getc(fp);

         if(temp > 0xbf)
            {
               numRepeat = 0x3f & temp;
               
               temp = getc(fp);

               for(int i = 0; i < numRepeat; i++)
                  {
                     image[index++] = temp;
                  }
            }
         else
            {
               image[index++] = temp;
            }

         fflush(stdout);
      }

   palette = new unsigned char[768];

   fseek(fp, -769, SEEK_END);

   temp = getc(fp);

   if(temp != 12)
      {
         fclose(fp);
         return false;
      }

   for(int i = 0; i < 768; i++)
      {
         temp = getc(fp);
         palette[i] = temp;
      }

   fclose(fp);

   unsigned char *unscaledImage;
   int width = 0, height = 0;

   unscaledImage = new unsigned char[imageWidth * imageHeight * 4];
   for(i = 0; i < imageHeight; i++)
      {
         for(int j = 0; j < imageWidth; j++)
            {
               unscaledImage[4 * (i * imageWidth + j) + 0] = 
                             (unsigned char)palette[3 * image[i * imageWidth + j] + 0];

               unscaledImage[4 * (i * imageWidth + j) + 1] = 
                             (unsigned char)palette[3 * image[i * imageWidth + j] + 1];

               unscaledImage[4 * (i * imageWidth + j) + 2] = 
                             (unsigned char)palette[3 * image[i * imageWidth + j] + 2];

               unscaledImage[4 * (i * imageWidth + j) + 3] = (unsigned char)255;
            }
      }

   width = imageWidth;
   height = imageHeight;

   int w = 0;
   while(width)
      {
         width /= 2;
         w++;
      }

   long int scaledHeight = (long)pow(2, w - 1);

   int h = 0;
   while(height)
      {
         height /= 2;
         h++;
      }

   long int scaledWidth = (long)pow(2, h - 1);
   if(image != 0)
      {
         delete[] image;
         image = 0;
      }

   image = new unsigned char[scaledWidth * scaledHeight * 4];

   gluScaleImage(GL_RGBA, imageWidth, imageHeight, GL_UNSIGNED_BYTE, unscaledImage, scaledWidth,
                 scaledHeight, GL_UNSIGNED_BYTE, image);

   if(unscaledImage != 0)
      {
         delete[] unscaledImage;
         unscaledImage = 0;
      }

   type = GL_RGBA;

   return true;
}


bool CTexture::CreateImage(int w, int h, int b)
{
   if(b == 24)
      type = GL_RGB;
   else if(b == 32)
      type = GL_RGBA;
   else
      type = GL_LUMINANCE;

   image = new unsigned char[w * h * (b / 8)];
   imageWidth = w;
   imageHeight = h;
   textureExist = true;

   return true;
}


void CTexture::GetColor(unsigned int x, unsigned int y, unsigned char *pR, unsigned char *pG, unsigned char* pB)
{
   int index = 0;
	unsigned int bits = type / 8;

   if(image == 0)
      return;

	if(((int)x < imageWidth) && ((int)y < imageHeight))
      {
         index = ((y * imageHeight) + x) * bits;
         *pR = image[index];
         *pG = image[index + 1];
         *pB = image[index + 2];
      }
}


void CTexture::SetColor(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
{
   unsigned int bits = type / 8;

   if(((int)x < imageWidth) && ((int)y < imageHeight))
      {
         image[((y * imageHeight) + x) * bits] = r;
         image[((y * imageHeight) + x) * bits + 1] = g;
         image[((y * imageHeight) + x) * bits + 2] = b;
      }
}


bool CTexture::WriteBMP(char *file, int width, int height, unsigned char *output)
{
   FILE *pFile = 0;             
   BITMAPINFOHEADER infoHeader; 
   BITMAPFILEHEADER fileHeader; 
   int index = 0;                
   unsigned char tempColors = 0; 

   pFile = fopen(file, "wb");   
   if(!pFile) return false;

   infoHeader.biSize          = sizeof(BITMAPINFOHEADER);
   infoHeader.biPlanes        = 1;
   infoHeader.biBitCount      = 24;
   infoHeader.biCompression   = BI_RGB;
   infoHeader.biSizeImage     = width * abs(height) * 3;
   infoHeader.biXPelsPerMeter = 0;
   infoHeader.biYPelsPerMeter = 0;
   infoHeader.biClrUsed       = 0;
   infoHeader.biClrImportant  = 0;
   infoHeader.biWidth         = width;
   infoHeader.biHeight        = height;

   fileHeader.bfSize       = sizeof(BITMAPFILEHEADER);
   fileHeader.bfType       = 0x4D42;
   fileHeader.bfReserved1  = 0;
   fileHeader.bfReserved2  = 0;
   fileHeader.bfOffBits    = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


   for(index = 0; index < (int)infoHeader.biSizeImage; index += 3)
      {
         tempColors = output[index];
         output[index] = output[index + 2];
         output[index + 2] = tempColors;
      }

   fwrite(&fileHeader, 1, sizeof(BITMAPFILEHEADER), pFile);

   fwrite(&infoHeader, 1, sizeof(BITMAPINFOHEADER), pFile);

   fwrite(output, 1, infoHeader.biSizeImage, pFile);

   fclose(pFile);

   return true;
}


bool CTexture::WriteTGA(char *file, short int width, short int height, unsigned char *outImage)
{
   FILE *pFile = 0;                
   unsigned char uselessChar = 0;  
   short int uselessInt = 0;   
   unsigned char imageType = 0;   
   int index = 0;            
   unsigned char bits = 0;         
   long Size = 0;               
   int colorMode = 0;             
   unsigned char tempColors = 0;    

   pFile = fopen(file, "wb");

   if(!pFile) { fclose(pFile); return false; }

   imageType = 2; colorMode = 3; bits = 24;

   fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);
   fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);

   fwrite(&imageType, sizeof(unsigned char), 1, pFile);

   fwrite(&uselessInt, sizeof(short int), 1, pFile);
   fwrite(&uselessInt, sizeof(short int), 1, pFile);
   fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);
   fwrite(&uselessInt, sizeof(short int), 1, pFile);
   fwrite(&uselessInt, sizeof(short int), 1, pFile);

   fwrite(&width, sizeof(short int), 1, pFile);
   fwrite(&height, sizeof(short int), 1, pFile);
   fwrite(&bits, sizeof(unsigned char), 1, pFile);

   fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);

   Size = width * height * colorMode;

   for(index = 0; index < Size; index += colorMode)
      {
         tempColors = outImage[index];
         outImage[index] = outImage[index + 2];
         outImage[index + 2] = tempColors;
      }

   fwrite(outImage, sizeof(unsigned char), Size, pFile);

   fclose(pFile);

   return true;
}


void CTexture::SaveBMPScreenShot(char *filename, int w, int h)
{
   unsigned char *outputImage = 0;

   outputImage = new unsigned char[w * h * 3];

   memset(outputImage, 0, w * h * 3);

   glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, outputImage);

   WriteBMP(filename, w, h, (unsigned char*)outputImage);

   delete[] outputImage;
}


void CTexture::EnvironmentMap(int w, int h)
{

   image = new unsigned char[w * h * 3];

   memset(image, 0, w * h * 3);

   glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	type = GL_RGB;
   GenerateTexture();

}

void CTexture::SaveTGAScreenShot(char *filename, int w, int h)
{
   unsigned char *outputImage = 0;

   outputImage = new unsigned char[w * h * 3];

   memset(outputImage, 0, w * h * 3);

   glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, outputImage);

   WriteTGA(filename, w, h, (unsigned char*)outputImage);

   delete[] outputImage;
}


void CTexture::FreeImage()
{
   if(image)
      {
         delete[] image;
         image = 0;
      }

   if(palette)
      {
         delete[] palette;
         palette = 0;
      }

   textureExist = false;
   type = 0;
}


