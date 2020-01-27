#include "stdafx.h"
#include "exporter.h"
/*
Old Version
void MyExporter::CalculateVertexLight()
{
	// vertex color = 255 - ( (Noktanin isiga uzakligi / isikigin maksimum uzakligi) * isik rengi )
	// isik siddeti = (I / d^2) * cos(alfa)  // alfa = isik ile normal arasindaki aci
	// I = isigin ampiludutesi d^2 = isigin uzakligi
	float tns,tne;
	float tlx,tly,tlz;
	float vx,vy,vz;
	float dx,dy,dz,dist;
	float alfa;
	unsigned char tlr,tlg,tlb;
	float calr,calg,calb;
	Point3 fa1,fa2; // find alfa 1-2
	float la1,la2;
	float al;
	float E,I;

	if (curl != 0 )
	{
		for (int l=0;l<curl;l++) // HER ISIK ICIN AYRI HESAP
		{
			if (lc[l].lighttype == 0) // eger omni isik ise
			{
				tns = lc[l].atten[0];tne = lc[l].atten[1]; // isigin calisma alani
				tlx = lc[l].lmatrix[9];tly = lc[l].lmatrix[11];tlz = -lc[l].lmatrix[10]; // isigin posizyonu
				fa1.x = tlx;fa1.y = tly;fa1.z =tlz;
				//tlr = lc[l].r;tlg = lc[l].g;tlb = lc[l].b;
				for(int o=0;o<curo;o++)
				{
					for(int v=0;v<oc[o].vertcount;v++)
					{
						vx = oc[o].mx[v];vy = oc[o].my[v];vz = oc[o].mz[v];
						fa2.x = oc[o].hx[v];fa2.y = oc[o].hy[v]; fa2.z = oc[o].hz[v];
						la1 = sqrt(tlx*tlx + tly*tly + tlz*tlz);
						la2 = sqrt(fa2.x*fa2.x + fa2.y*fa2.y + fa2.z*fa2.z);
						dx = tlx - vx;dy = tly - vy;dz = tlz - vz;
						dist = (float)sqrt( (dx*dx) + (dy*dy) + (dz*dz));
						if (dist < tne && dist > tns) // eger nokta baslangic ile bitis arasinda ise
						{
							//al = (lc[l].r + lc[l].g + lc[l].b) / 3;
							alfa = dotp(fa1,fa2) / (la1 * la2);
							//I = (al * 45) / (4*PI); // al watt
							//E = (I / (dist*dist)) * alfa;
							// I = lum / 4pi
							// E = I / d^2 * cos(alfa)
							
							calr = (dist/tne) * (lc[l].r);
							calg = (dist/tne) * (lc[l].g);
							calb = (dist/tne) * (lc[l].b);
							// I / d^2 * cos(alfa)						
							
							tlr = 255-calr; // 128 for ambience
							tlg = 255-calg;
							tlb = 255-calb;

							if (tlr > 255) tlr = 191;
							if (tlg > 255) tlr = 191;
							if (tlb > 255) tlr = 191;

							tlr +=64;
							tlg +=64;
							tlb +=64;
							


							oc[o].cr[v] = tlr * alfa;
							oc[o].cg[v] = tlg* alfa;
							oc[o].cb[v] = tlb* alfa;

							/*oc[o].cr[v]=tlr;
							oc[o].cg[v]=tlg;
							oc[o].cb[v]=tlb;*//*
						}
						
					}//close vertex icin
				}//close obje icin
			}//close light type check
		} // close isik icin
	} // close if curl != 0

}*/

void MyExporter::CalculateVertexLight()
{
	Point3 l0; // light position
	Point3 v0,v1,v2; // vector position
	Point3 n0,n1,n2; // vector normal
	Point3 q1,q2,q3;
	float l1,l2,l3; // length
	Point3 s1,s2,s3;
	float f1,f2,f3; // factors
	unsigned char lr,lg,lb;
	int vn;
	if (curl != 0 )
	{
		for (int l=0;l<curl;l++) // HER ISIK ICIN AYRI HESAP
		{
			if (lc[l].lighttype == 0) // eger omni isik ise
			{
				l0.x = lc[l].lmatrix[9];
				l0.y = lc[l].lmatrix[11];
				l0.z = -lc[l].lmatrix[10];
				lr = lc[l].r;
				lg = lc[l].g;
				lb = lc[l].b;

				for(int o=0;o<curo;o++)
				{
					vn = 0;
					for(int v=0;v<oc[o].facecount;v++)
					{
						int h1 = oc[o].v1[v];
						int h2 = oc[o].v2[v];
						int h3 = oc[o].v3[v];

						v0.x = oc[o].mx[h1]; v0.y = oc[o].my[h1]; v0.z = oc[o].mz[h1];
						v1.x = oc[o].mx[h2]; v1.y = oc[o].my[h2]; v1.z = oc[o].mz[h2];
						v2.x = oc[o].mx[h3]; v2.y = oc[o].my[h3]; v2.z = oc[o].mz[h3];

						n0.x = oc[o].hx[vn+0]; n0.y = oc[o].hy[vn+0]; n0.z = oc[o].hz[vn+0];
						n1.x = oc[o].hx[vn+1]; n1.y = oc[o].hy[vn+1]; n1.z = oc[o].hz[vn+1];
						n2.x = oc[o].hx[vn+2]; n2.y = oc[o].hy[vn+2]; n2.z = oc[o].hz[vn+2];

						q1 = l0 - v0; q2 = l0 - v1; q3 = l0 - v2;
						l1 = sqrt((q1.x * q1.x) + (q1.y * q1.y) + (q1.z * q1.z));
						l2 = sqrt((q2.x * q2.x) + (q2.y * q2.y) + (q2.z * q2.z));
						l3 = sqrt((q3.x * q3.x) + (q3.y * q3.y) + (q3.z * q3.z));

						s1.x = q1.x / l1; s1.y = q1.y / l1; s1.z = q1.z / l1;
						s2.x = q2.x / l2; s2.y = q2.y / l2; s2.z = q2.z / l2;
						s3.x = q3.x / l3; s3.y = q3.y / l3; s3.z = q3.z / l3;

						f1 = dotp(s1,n0); f2 = dotp(s2,n1); f3 = dotp(s3,n2);
						if (f1 < 0) f1 = 0; if (f2 < 0) f2 = 0; if (f3 < 0) f3 = 0;
						
						oc[o].cr[vn+0] += (f1 * lr);
						oc[o].cg[vn+0] += (f1 * lg);
						oc[o].cb[vn+0] += (f1 * lb);

						oc[o].cr[vn+1] += (f2 * lr);
						oc[o].cg[vn+1] += (f2 * lg);
						oc[o].cb[vn+1] += (f2 * lb);

						oc[o].cr[vn+2] += (f3 * lr);
						oc[o].cg[vn+2] += (f3 * lg);
						oc[o].cb[vn+2] += (f3 * lb);
						vn +=3;
					}
				}
			}
		}
	}
}