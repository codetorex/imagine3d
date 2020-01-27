#include "stdafx.h"
#include "exporter.h"


void MyExporter::ExportEntity(INode * node)
{
	TimeValue currtime = m_ip->GetTime();
	ObjectState os = node->EvalWorldState(currtime);
	if (!os.obj) return;
	if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID,0)) return;

    Matrix3 nodepivot = node->GetNodeTM(currtime);
	nodepivot = Mat2GL(nodepivot);

	MxToM(nodepivot,ec[cure].matrix);

	sprintf(ec[cure].nameandparam,"%s",node->GetName());
	cure++;

}
