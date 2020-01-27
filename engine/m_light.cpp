#include "cmodify.h"

/*
void IModel::CalculateLightMaps(long size)
{
// First Sub Divide Mesh

long v1,v2,v3;
vector3f t0,t1,t2;
float area;
float e1,e2,e3;
long state;

vector3f* st1;
vector3f* st2;
vector3f* st3;

st1 = new vector3f [size];
st2 = new vector3f [size];
st3 = new vector3f [size];

float stp;
vector3f temp;
tco = 0;
float k;

	for (long o=0;o<IM3Header.objectcount;o++)
	{
		for(long f=0;f<IM3Mesh[o].facecount;f++)
		{
			v1=IM3Mesh[o].v1[f];
			v2=IM3Mesh[o].v2[f];
			v3=IM3Mesh[o].v3[f];
			t0.set(IM3Mesh[o].mx[v1],IM3Mesh[o].my[v1],IM3Mesh[o].mz[v1]);
			t1.set(IM3Mesh[o].mx[v2],IM3Mesh[o].my[v2],IM3Mesh[o].mz[v2]);
			t2.set(IM3Mesh[o].mx[v3],IM3Mesh[o].my[v3],IM3Mesh[o].mz[v3]);
			temp = cross(t1-t0,t2-t0);
			area = 0.5f * ( temp.length() );

			e1 = vecdist(t0,t1);
			e2 = vecdist(t0,t2);
			e3 = vecdist(t1,t2);

			if (e1 >= e2 && e1 >= e3 ) state = 1;
			if (e2 >= e1 && e2 >= e3 ) state = 2;
			if (e3 >= e1 && e3 >= e2 ) state = 3;

			for (int i=1;i<size;i++)
			{
				//st1[i] = eline(t0,t1,(float)(i)*stp);
				//st2[i] = eline(t0,t2,(float)(i)*stp);
				//st3[i] = eline(t1,t2,(float)(i)*stp);
				k = float(i) / float(size-i);
				st1[i].x = (t0.x + (k * t1.x)) / (1 + k);
				st1[i].y = (t0.y + (k * t1.y)) / (1 + k);
				st1[i].z = (t0.z + (k * t1.z)) / (1 + k);

				st2[i].x = (t0.x + (k * t2.x)) / (1 + k);
				st2[i].y = (t0.y + (k * t2.y)) / (1 + k);
				st2[i].z = (t0.z + (k * t2.z)) / (1 + k);

				st3[i].x = (t1.x + (k * t2.x)) / (1 + k);
				st3[i].y = (t1.y + (k * t2.y)) / (1 + k);
				st3[i].z = (t1.z + (k * t2.z)) / (1 + k);

				zx.AddElement(st1[i].x);
				zy.AddElement(st1[i].y);
				zz.AddElement(st1[i].z);

				zx.AddElement(st2[i].x);
				zy.AddElement(st2[i].y);
				zz.AddElement(st2[i].z);

				zx.AddElement(st3[i].x);
				zy.AddElement(st3[i].y);
				zz.AddElement(st3[i].z);

				tco +=3;
			}


		}
	}


}
*/

void IModel::CalculateLightMaps(long size)
{
// First Sub Divide Mesh

long v1,v2,v3,k1,k2,k3;
vector3f t[3],p1,p2,p3;
float area;
float e1,e2,e3;
long state;

vector3f st[3];
vector3f tr[3];

vector3f temp;
tco = 0;
IM3Object* otem;
otem = new IM3Object [IM3Header.objectcount];
for (int i=0;i<IM3Header.objectcount;i++)
{
	otem[i].vertcount = IM3Mesh[i].vertcount * 2;
	otem[i].facecount = IM3Mesh[i].facecount * 4;
	otem[i].tvcount = 1;
	otem[i].tu.AddElement(0);
	otem[i].tv.AddElement(0);

}

	for (long o=0;o<IM3Header.objectcount;o++)
	{
		for(long f=0;f<IM3Mesh[o].facecount;f++)
		{
			v1=IM3Mesh[o].v1[f];
			v2=IM3Mesh[o].v2[f];
			v3=IM3Mesh[o].v3[f];
			k1=IM3Mesh[o].t1[f];
			k2=IM3Mesh[o].t2[f];
			k3=IM3Mesh[o].t3[f];

			t[0].set(IM3Mesh[o].mx[v1],IM3Mesh[o].my[v1],IM3Mesh[o].mz[v1]);
			t[1].set(IM3Mesh[o].mx[v2],IM3Mesh[o].my[v2],IM3Mesh[o].mz[v2]);
			t[2].set(IM3Mesh[o].mx[v3],IM3Mesh[o].my[v3],IM3Mesh[o].mz[v3]);
			p1.set(IM3Mesh[0].tu[k1],IM3Mesh[0].tv[k1],0);
			p2.set(IM3Mesh[0].tu[k2],IM3Mesh[0].tv[k2],0);
			p3.set(IM3Mesh[0].tu[k3],IM3Mesh[0].tv[k3],0);

			temp = cross(t[1]-t[0],t[2]-t[0]);
			area = 0.5f * ( temp.length() );



			st[0] = (t[0] + t[1]) * 0.5f;
			st[1] = (t[0] + t[2]) * 0.5f;
			st[2] = (t[1] + t[2]) * 0.5f;

			// Orginal Vertexs
			otem[o].mx.AddElement(t[0].x);
			otem[o].my.AddElement(t[0].y);
			otem[o].mz.AddElement(t[0].z);

			otem[o].mx.AddElement(t[1].x);
			otem[o].my.AddElement(t[1].y);
			otem[o].mz.AddElement(t[1].z);

			otem[o].mx.AddElement(t[2].x);
			otem[o].my.AddElement(t[2].y);
			otem[o].mz.AddElement(t[2].z);

			// Artifical Vertexes
			otem[o].mx.AddElement(st[0].x);
			otem[o].my.AddElement(st[0].y);
			otem[o].mz.AddElement(st[0].z);

			otem[o].mx.AddElement(st[1].x);
			otem[o].my.AddElement(st[1].y);
			otem[o].mz.AddElement(st[1].z);

			otem[o].mx.AddElement(st[2].x);
			otem[o].my.AddElement(st[2].y);
			otem[o].mz.AddElement(st[2].z);

			// Adding Faces
			int r;
			r = f*6;

			for (int i=0;i<3;i++)
			{
				e1 = vecdist(t[i],st[0]);
				e2 = vecdist(t[i],st[1]);
				e3 = vecdist(t[i],st[2]);
				
				otem[o].v1.AddElement(r+i);
				otem[o].v2.AddElement(r+i);
				otem[o].v3.AddElement(r+i);

				if ( e1 >= e2 || e1 >= e3 )
				{
					otem[o].v1.AddElement(r+3);
					otem[o].v2.AddElement(r+3);
					otem[o].v3.AddElement(r+3);		
				}
				if ( e2 >= e1 || e2 >= e3 )
				{
					otem[o].v1.AddElement(r+4);
					otem[o].v2.AddElement(r+4);
					otem[o].v3.AddElement(r+4);		
				}
				if ( e3 >= e1 || e3 >= e2 )
				{
					otem[o].v1.AddElement(r+5);
					otem[o].v2.AddElement(r+5);
					otem[o].v3.AddElement(r+5);		
				}


			}


			
			
			otem[o].mat.AddElement(IM3Mesh[o].mat[r]);
			otem[o].mat.AddElement(IM3Mesh[o].mat[r]);
			otem[o].mat.AddElement(IM3Mesh[o].mat[r]);
			otem[o].mat.AddElement(IM3Mesh[o].mat[r]);


			

			otem[o].t1.AddElement(0);
			otem[o].t2.AddElement(0);
			otem[o].t3.AddElement(0);

			otem[o].t1.AddElement(0);
			otem[o].t2.AddElement(0);
			otem[o].t3.AddElement(0);

			otem[o].t1.AddElement(0);
			otem[o].t2.AddElement(0);
			otem[o].t3.AddElement(0);

			otem[o].t1.AddElement(0);
			otem[o].t2.AddElement(0);
			otem[o].t3.AddElement(0);

		
		}
	}
delete [] IM3Mesh;
IM3Mesh = otem;
CalculateNormals();

}