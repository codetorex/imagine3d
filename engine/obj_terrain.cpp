#include "cobject.h"

void ITile::CreateTile(IBitmap &bitms)
{
	IM3Header.objectcount = 1;
	IM3Mesh = new IM3Object[1];
	
	int square = bitms.bw * bitms.bh;
	int faces = (bitms.bw - 1) * (bitms.bh -1) * 2;
	IM3Mesh[0].mx.Resize(square);
	IM3Mesh[0].my.Resize(square);
	IM3Mesh[0].mz.Resize(square);
	IM3Mesh[0].v1.Resize(faces);
	IM3Mesh[0].v2.Resize(faces);
	IM3Mesh[0].v3.Resize(faces);
	IM3Mesh[0].tu.Resize(square);
	IM3Mesh[0].tv.Resize(square);
	IM3Mesh[0].t1.Resize(faces);
	IM3Mesh[0].t2.Resize(faces);
	IM3Mesh[0].t3.Resize(faces);
	IM3Mesh[0].mat.Resize(faces);
	for (int i=0;i<faces;i++)
	{
		IM3Mesh[0].mat[i] = 0;
	}


	IM3Mesh[0].facecount = faces;
	IM3Mesh[0].vertcount = square; 
	bitms.monochrome();
	//return (8 * y) + x;
	c24b cs;
	float car;
	car = 1/(float)bitms.bw;

	for (int h=0;h<bitms.bh;h++)
	{
		for(int w=0;w<bitms.bw;w++)
		{
			// add vertexs
			cs = bitms.getpixel(w+1,h+1);
			IM3Mesh[0].mx[(bitms.bw*h)+w] = (float)(w) * 0.1f;
			IM3Mesh[0].my[(bitms.bw*h)+w] = (float)(cs.r/255.0f);
			IM3Mesh[0].mz[(bitms.bw*h)+w] = (float)(h)*0.1f;
			IM3Mesh[0].tu[(bitms.bw*h)+w] = (float)(w*car);
			IM3Mesh[0].tv[(bitms.bw*h)+w] = (float)(-h*car);

		}
	}

	int fac=0;
	
	for (h=0;h<bitms.bh-1;h++)
	{
		for(int w=0;w<bitms.bw-1;w++)
		{	
			// add faces
			IM3Mesh[0].v1[fac] = (bitms.bw*h)+w;
			IM3Mesh[0].v2[fac] = (bitms.bw*(h+1))+w;
			IM3Mesh[0].v3[fac] = (bitms.bw*h)+w+1;

			IM3Mesh[0].v1[fac+1] = (bitms.bw*(h+1))+w;
			IM3Mesh[0].v2[fac+1] = (bitms.bw*(h+1))+w+1;
			IM3Mesh[0].v3[fac+1] = (bitms.bw*h)+w+1;
			
			// set texture coords
			IM3Mesh[0].t1[fac] = (bitms.bw*h)+w;
			IM3Mesh[0].t2[fac] = (bitms.bw*(h+1))+w;
			IM3Mesh[0].t3[fac] = (bitms.bw*h)+w+1;

			IM3Mesh[0].t1[fac+1] = (bitms.bw*(h+1))+w;
			IM3Mesh[0].t2[fac+1] = (bitms.bw*(h+1))+w+1;
			IM3Mesh[0].t3[fac+1] = (bitms.bw*h)+w+1;


			fac+=2;
		}		
	}
}
