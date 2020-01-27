#include "stdafx.h"
#include "exporter.h"

// « ¬ ó û ü ý è ° ± ² ³ ´ ¹ º » ¼ ¿ À Á Â Ã Ä Å È É Ê Ë Ì Í Î Ù Ú Û Ü ß æ ø õ Ï ¾ ½ ›

// FFS-SA (Face For Shadower - Shadowing Algorithm)
// Made by Burak575

void MyExporter::CalculateVertexShadows()
{
	int l,o,o2,v,f;
//		³ ³ ³  ³ ÀÄface for shadowed
// lightÙ ÃÄÙ  Àface for shadower
//        Àobjects
	int f0,f1,f2;		// Temporary face indices
	Point3 v0,v1,v2;	// face's vertexs.

	int f3,f4,f5;		// temp face indices 2
	Point3 v3,v4,v5;	// 2. indices's vertexs 

	Triangle ttri;		// a triangle
	Ray ry1,ry2,ry3;	// our rays
	Point3 r01,r02,r03;	// returned point
	Point3 cenf;
	int re1,re2,re3;	// results

	float ad01,ad02;	// average distances

	if (curl != 0)// is any light in scene?
	{
		for (l=0;l<curl;l++) // HER ISIK ICIN AYRI HESAP
		{
			if (lc[l].lighttype == 0) // eger omni isik ise
			{
//				tns = lc[l].atten[0];tne = lc[l].atten[1]; // isigin calisma alani // bu uygulamada kullanmicam
				ry1.p.x = lc[l].lmatrix[9];ry1.p.y = lc[l].lmatrix[11];ry1.p.z = -lc[l].lmatrix[10]; // isigin posizyonu
				//ry1.p = Ver2GL(ry1.p);
				ry2.p = ry1.p; ry3.p = ry1.p; // ray2 and ray3 is same with ray1 because light is coming form 1 point
				for(o=0;o<curo;o++) // her objenin 
				{
					for(v=0;v<oc[o].facecount;v++) // her facesi
					{
						f3 = oc[o].v1[v]; f4 = oc[o].v2[v]; f5 = oc[o].v3[v];
						v3.x = oc[o].mx[f3];v3.y = oc[o].my[f3];v3.z = oc[o].mz[f3];
						v4.x = oc[o].mx[f4];v4.y = oc[o].my[f4];v4.z = oc[o].mz[f4];
						v5.x = oc[o].mx[f5];v5.y = oc[o].my[f5];v5.z = oc[o].mz[f5];
						
						// TODO: make 100 radius of light
						ry1.dir = v3; // our 2x extended first light ray
						ry2.dir = v4; // our 2x extended second light ray
						ry3.dir = v5; // our 2x extended third light ray

						ad01 = (RayDistance(ry1) + RayDistance(ry2) + RayDistance(ry3)) / 3;

//						ry1.dir.x = oc[o].mx[v];ry1.dir.z = oc[o].my[v];ry1.dir.z = oc[o].mz[v]; // isiktan->vertexe ray
						for(o2=0;o2<curo;o2++)// bu ray diger objenin
						{
							for (f=0;f<oc[o2].facecount;f++) // her facesini
							{
								f0 = oc[o2].v1[f];f1 = oc[o2].v2[f];f2 = oc[o2].v3[f];
								v0.x = oc[o2].mx[f0];v0.y = oc[o2].my[f0];v0.z = oc[o2].mz[f0];
								v1.x = oc[o2].mx[f1];v1.y = oc[o2].my[f1];v1.z = oc[o2].mz[f1];
								v2.x = oc[o2].mx[f2];v2.y = oc[o2].my[f2];v2.z = oc[o2].mz[f2];
								ad02 = (VecDistance(ry1.p,v0) + VecDistance(ry1.p,v1) + VecDistance(ry1.p,v2)) / 3;
								//sprintf(dbuffer,"ad01:%f ad02:%f",ad01,ad02);AddDbg();
								if (ad01 < ad02) // if our shadower's distance < shadowed object's distance
								{
									ttri.V0 =v0; ttri.V1 = v1;ttri.V2 = v2;
									re1 = intersect_RayTriangle(ry1,ttri,&r01);
									re2 = intersect_RayTriangle(ry2,ttri,&r02);
									re3 = intersect_RayTriangle(ry3,ttri,&r03);
									//sprintf(dbuffer,"re1:%i re2:%i re3:%i",re1,re2,re3);AddDbg();
									
									// shadow is erroring when cut test in here i used a tolerance
									if (re1 +re2 +re3 >1)
									{
										if ( !isvusing(r01) && !isvusing(r02) && !isvusing(r03)) // kesiyorsa
										{
											// calculate center of face
											/*cenf.x = (r01.x + r02.x + r03.x) / 3;
											cenf.y = (r01.y + r02.y + r03.y) / 3;
											cenf.z = (r01.z + r02.z + r03.z) / 3;*/

											oc[o2].sfcount++;
											oc[o2].sf.AddElement(r01.x);
											oc[o2].sf.AddElement(r01.y);
											oc[o2].sf.AddElement(r01.z);

											oc[o2].sf.AddElement(r02.x);
											oc[o2].sf.AddElement(r02.y);
											oc[o2].sf.AddElement(r02.z);

											oc[o2].sf.AddElement(r03.x);
											oc[o2].sf.AddElement(r03.y);
											oc[o2].sf.AddElement(r03.z);

										}
									}
								}
								else
								{
									continue;
								};
							}
						}
					}
				}
			}
		}
	}



	// TODO: eleyici bi algoritma daha ekle golgenin toplaminin bolumuyle orta noktayi bul
	// orta noktadan en uzak olan noktalari sec bu noktalarla tri-fan la cizilcek uygun golge olustur

	// IDEA: shadow vertexlerinin en uzak noktalarini bul ve bir plane olustur.Bu planeya
	// shadow mapping gibi bisiy uygula.
}
