#include "cmodify.h"


void IModel::CalculateNormals()
{
	for(int zak=0;zak<IM3Header.objectcount;zak++)
	{
		vector3f *s;
		s = new vector3f [IM3Mesh[zak].facecount];

		IM3Mesh[zak].hx.Resize(IM3Mesh[zak].facecount*3);
		IM3Mesh[zak].hy.Resize(IM3Mesh[zak].facecount*3);
		IM3Mesh[zak].hz.Resize(IM3Mesh[zak].facecount*3);

		int tra=0;

		for(int i=0;i<IM3Mesh[zak].facecount;i++)
		{
			vector3f t1,t2,t3;
			vector3f s1,s2;
			vector3f v;
			t1.x = IM3Mesh[zak].mx[IM3Mesh[zak].v1[i]];
			t1.y = IM3Mesh[zak].my[IM3Mesh[zak].v1[i]];
			t1.z = IM3Mesh[zak].mz[IM3Mesh[zak].v1[i]];

			t2.x = IM3Mesh[zak].mx[IM3Mesh[zak].v2[i]];
			t2.y = IM3Mesh[zak].my[IM3Mesh[zak].v2[i]];
			t2.z = IM3Mesh[zak].mz[IM3Mesh[zak].v2[i]];

			t3.x = IM3Mesh[zak].mx[IM3Mesh[zak].v3[i]];
			t3.y = IM3Mesh[zak].my[IM3Mesh[zak].v3[i]];
			t3.z = IM3Mesh[zak].mz[IM3Mesh[zak].v3[i]];
			
			s1 = t2 - t1;
			s2 = t3 - t1;
			v = cross(s1,s2);
			v.normalize();
			s[i] = v;
			//IM3Mesh[zak].hx[tra] = v.x;
			//IM3Mesh[zak].hy[tra] = v.y;
			//IM3Mesh[zak].hz[tra] = v.z;

			tra++;
		}
		tra =0;
		for (i=0;i<IM3Mesh[zak].facecount;i++)
		{
			int t1,t2,t3;
			t1 = IM3Mesh[zak].v1[i];
			t2 = IM3Mesh[zak].v2[i];
			t3 = IM3Mesh[zak].v3[i];

			vector3f n1,n2,n3;
			int s1,s2,s3;
			s1 = s2 = s3 = 0;
			for (int l=0;l<IM3Mesh[zak].facecount;l++)
			{
				int k1,k2,k3;
				k1 = IM3Mesh[zak].v1[l];
				k2 = IM3Mesh[zak].v2[l];
				k3 = IM3Mesh[zak].v3[l];
				
				if ((k1 == t1) || (k2 == t1) || (k3 == t1) )
				{
					s1++;
					n1 += s[l];
				}
				if ((k1 == t2) || (k2 == t2) || (k3 == t2) )
				{
					s2++;
					n2 += s[l];
				}
				if ((k1 == t3) || (k2 == t3) || (k3 == t3) )
				{
					s3++;
					n3 += s[l];
				}
			}

			n1.normalize();
			n2.normalize();
			n3.normalize();
			IM3Mesh[zak].hx[tra] = n1.x;
			IM3Mesh[zak].hy[tra] = n1.y;
			IM3Mesh[zak].hz[tra] = n1.z;

			IM3Mesh[zak].hx[tra+1] = n2.x;
			IM3Mesh[zak].hy[tra+1] = n2.y;
			IM3Mesh[zak].hz[tra+1] = n2.z;

			IM3Mesh[zak].hx[tra+2] = n3.x;
			IM3Mesh[zak].hy[tra+2] = n3.y;
			IM3Mesh[zak].hz[tra+2] = n3.z;

			tra+=3;
		}
	}
}