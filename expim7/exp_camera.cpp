#include "stdafx.h"
#include "exporter.h"


void MyExporter::ExportCamera(INode * node)
{
    TimeValue currtime = m_ip->GetTime();
    ObjectState os = node->EvalWorldState(currtime);
    if (!os.obj)
        return;

/*	GenCamera* camera = (GenCamera*)os.obj;
    struct CameraState cs;
    camera->EvalLightState(currtime, FOREVER, &cs);
*/
	sprintf(cc[curc].names,"%s",node->GetName());
	
	Matrix3 nodepivot = node->GetNodeTM(currtime);
	Point3 row;
	row = nodepivot.GetTrans();
	row = Ver2GL(row);
	cc[curc].cx = row.x; cc[curc].cy = row.y; cc[curc].cz = row.z;
    INode* target = node->GetTarget();
	nodepivot = target->GetNodeTM(currtime);
	row = nodepivot.GetTrans();
	row = Ver2GL(row);
	cc[curc].tx = row.x; cc[curc].ty = row.y; cc[curc].tz = row.z;
	curc++;

}
