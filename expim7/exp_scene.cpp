#include "stdafx.h"
#include "exporter.h"

void MyExporter::DoAll()
{
	DoHeader();
	DoNodes();

	if (fh.vertexlights) CalculateVertexLight();
	if (fh.shadowface) CalculateVertexShadows();

	WriteToFile();

	sprintf(dbuffer,"Export tooks %i ms.",GetTickCount()-elaptimer);AddDbg();
}


void MyExporter::DoHeader()
{
	fh.signature = 1395871049;
	fh.objectcount = 0;
	fh.lightcount = 0;
	fh.entitycount = 0;
	fh.cameracount = 0;

	SYSTEMTIME systim;
	GetLocalTime(&systim);
	elaptimer = GetTickCount();
	GetString(IDS_LONGDESC);

	sprintf(dbuffer,"-----------------------------------------------");AddDbg();
	sprintf(dbuffer,"%s %i/%i/%i %i:%i",GetString(IDS_LONGDESC),systim.wDay,
		systim.wMonth,systim.wYear,systim.wHour,systim.wMinute);AddDbg();
	sprintf(dbuffer,"-----------------------------------------------");AddDbg();
	sprintf(dbuffer,"EXPORTMODE=%i",exportmode);AddDbg();


	Color ambLight = m_ip->GetAmbient(m_ip->GetTime(), FOREVER);
	COLORREF ambColor = ambLight.toRGB();

	fh.alr = GetRValue(ambColor);
	fh.alg = GetGValue(ambColor);
	fh.alb = GetBValue(ambColor);

	LoadTextureInfo();
	CountLAO();
	PrepareMem();


}

void MyExporter::PrepareMem()
{
	oc = new IM3Object	[fh.objectcount];
	lc = new IM3Light	[fh.lightcount];
	ec = new IM3Entity	[fh.entitycount];
	cc = new IM3Camera	[fh.cameracount];
}

void MyExporter::DoNodes()
{
    int numChildren = m_ip->GetRootNode()->NumberOfChildren();
    for (int idx = 0; idx < numChildren; idx++) {
        if (m_ip->GetCancel())break;
        nodeEnum(m_ip->GetRootNode()->GetChildNode(idx));
    }
}

bool MyExporter::nodeEnum(INode* node) 
{
	char tak[100];

    if (!node) return FALSE;
    if (m_exportSelected && node->Selected() == FALSE)return FALSE;
    if (m_ip->GetCancel())return FALSE;

    ObjectState os = node->EvalWorldState(m_ip->GetTime()); 
    if (os.obj) {
        switch(os.obj->SuperClassID()) {
        case GEOMOBJECT_CLASS_ID: 
            sprintf(tak,"%s",node->GetName());
			if (tak[0] == 0x65)
			{
				ExportEntity(node);
			}else{
				ExportGeomObject(node); 
			}
            break;

        case LIGHT_CLASS_ID:
            ExportLightObject(node);
            break;
		
		case CAMERA_CLASS_ID:
			ExportCamera(node);
			break;

        default:
            break;
        }
    }

    for (int c = 0; c < node->NumberOfChildren(); c++) {
        if (!nodeEnum(node->GetChildNode(c)))
            return FALSE;
    }


    return TRUE;
}


void MyExporter::CountLAO()
{
	char tak[100];
	INode* node;
	int numChildren = m_ip->GetRootNode()->NumberOfChildren();
    for (int idx = 0; idx < numChildren; idx++) {
        if (m_ip->GetCancel())break;
        node = m_ip->GetRootNode()->GetChildNode(idx);
			ObjectState os = node->EvalWorldState(m_ip->GetTime()); 
			if (os.obj) {
				switch(os.obj->SuperClassID()) {
				case GEOMOBJECT_CLASS_ID: 
					sprintf(tak,"%s",node->GetName());
					if (tak[0] == 0x65)
					{
						fh.entitycount++;
					}else{
						fh.objectcount++;
					}
					break;
		
				case LIGHT_CLASS_ID:
					fh.lightcount++;
					break;

				case CAMERA_CLASS_ID:
					fh.cameracount++;
					break;

				default:
					break;
				}
			}
    }
	//GetBoneCount();
}
