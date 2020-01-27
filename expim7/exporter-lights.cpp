
[in DoHeader]



    // export ambient scene light
    Color ambLight = m_ip->GetAmbient(m_ip->GetTime(), FOREVER);
    COLORREF ambColor = (DWORD)ambLight;
    ::fprintf(m_fileStream,"AMBIENT LIGHT rgb:<%d,%d,%d>\n", 
        GetRValue(ambColor), GetGValue(ambColor), GetBValue(ambColor));



[new method : ExportLightObject]




void MyExporter::ExportLightObject(INode * node)
{

    TimeValue currtime = m_ip->GetTime();
    ObjectState os = node->EvalWorldState(currtime);
    if (!os.obj)
        return;

    GenLight* light = (GenLight*)os.obj;
    struct LightState ls;
    light->EvalLightState(currtime, FOREVER, &ls);

    if (! light->GetUseLight())
        return; // only export lights that are on for simplicity

    ::fprintf(m_fileStream, "BEGIN LIGHT Name:<%s> Type:<",node->GetName());

    // light type
    switch(light->Type()) {
    case OMNI_LIGHT:  
        fprintf(m_fileStream, "OMNI>\n"); 
        break;
    case TSPOT_LIGHT: 
        fprintf(m_fileStream, "TARGET SPOT>\n"); 
        break;
    case DIR_LIGHT:   
        fprintf(m_fileStream, "DIRECTIONAL>\n"); 
        break;
    case FSPOT_LIGHT:
        fprintf(m_fileStream, "FREE SPOT>\n"); 
        break;
    case TDIR_LIGHT:
    default:
        fprintf(m_fileStream, "TARGETED DIRECTIONAL>\n"); 
        break;
    }

    ///////////////////////////////////
    // color, intensity info
    COLORREF lightcol = (DWORD)ls.color;
    ::fprintf(m_fileStream,"    light color -- rgb:<%d,%d,%d>\n", 
        GetRValue(lightcol), GetGValue(lightcol), GetBValue(lightcol));
    ::fprintf(m_fileStream,"    light intensity -- mult:<%f>\n", ls.intens);

    ///////////////////////////////////
    // get and dump the node matrix, mainly for xform and rot info
    // also dump target TM, if the light has a target
    Matrix3 nodepivot = node->GetNodeTM(currtime);
    Point3 row;
    row = nodepivot.GetRow(0);
    ::fprintf(m_fileStream,"BEGIN TM\n    Row 0:<%f,%f,%f>\n", row.x, row.y, row.z);
    row = nodepivot.GetRow(1);
    ::fprintf(m_fileStream,"    Row 1:<%f,%f,%f>\n", row.x, row.y, row.z);
    row = nodepivot.GetRow(2);
    ::fprintf(m_fileStream,"    Row 2:<%f,%f,%f>\n", row.x, row.y, row.z);
    row = nodepivot.GetRow(3);
    ::fprintf(m_fileStream,"    Row 3:<%f,%f,%f>\nEND TM\n", row.x, row.y, row.z);
    INode* target = node->GetTarget();
    if (target) {
        nodepivot = target->GetNodeTM(currtime);
        row = nodepivot.GetRow(0);
        ::fprintf(m_fileStream,"BEGIN TARGET TM\n    Row 0:<%f,%f,%f>\n", row.x, row.y, row.z);
        row = nodepivot.GetRow(1);
        ::fprintf(m_fileStream,"    Row 1:<%f,%f,%f>\n", row.x, row.y, row.z);
        row = nodepivot.GetRow(2);
        ::fprintf(m_fileStream,"    Row 2:<%f,%f,%f>\n", row.x, row.y, row.z);
        row = nodepivot.GetRow(3);
        ::fprintf(m_fileStream,"    Row 3:<%f,%f,%f>\nEND TARGET TM\n", row.x, row.y, row.z);
    }

    ///////////////////////////////////
    // export shadow info, if applicable

    if (light->GetShadow()) {
        int shadtype = light->GetShadowType();
        ::fprintf(m_fileStream,"    shadow -- type:<");
        switch (shadtype) {
        case -1: 
            ::fprintf(m_fileStream, "GENERATOR (null)>\n");
            break;
        case 0: 
            ::fprintf(m_fileStream, "SHADOW MAPS>\n");
            break;
        case 1: 
            ::fprintf(m_fileStream, "RAYTRACED>\n");
            break;
        default: 
            ::fprintf(m_fileStream, "GENERATOR (0x%x)>\n", shadtype);
            break;
        }
    }

    ::fprintf(m_fileStream, "END LIGHT\n");

}