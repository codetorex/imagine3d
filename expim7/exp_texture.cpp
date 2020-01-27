#include "stdafx.h"
#include "exporter.h"

void MyExporter::LoadTextureInfo()
{
	int subtexcount;
    MtlBaseLib * scenemats = m_ip->GetSceneMtls();
    int i,j; // for loops
    if (scenemats) {
        for (i = 0; i < scenemats->Count(); i++)  { 
            MtlBase * mtl = (*scenemats)[i];
            if (IsMtl(mtl) && mtl->IsMultiMtl()) 
			{
                Mtl * m = (Mtl *)mtl;
                //::fprintf(m_fileStream, "    multimtl -- submtls:\n");
				subtexcount = m->NumSubMtls();
				fh.texturecount = subtexcount;
				tc = new IM3Texture [subtexcount];

                for (j = 0; j < subtexcount; j++) {
                    Mtl *sm = m->GetSubMtl(j);
                    if (sm) {
                        // NOTE: For this tutorial, we only go one "level" deep
                        sprintf(tc[j].names,"%s",sm->GetName());
						//::fprintf(m_fileStream, "        Name:<%s>\n", sm->GetName());
                    }
                } 

            }
        }
    }
}

