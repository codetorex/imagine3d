

    // export material info used in scene
    MtlBaseLib * scenemats = m_ip->GetSceneMtls();
    int i,j; // for loops
    if (scenemats) {
        for (i = 0; i < scenemats->Count(); i++)  { 
            // DoSomething(scenemats[i]); 
            MtlBase * mtl = (*scenemats)[i];
            ::fprintf(m_fileStream, "BEGIN MTL Name:<%s> FullName:<%s>\n", mtl->GetName(), mtl->GetFullName());
            if (IsMtl(mtl) && mtl->IsMultiMtl()) {
                // multi-mtl
                Mtl * m = (Mtl *)mtl;
                ::fprintf(m_fileStream, "    multimtl -- submtls:\n");
                for (j = 0; j < m->NumSubMtls(); j++) {
                    Mtl *sm = m->GetSubMtl(j);
                    if (sm) {
                        // NOTE: For this tutorial, we only go one "level" deep
                        ::fprintf(m_fileStream, "        Name:<%s>\n", sm->GetName());
                    }
                }

            } else {

                // submtls or texmaps
                for (j = 0; j < mtl->NumSubTexmaps(); j++) {
                    Texmap * tmap = mtl->GetSubTexmap(j);
                    if (tmap) {
                        // NOTE: For this tutorial, we only go one subtex "level"
                        // deep, although in reality, we can go much deeper
                        // (e.g. mtl with checker diffuse, that in turn has another
                        // checker as a subtex, etc)
                        ::fprintf(m_fileStream, "    subtex -- Name:<%s> UVWSrc:<%d> MapChannel:<%d> \n", tmap->GetName(), tmap->GetUVWSource(), tmap->GetMapChannel());
                        // for this sample, if one of the first level subtex's is a 
                        // bitmaptex, dump out some more info.  It should be clear
                        // that similar actions can be taken with other typical subtexs
                        // (RGBMult, etc)
                        if (tmap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0)) {
                            BitmapTex *bmt = (BitmapTex*) tmap;
                            ::fprintf(m_fileStream, "        Bitmap Tex -- File:<%s>\n", bmt->GetMapName());
                            // (Sidenote: There are supposedly some cases where this
                            // might not return the full filename + path)
                        }

                    }
                }
            }
            ::fprintf(m_fileStream, "END MTL\n");
        }
    }
