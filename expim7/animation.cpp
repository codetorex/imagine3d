#include "stdafx.h"
#include "exporter.h"
#include "decomp.h"


#define ALMOST_ZERO 1.0e-3f
bool EqualPoint3(Point3 p1, Point3 p2);

void MyExporter::ExportBoneKeys(INode* node)
{

}


bool MyExporter::CheckForAnimation(INode* node, bool& bPos, bool& bRot, bool& bScale)
{
	TimeValue start = m_ip->GetAnimRange().Start();
	TimeValue end = m_ip->GetAnimRange().End();
	TimeValue t;
	int delta = GetTicksPerFrame();
	Matrix3 tm;
	AffineParts ap;
	Point3 firstPos;
	float rotAngle, firstRotAngle;
	Point3 rotAxis, firstRotAxis;
	Point3 firstScaleFactor;

	bPos = bRot = bScale = FALSE;

	for (t=start; t<=end; t+=delta) {
		tm = node->GetNodeTM(t) * Inverse(node->GetParentTM(t));

		decomp_affine(tm, &ap);

		AngAxisFromQ(ap.q, &rotAngle, rotAxis);

		if (t != start) {
			if (!bPos) {
				if (!EqualPoint3(ap.t, firstPos)) {
					bPos = TRUE;
					}
				}
			if (!bRot) {
				if (fabs(rotAngle - firstRotAngle) > ALMOST_ZERO) {
					bRot = TRUE;
					}
				else if (!EqualPoint3(rotAxis, firstRotAxis)) {
					bRot = TRUE;
					}
				}

			if (!bScale) {
				if (!EqualPoint3(ap.k, firstScaleFactor)) {
					bScale = TRUE;
					}
				}
			}
		else {
			firstPos = ap.t;
			firstRotAngle = rotAngle;
			firstRotAxis = rotAxis;
			firstScaleFactor = ap.k;
			}

		if (bPos && bRot && bScale)
			break;
		}

	return bPos || bRot || bScale;
}

void MyExporter::ExportPosSample(INode* node) 
{		
//	fprintf(pStream,"%s\t\t%s {\n", indent.data(), ID_POS_TRACK);

	TimeValue start = m_ip->GetAnimRange().Start();
	TimeValue end = m_ip->GetAnimRange().End();
	TimeValue t;
	int delta = GetTicksPerFrame() ;
	Matrix3 tm;
	AffineParts ap;
	Point3	prevPos;

	for (t=start; t<=end; t+=delta) {
		tm = node->GetNodeTM(t) * Inverse(node->GetParentTM(t));
		decomp_affine(tm, &ap);

		Point3 pos = ap.t;

		if (t!= start && EqualPoint3(pos, prevPos)) {
			// Skip identical keys 
			continue;
		}

		prevPos = pos;

		// Output the sample
		//fprintf(pStream, "%s\t\t\t%s %d\t%s\n",indent.data(),ID_POS_SAMPLE,t,Format(pos));
	}

	//fprintf(pStream,"%s\t\t}\n", indent.data());
}

void MyExporter::ExportRotSample(INode* node) 
{	
	
	//fprintf(pStream,"%s\t\t%s {\n", indent.data(), ID_ROT_TRACK);

	TimeValue start = m_ip->GetAnimRange().Start();
	TimeValue end = m_ip->GetAnimRange().End();
	TimeValue t;
	int delta = GetTicksPerFrame();
	Matrix3 tm;
	AffineParts ap;
	Quat prevQ;

	prevQ.Identity();

	for (t=start; t<=end; t+=delta) {
		tm = node->GetNodeTM(t) * Inverse(node->GetParentTM(t));

		decomp_affine(tm, &ap);

		// Rotation keys should be relative, so we need to convert these
		// absolute samples to relative values.

		Quat q = ap.q / prevQ;
		prevQ = ap.q;

		if (q.IsIdentity()) {
			// No point in exporting null keys...
			continue;
		}

		// Output the sample
		//fprintf(pStream, "%s\t\t\t%s %d\t%s\n",indent.data(),ID_ROT_SAMPLE,t,Format(q));
	}

	//fprintf(pStream,"%s\t\t}\n", indent.data());
}

void MyExporter::ExportScaleSample(INode* node)
{	
	
//	fprintf(pStream,"%s\t\t%s {\n", indent.data(), ID_SCALE_TRACK);

	TimeValue start = m_ip->GetAnimRange().Start();
	TimeValue end = m_ip->GetAnimRange().End();
	TimeValue t;
	int delta = GetTicksPerFrame();
	Matrix3 tm;
	AffineParts ap;
	Point3	prevFac;

	for (t=start; t<=end; t+=delta) {
		tm = node->GetNodeTM(t) * Inverse(node->GetParentTM(t));
		decomp_affine(tm, &ap);

		if (t!= start && EqualPoint3(ap.k, prevFac)) {
			// Skip identical keys 
			continue;
		}

		prevFac = ap.k;

		// Output the sample
		//fprintf(pStream, "%s\t\t\t%s %d\t%s %s\n",indent.data(),ID_SCALE_SAMPLE,t,Format(ap.k),Format(ap.u));
	}

	//fprintf(pStream,"%s\t\t}\n", indent.data());
}

bool EqualPoint3(Point3 p1, Point3 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return FALSE;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return FALSE;
	if (fabs(p1.z - p2.z) > ALMOST_ZERO)
		return FALSE;

	return TRUE;
}