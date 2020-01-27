#include "stdafx.h"
#include "exporter.h"


Modifier* MyExporter::FindPhysiqueModifier (INode* nodePtr)
{
	Object* ObjectPtr = nodePtr->GetObjectRef();
	if (!ObjectPtr) return NULL;
	while (ObjectPtr->SuperClassID() == GEN_DERIVOB_CLASS_ID && ObjectPtr)
	{
		IDerivedObject *DerivedObjectPtr = (IDerivedObject *)(ObjectPtr);
						
		int ModStackIndex = 0;
		while (ModStackIndex < DerivedObjectPtr->NumModifiers())
		{
			Modifier* ModifierPtr = DerivedObjectPtr->GetModifier(ModStackIndex);
			if (ModifierPtr->ClassID() == Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B))
			{
				return ModifierPtr;
			}
			ModStackIndex++;
		}
		ObjectPtr = DerivedObjectPtr->GetObjRef();
	}
	return NULL;
}


void MyExporter::ExportPhysiqueData(TimeValue t, ObjectState *os, INode *node)
{
	Modifier *phyMod = FindPhysiqueModifier(node);
	if (!phyMod) return;
	IPhysiqueExport *phyExport = (IPhysiqueExport *)phyMod->GetInterface(I_PHYINTERFACE);
	if (phyExport)
	{
		IPhyContextExport *mcExport = (IPhyContextExport *)phyExport->GetContextInterface(node);

		if (mcExport)
		{
			mcExport->ConvertToRigid(TRUE);
			for (int i = 0; i < os->obj->NumPoints();  i++)
			{
				IPhyVertexExport *vtxExport = mcExport->GetVertexInterface(i);

				if (vtxExport)
				{
					if (!(vtxExport->GetVertexType() & BLENDED_TYPE))
					{ // no 1
						IPhyRigidVertex *vtxNoBlend = (IPhyRigidVertex *)vtxExport;
						INode *Bone = vtxNoBlend->GetNode();

						oc[curo].abone.AddElement(GenID(Bone->GetName()));
						
//						sprintf(dbuffer,"Vertex %i attached to %s(%i)",i,Bone->GetName(),GenID(Bone->GetName()));
//						AddDbg();

/*						Point3 Offset = vtxNoBlend->GetOffsetVector();
                                        
						os->obj->SetPoint(i, Bone->GetNodeTM(t) * Offset);
*/
						mcExport->ReleaseVertexInterface(vtxExport);
						vtxExport = NULL;
					}
				}
			}
			phyExport->ReleaseContextInterface(mcExport);
		}
		phyMod->ReleaseInterface(I_PHYINTERFACE, phyExport);
	}
}