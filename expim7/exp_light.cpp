#include "stdafx.h"
#include "exporter.h"


void MyExporter::ExportLightObject(INode * node)
{

    TimeValue currtime = m_ip->GetTime();
    ObjectState os = node->EvalWorldState(currtime);
    if (!os.obj)
        return;

    GenLight* light = (GenLight*)os.obj;
    struct LightState ls;
    light->EvalLightState(currtime, FOREVER, &ls);

    if (!light->GetUseLight())
        return; // only export lights that are on for simplicity

    //::fprintf(m_fileStream, "BEGIN LIGHT Name:<%s> Type:<",node->GetName());

    // light type
    switch(light->Type()) {
    case OMNI_LIGHT:
		lc[curl].lighttype = 0;
        break;
    case TSPOT_LIGHT: 
        lc[curl].lighttype = 1; // target spot
        break;
    case DIR_LIGHT:   
        lc[curl].lighttype = 2; // directional
        break;
    case FSPOT_LIGHT:
        lc[curl].lighttype = 3; // free spot
        break;
    case TDIR_LIGHT:
    default:
        lc[curl].lighttype = 4; // targeted directional 
        break;
    }

    ///////////////////////////////////
    // color, intensity info
	Point3 lcolor;
	lcolor = light->GetRGBColor(currtime);

	lc[curl].r = (lcolor.x*255);
	lc[curl].g = (lcolor.y*255);
	lc[curl].b = (lcolor.z*255);
	lc[curl].intensity = ls.intens;

    ///////////////////////////////////
    // get and dump the node matrix, mainly for xform and rot info
    // also dump target TM, if the light has a target
    Matrix3 nodepivot = node->GetNodeTM(currtime);
	//nodepivot = Mat2GL(nodepivot);

	MxToM(nodepivot,lc[curl].lmatrix);

    INode* target = node->GetTarget();
    if (target) {
        nodepivot = target->GetNodeTM(currtime);
		//nodepivot = Mat2GL(nodepivot);
		MxToM(nodepivot,lc[curl].tmatrix);
    }

	sprintf(lc[curl].namesz,"%s",node->GetName());

	lc[curl].atten[0] = light->GetAtten(currtime,ATTEN1_START); // Near Start
	lc[curl].atten[1] = light->GetAtten(currtime,ATTEN1_END); // Near End
	lc[curl].atten[2] = light->GetAtten(currtime,ATTEN_START); // Far Start
	lc[curl].atten[3] = light->GetAtten(currtime,ATTEN_END); // Far End
    curl++;

}
