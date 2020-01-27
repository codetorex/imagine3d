#include "cmodify.h"

void IModel::CalculateTangentSpace()
{
	for (int i=0;i<IM3Header.objectcount;i++)
	{
		IM3Mesh[i].TBN_Tangent = new vector3f [IM3Mesh[i].vertcount];
		IM3Mesh[i].TBN_Binormal = new vector3f [IM3Mesh[i].vertcount];
		IM3Mesh[i].TBN_Normal = new vector3f [IM3Mesh[i].vertcount];
		
		for (int f=0;f<IM3Mesh[i].facecount;f++)
		{
			// Load Veretexs
			vector3f v0,v1,v2;
			vector3f t0,t1,t2;
			vector3f norm,tang,bino;
			v0.x = IM3Mesh[i].mx[IM3Mesh[i].v1[f]];
			v0.y = IM3Mesh[i].my[IM3Mesh[i].v1[f]];
			v0.z = IM3Mesh[i].mz[IM3Mesh[i].v1[f]];

			v1.x = IM3Mesh[i].mx[IM3Mesh[i].v2[f]];
			v1.y = IM3Mesh[i].my[IM3Mesh[i].v2[f]];
			v1.z = IM3Mesh[i].mz[IM3Mesh[i].v2[f]];

			v2.x = IM3Mesh[i].mx[IM3Mesh[i].v3[f]];
			v2.y = IM3Mesh[i].my[IM3Mesh[i].v3[f]];
			v2.z = IM3Mesh[i].mz[IM3Mesh[i].v3[f]];

			t0.x = IM3Mesh[i].tu[IM3Mesh[i].t1[f]];
			t0.y = IM3Mesh[i].tv[IM3Mesh[i].t1[f]];

			t1.x = IM3Mesh[i].tu[IM3Mesh[i].t2[f]];
			t1.y = IM3Mesh[i].tv[IM3Mesh[i].t2[f]];
		
			t2.x = IM3Mesh[i].tu[IM3Mesh[i].t3[f]];
			t2.y = IM3Mesh[i].tv[IM3Mesh[i].t3[f]];

			vector3f side0,side1;
			side0 =v0-v1;
			side1 =v2-v1;
			norm=cross(side0,side1);
			norm.normalize();

			float deltaT0,deltaT1;
			deltaT0=t0.y-t1.y;
			deltaT1=t2.y-t1.y;
			tang = side0*deltaT1-side1*deltaT0;
			tang.normalize();

			float deltaS0,deltaS1;
			deltaS0=t0.x - t1.x;
			deltaS1=t2.x - t1.x;
			bino=side0*deltaS1 - side1*deltaS0;
			bino.normalize();

			vector3f tangcro;
			tangcro=cross(tang,bino);
			if(dot(tangcro,norm)<0.0f)
			{
				tang=-tang;
				bino=-bino;
			}

			IM3Mesh[i].TBN_Tangent[IM3Mesh[i].v1[f]] += tang;
			IM3Mesh[i].TBN_Tangent[IM3Mesh[i].v2[f]] += tang;
			IM3Mesh[i].TBN_Tangent[IM3Mesh[i].v3[f]] += tang;

			IM3Mesh[i].TBN_Binormal[IM3Mesh[i].v1[f]] += bino;
			IM3Mesh[i].TBN_Binormal[IM3Mesh[i].v2[f]] += bino;
			IM3Mesh[i].TBN_Binormal[IM3Mesh[i].v3[f]] += bino;

			IM3Mesh[i].TBN_Normal[IM3Mesh[i].v1[f]] += norm;
			IM3Mesh[i].TBN_Normal[IM3Mesh[i].v2[f]] += norm;
			IM3Mesh[i].TBN_Normal[IM3Mesh[i].v3[f]] += norm;


			
		}
		
		for (long l=0;l<IM3Mesh[i].vertcount;l++)
		{
			IM3Mesh[i].TBN_Tangent[l].normalize();
			IM3Mesh[i].TBN_Binormal[l].normalize();
			IM3Mesh[i].TBN_Normal[l].normalize();
		}
	}
}