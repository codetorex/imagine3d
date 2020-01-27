#include "stdafx.h"
#include "exporter.h"
#include "DECOMP.H"

bool MyExporter::skeletalEnum(INode* node) 
{
    if (!node) return FALSE;
    if (m_exportSelected && node->Selected() == FALSE)return FALSE;
    if (m_ip->GetCancel())return FALSE;

    ObjectState os = node->EvalWorldState(m_ip->GetTime()); 
    if (os.obj) {
		Control *c = node->GetTMController();
		if ((c->ClassID() == BIPSLAVE_CONTROL_CLASS_ID) ||
			(c->ClassID() == BIPBODY_CONTROL_CLASS_ID) ||
			(c->ClassID() == FOOTPRINT_CLASS_ID))
        {
			//sprintf(dbuffer,"Exporting... %s id=%i class=%i",node->GetName(),GenID(node->GetName()),c->ClassID());AddDbg();
			ExportBone(node,c);
		}
    }

    for (int c = 0; c < node->NumberOfChildren(); c++) {
        if (!skeletalEnum(node->GetChildNode(c)))
            return FALSE;
    }


    return TRUE;
}
void MyExporter::DoSkeletal()
{
	// Send some info	
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
	bh.signature = 1110658377;

	bcon = new IMBBone [bh.bonecount];
	bh.keystart = (m_ip->GetAnimRange().Start())/GetTicksPerFrame();
	bh.keyend = (m_ip->GetAnimRange().End())/GetTicksPerFrame();
	//sprintf(dbuffer,"Keystart=%i",bh.keystart);AddDbg();
	//sprintf(dbuffer,"Keyend=%i",bh.keyend);AddDbg();
	bh.framerate = GetFrameRate();
	//bh.ticksperframe = GetTicksPerFrame();
	//sprintf(dbuffer,"Framerate=%i",bh.framerate);AddDbg();
	//sprintf(dbuffer,"Ticksperframe=%i",bh.ticksperframe);AddDbg();




	// Okay lets go
	//sprintf(dbuffer,"Memory ready for bone export.");AddDbg();

	int numChildren = m_ip->GetRootNode()->NumberOfChildren();
    for (int idx = 0; idx < numChildren; idx++) {
        if (m_ip->GetCancel())break;
        skeletalEnum(m_ip->GetRootNode()->GetChildNode(idx));
    }
	WriteBones();
}

void MyExporter::GetBoneCount()
{
	int numChildren = m_ip->GetRootNode()->NumberOfChildren();
    for (int idx = 0; idx < numChildren; idx++) {
        if (m_ip->GetCancel())break;
		BoneCounter(m_ip->GetRootNode()->GetChildNode(idx));
		
    }

}
void MyExporter::BoneCounter(INode* node)
{
	if (node)
	{

		ObjectState os = node->EvalWorldState(m_ip->GetTime()); 
		if (os.obj) {
			Control *c = node->GetTMController();
			if ((c->ClassID() == BIPSLAVE_CONTROL_CLASS_ID) ||
				(c->ClassID() == BIPBODY_CONTROL_CLASS_ID) ||
				(c->ClassID() == FOOTPRINT_CLASS_ID))
			{
				bh.bonecount++;
			}
		}

		for (int c = 0; c < node->NumberOfChildren(); c++) {
			BoneCounter(node->GetChildNode(c));
		}
	}
}
void MyExporter::ExportBone(INode* node,Control* c)
{
	Matrix3 ma,pma,ltma;
	// MA object matrix PMA parent's matrix LTMA local matrix
	Matrix3 lm;
	//int delta = bh.ticksperframe;
	int kfc=0;
	lm.Zero();
//	lm.Identity();
	for (int i=bh.keystart;i<bh.keyend;i++)
	{
		ma = node->GetNodeTM(i*GetTicksPerFrame());
		if (ma == lm)
			continue;
		lm = ma;
		//sprintf(dbuffer,"Bone %s changed in %i.",node->GetName(),i);AddDbg();
		kfc++;
	}
	bcon[curb].framec = kfc;
	bcon[curb].frames = new IMBKeyframe [kfc];
	//sprintf(dbuffer,"Bone %s id=%i has %i frames.",node->GetName(),GenID(node->GetName()),kfc);AddDbg();

	kfc = 0;
	for (i=bh.keystart;i<bh.keyend;i++)
	{
		ma = node->GetNodeTM(i*GetTicksPerFrame());
		//ma.NoScale();
		//ma = Mat2GL(ma);
		
		
		if (ma == lm)
			continue;
	

		bcon[curb].frames[kfc].frameno = i;
//		INode *npnode = node->GetParentNode();
		ma = node->GetNodeTM(i*GetTicksPerFrame());
//		pma = npnode->GetNodeTM(i*GetTicksPerFrame());
		lm = ma;
		ma.NoScale();		// scale sicirtir
//		pma.NoScale();		// scale sicirtir
			
//		ltma	= ma * Inverse(pma);
//		Point3 trans = ltma.GetTrans();
		Point3 trans = ma.GetTrans();

		AffineParts affparts;
		float rgflXYZRotations[3];
		
//		decomp_affine(ltma, &affparts);
		decomp_affine(ma, &affparts);
		QuatToEuler(affparts.q, rgflXYZRotations);

		float xRo = rgflXYZRotations[0];		// in radians
		float yRo = rgflXYZRotations[1];		// in radians
		float zRo = rgflXYZRotations[2];		// in radians

		xRo = ReduceRotation(xRo);
		yRo = ReduceRotation(yRo);
		zRo = ReduceRotation(zRo);
		bcon[curb].frames[kfc].xPos = trans.x;
		bcon[curb].frames[kfc].yPos = trans.y;
		bcon[curb].frames[kfc].zPos = trans.z;

		bcon[curb].frames[kfc].xRot = xRo;
		bcon[curb].frames[kfc].yRot = yRo;
		bcon[curb].frames[kfc].zRot = zRo;
		//MxToM(ma,bcon[curb].frames[kfc].m);

		kfc++;
	}
	bcon[curb].boneid = GenID(node->GetName());
//	bcon[curb].parentid = 0;
//	bcon[curb].childid = 0;

	//sprintf(dbuffer,"Bone %s id=%i exported.",node->GetName(),GenID(node->GetName()) );AddDbg();

	/*Matrix3 bmat;
	Animatable *a1 = c->SubAnim(0);
	Animatable *a2 = c->SubAnim(1);
	Animatable *a3 = c->SubAnim(2);*/


	curb++;

}

float MyExporter::ReduceRotation(float fl)
{
	while (fl >= TWOPI)
		fl -= TWOPI;
	while (fl <= -TWOPI)
		fl += TWOPI;
	return fl;
}