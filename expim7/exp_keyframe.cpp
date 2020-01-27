#include "stdafx.h"
#include "exporter.h"


/*struct IMKHeader
{
	int signature;
	int keystart;
	int keyend;
	int framerate;
};

struct IMKKey
{
	int keyno;
	float* chunk; // x1,y1,z1,x2,y2,z...
};*/

/*
	IMKHeader	kh;
	IMKKey*		frms;
*/

void MyExporter::DoKeyframe()
{
	SYSTEMTIME systim;
	GetLocalTime(&systim);
	elaptimer = GetTickCount();
	GetString(IDS_LONGDESC);

	sprintf(dbuffer,"-----------------------------------------------");AddDbg();
	sprintf(dbuffer,"%s %i/%i/%i %i:%i",GetString(IDS_LONGDESC),systim.wDay,
		systim.wMonth,systim.wYear,systim.wHour,systim.wMinute);AddDbg();
	sprintf(dbuffer,"-----------------------------------------------");AddDbg();
	sprintf(dbuffer,"EXPORTMODE=%i",exportmode);AddDbg();
	// Prepare Memory
	GetBoneCount();
	kh.signature = 1261653321;
	kh.keystart = (m_ip->GetAnimRange().Start())/GetTicksPerFrame();
	kh.keyend = (m_ip->GetAnimRange().End())/GetTicksPerFrame();
	kh.framerate = GetFrameRate();
	keyc = kh.keyend - kh.keystart;

	fh.objectcount = 0;
	fh.lightcount = 0;
	fh.entitycount = 0;
	fh.cameracount = 0;
	CountLAO();

	kfob = new IMKObj [fh.objectcount];
	for (int i=0;i<fh.objectcount;i++)
	{
		kfob[i].frms = new IMKKey [keyc];
	}

    int numChildren = m_ip->GetRootNode()->NumberOfChildren();
    for (int idx = 0; idx < numChildren; idx++) {
        if (m_ip->GetCancel())break;
        FrameEnum(m_ip->GetRootNode()->GetChildNode(idx));
    }

}


bool MyExporter::FrameEnum(INode* node) 
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
				//this is a entity i dont need this
			}else{
				ExportGeomObject(node); 
			}
            break;

        default:
            break;
        }
    }

    for (int c = 0; c < node->NumberOfChildren(); c++) {
        if (!FrameEnum(node->GetChildNode(c)))
            return FALSE;
    }

    return TRUE;
}