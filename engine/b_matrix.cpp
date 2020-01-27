#include "cbitmap.h"

void IBitmap::matrixmul(float m[],int mw,int mh,bool mabs)
{
	int sumr=0;
	int sumg=0;
	int sumb=0;

	int i,j,k,l;
	int iix,iiy;
	int teas;

	IBitmap tempb;
	tempb.createbitmap(bw,bh);
//	int ast;
	c24b color;

//	mini = new byte [mw*mh*3];

	int suma=0;
	for (i = 0;i<mw*mh;i++)
	{
		suma+= m[i];
	}
	if (suma == 0) suma = 1;
//	cout << suma;

	for (i=1;i<bw+1;i++){
		for (j=1;j<bh+1;j++){
			for (k=1;k<mw+1;k++){
				for (l=1;l<mh+1;l++){
					iix = i + k-1;
					iiy = j + l-1;
					if (iix > bw) iix = bw-1;
					if (iiy > bh) iiy = bh-1;

					color = getpixel(iix,iiy);
					teas = ((k-1)*mw) + (l -1);
					sumr += color.r * m[teas];
					sumg += color.g * m[teas];
					sumb += color.b * m[teas];
					//cout << m[teas] << endl;
	
				}
			}
			sumr /= suma;
			sumg /= suma;
			sumb /= suma;
			if (mabs)
			{
				sumr = abs(sumr);
				sumg = abs(sumg);
				sumb = abs(sumb);
			}
			else
			{
				if (sumr < 0) sumr = 0;
				if (sumg < 0) sumg = 0;
				if (sumb < 0) sumb = 0;
			}
			if (sumr > 255) sumr = 255;
			if (sumg > 255) sumg = 255;
			if (sumb > 255) sumb = 255;


			tempb.setpixel(i,j,m24b(sumr,sumg,sumb));
			sumr = sumg = sumb = 0;
		}
	}

	memcpy(bytes,tempb.bytes,total);


}

void IBitmap::sharpen()
{
	float mymat [] = { 0,-1,0,-1,5,-1,0,-1,0};
	matrixmul(mymat,3,3,false);
}

void IBitmap::emboss()
{
	float mymat [] = {3,0,0,0,-1,0,0,0,-1 }; // Emboss
	matrixmul(mymat,3,3,false);
}

void IBitmap::edged()
{
	float mymat [] = {-1,-1,-1,0,0,0,1,1,1};
	matrixmul(mymat,3,3,false);
}

void IBitmap::blur()
{
	float mymat [] = { 1,2,1,2,4,2,1,2,1};
	matrixmul(mymat,3,3,false);
}