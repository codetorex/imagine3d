#include "stdafx.h"
#include "exporter.h"


void MyExporter::ExportGeomObject(INode * node)
{
    int i; // for loops
    Point3 vert;
    int numTVerts;

    TimeValue currtime = m_ip->GetTime();
    ObjectState os = node->EvalWorldState(currtime);
    if (!os.obj) return;
    
    // Target camera "targets" are actually geomobjects, so we skip them here.
    if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0)) return;
	if (os.obj->ClassID() == SKELOBJ_CLASS_ID) return;
//	sprintf(dbuffer,"%s is a Class: %i",node->GetName(),os.obj->ClassID());AddDbg();



    Matrix3 tm = node->GetObjTMAfterWSM(currtime);
        bool delMesh = false;
        Object *obj = os.obj;
        if (obj && obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0))) { 
            TriObject * tri = NULL;
            tri = (TriObject *) obj->ConvertToType(0, Class_ID(TRIOBJ_CLASS_ID, 0));
            if (obj != tri) 
                delMesh = true; // we own the copy
            if (tri) {
                Mesh * mesh = &(tri->GetMesh());
                assert(mesh);
                mesh->buildNormals();
				int a,b;
				a = mesh->getNumVerts();
				b = mesh->getNumFaces();
				oc[curo].vertcount = a;
				oc[curo].facecount = b;
				
				float tirex,tirey,tirez;
				tirex = tirey = tirez = 0;
				oc[curo].mx.Resize(a);
				oc[curo].my.Resize(a);
				oc[curo].mz.Resize(a);

                // Export the vertices
                for (i = 0; i < a; i++) {
                    vert = tm * mesh->verts[i];
					vert = Ver2GL(vert);
					oc[curo].mx.AddElement(vert.x);
					oc[curo].my.AddElement(vert.y);
					oc[curo].mz.AddElement(vert.z);
//					sprintf(dbuffer,"Vertex %i = X: %f Y: %f Z: %f",i,vert.x,vert.y,vert.z);AddDbg();


					tirex += vert.x;
					tirey += vert.y;
					tirez += vert.z;
							// finding bounding box
							float temp;
							temp = vert.x;
							if (temp > oc[curo].bx) oc[curo].bx = temp;
							if (temp < oc[curo].kx) oc[curo].kx = temp;

							temp = vert.y;
							if (temp > oc[curo].by) oc[curo].by = temp;
							if (temp < oc[curo].ky) oc[curo].ky = temp;
							
							temp = vert.z;
							if (temp > oc[curo].bz) oc[curo].bz = temp;
							if (temp < oc[curo].kz) oc[curo].kz = temp;

                }

				oc[curo].cx = tirex / a;
				oc[curo].cy = tirey / a;
				oc[curo].cz = tirez / a;




/*				oc[curo].cr.AddElement(0);
				oc[curo].cg.AddElement(0);
				oc[curo].cb.AddElement(0);*/


				int ak;
				//sprintf(dbuffer,"%s = X: %f Y: %f Z: %f",node->GetName(),oc[curo].cx,oc[curo].cy,oc[curo].cz);AddDbg();

                // export faces
				oc[curo].v1.Resize(mesh->getNumFaces());
				oc[curo].v2.Resize(mesh->getNumFaces());
				oc[curo].v3.Resize(mesh->getNumFaces());
				oc[curo].mat.Resize(mesh->getNumFaces());

                for (i = 0; i < mesh->getNumFaces(); i++) {
					
					ak = (int)mesh->faces[i].getMatID();
					oc[curo].v1.AddElement(mesh->faces[i].v[0]);
					oc[curo].v2.AddElement(mesh->faces[i].v[1]);
					oc[curo].v3.AddElement(mesh->faces[i].v[2]);
					oc[curo].mat.AddElement(ak);
                }
				
                numTVerts = mesh->getNumTVerts();
				oc[curo].tvcount = numTVerts;
                if (numTVerts) {
					for (i = 0; i < numTVerts; i++) {
                        UVVert tvert = mesh->tVerts[i];
						oc[curo].tu.AddElement(tvert.x);
						oc[curo].tv.AddElement(tvert.y);
                    }
                    for (i = 0; i < mesh->getNumFaces(); i++) {
                        TVFace tface = mesh->tvFace[i];
						oc[curo].t1.AddElement(tface.t[0]);
						oc[curo].t2.AddElement(tface.t[1]);
						oc[curo].t3.AddElement(tface.t[2]);
                    }                    
                }


					Point3 fn;  // Face normal
					Point3 vn;  // Vertex normal
					int  vert;
					Face* f;
					
					// Face and vertex normals.
					// In MAX a vertex can have more than one normal (but doesn't always have it).
					// This is depending on the face you are accessing the vertex through.
					// To get all information we need to export all three vertex normals
					// for every face.
					for (i=0; i<mesh->getNumFaces(); i++) {
						f = &mesh->faces[i];
						//fn = mesh->getFaceNormal(i);
						//fprintf(pStream,"%s\t\t%s %d\t%s\n", indent.data(), ID_MESH_FACENORMAL, i, Format(fn));
						
						vert = f->getVert(0);
						vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert));
						vn = Ver2GL(vn);
						oc[curo].hx.AddElement(vn.x);
						oc[curo].hy.AddElement(vn.y);
						oc[curo].hz.AddElement(vn.z);

						
						vert = f->getVert(1);
						vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert));
						vn = Ver2GL(vn);
						oc[curo].hx.AddElement(vn.x);
						oc[curo].hy.AddElement(vn.y);
						oc[curo].hz.AddElement(vn.z);
						
						vert = f->getVert(2);
						vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert));
						vn = Ver2GL(vn);
						oc[curo].hx.AddElement(vn.x);
						oc[curo].hy.AddElement(vn.y);
						oc[curo].hz.AddElement(vn.z);

					}
				oc[curo].cr = new unsigned char [mesh->getNumFaces() * 3];
				oc[curo].cg = new unsigned char [mesh->getNumFaces() * 3];
				oc[curo].cb = new unsigned char [mesh->getNumFaces() * 3];
				for (i=0;i<mesh->getNumFaces() * 3;i++)
				{
					oc[curo].cr[i] = fh.alr;
					oc[curo].cg[i] = fh.alg;
					oc[curo].cb[i] = fh.alb;
				}

				oc[curo].normalcount = 3 * mesh->getNumFaces();
				oc[curo].sfcount = 0;
				sprintf(oc[curo].namesz,"%s",node->GetName());
                if (delMesh)delete tri;
				ExportPhysiqueData(currtime,&os,node);
				curo++;
				
            }
        }

}

Point3 MyExporter::GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv)
{
	Face* f = &mesh->faces[faceNo];
	DWORD smGroup = f->smGroup;
	int numNormals;
	Point3 vertexNormal;
	if (rv->rFlags & SPECIFIED_NORMAL) {
		vertexNormal = rv->rn.getNormal();
	}
	else if ((numNormals = rv->rFlags & NORCT_MASK) && smGroup) {
		if (numNormals == 1) {
			vertexNormal = rv->rn.getNormal();
		}
		else {
			for (int i = 0; i < numNormals; i++) {
				if (rv->ern[i].getSmGroup() & smGroup) {
					vertexNormal = rv->ern[i].getNormal();
				}
			}
		}
	}
	else {
		vertexNormal = mesh->getFaceNormal(faceNo);
	}
	return vertexNormal;
}


