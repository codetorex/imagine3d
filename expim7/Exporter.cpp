/*

  IM3 Exporter
  -----------------------------------------------
  Programmed by Burak YILDIRIM

  0.1b
  ----
  Mesh export

  0.2b
  ----
  Added normal export

  0.3b
  ----
  added header info
  correct object export
  calculate physical properties
  light export
  entity export
  camera export
  texture export

  0.4b
  ----
  added physique export


  0.45b
  ----
  added vertex lightning calculations

  0.5b
  ----
  bone animation exporting
  code seperated into files





*/
#include "stdafx.h"
#include "exporter.h"


class MyExporterClassDesc : public ClassDesc2 
{
public:
    int             IsPublic()              { return TRUE; }
    void *          Create(BOOL loading)    { return new MyExporter; }
    const TCHAR *   ClassName()             { return GetString(IDS_CLASSNAME); }
    SClass_ID       SuperClassID()          { return SCENE_EXPORT_CLASS_ID; }
    Class_ID        ClassID()               { return MYEXP_CLASSID; }
    const TCHAR*    Category()              { return _T("");  }
    const TCHAR*    InternalName()          { return _T("IM3Exporter"); }
    HINSTANCE       HInstance()             { return g_hInstance; }
};

static MyExporterClassDesc g_ExportCD;
ClassDesc* GetSceneExportDesc() { return &g_ExportCD; }
MyExporter::MyExporter(): m_exportSelected(false), m_suppressPrompts(false), m_ip(NULL), m_expip(NULL), m_fileStream(NULL){}
int MyExporter::ExtCount() {return 1; }
const TCHAR * MyExporter::Ext(int n){switch(n) {case 0:return (_T(MYEXP_EXT));}return _T("");}
const TCHAR * MyExporter::LongDesc(){return GetString(IDS_LONGDESC);}
const TCHAR * MyExporter::ShortDesc(){return GetString(IDS_SHORTDESC);}
const TCHAR * MyExporter::AuthorName(){return GetString(IDS_AUTHOR);}
const TCHAR * MyExporter::CopyrightMessage(){return GetString(IDS_COPYRIGHT);}
const TCHAR * MyExporter::OtherMessage1(){return GetString(IDS_OTHER1);}
const TCHAR * MyExporter::OtherMessage2() {return GetString(IDS_OTHER2); }
unsigned int MyExporter::Version(){return MYEXP_VER;}
static BOOL CALLBACK AboutDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){MyExporter * myexp = (MyExporter*)GetWindowLong(hWnd,GWL_USERDATA);if (!myexp && msg != WM_INITDIALOG)return FALSE;switch (msg) {case WM_INITDIALOG: myexp = (MyExporter*)lParam;SetWindowLong(hWnd,GWL_USERDATA,lParam);break;case WM_DESTROY:break;case WM_COMMAND:switch (LOWORD(wParam)) {case IDOK:EndDialog(hWnd,1);break;}break;default:return FALSE;}return TRUE;}
void MyExporter::ShowAbout(HWND hWnd){DialogBoxParam(g_hInstance,MAKEINTRESOURCE(IDD_ABOUT),hWnd,AboutDlgProc,(LPARAM)this);}
BOOL MyExporter::SupportsOptions(int ext, DWORD options){if (options & SCENE_EXPORT_SELECTED) return TRUE;else return FALSE;}

//MyExporter* wthis;

static INT_PTR CALLBACK DebugDlgProc(HWND hWnd, UINT msg,WPARAM wParam, LPARAM lParam)
{
	MyExporter *expo= (MyExporter*)GetWindowLongPtr(hWnd,GWLP_USERDATA); 
	switch (msg) {
	case WM_INITDIALOG:
		expo = (MyExporter*)lParam;
		SetWindowLongPtr(hWnd,GWLP_USERDATA,lParam); 
		CenterWindow(hWnd, GetParent(hWnd));
		expo->DebugDlgs = &hWnd;

		if (expo->exportmode==0)
		{
			expo->DoAll();
		}

		if (expo->exportmode==1)
		{
			expo->DoSkeletal();
		}
		if (expo->exportmode==2)
		{
			expo->DoKeyframe();
		}

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:

			EndDialog(hWnd, 1);
			break;
		case IDCANCEL:
			EndDialog(hWnd, 0);
			break;
		}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}  

static INT_PTR CALLBACK ExportDlgProc(HWND hWnd, UINT msg,WPARAM wParam, LPARAM lParam)
{
	MyExporter *expo = (MyExporter*)GetWindowLongPtr(hWnd,GWLP_USERDATA); 
	switch (msg) {
	case WM_INITDIALOG:
		expo = (MyExporter*)lParam;
		SetWindowLongPtr(hWnd,GWLP_USERDATA,lParam); 
		CenterWindow(hWnd, GetParent(hWnd));

		//CheckDlgButton(hWnd, IDC_MESHDATA, exp->GetIncludeMesh()); 

		CheckRadioButton(hWnd, IDC_SCENE, IDC_SKELETON, IDC_SCENE);
		

		// Enable / disable mesh options
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:

			if (IsDlgButtonChecked(hWnd,IDC_SCENE)){expo->exportmode = 0;}
			if (IsDlgButtonChecked(hWnd,IDC_SKELETON)){expo->exportmode = 1;}
			if (IsDlgButtonChecked(hWnd,IDC_KEY)){expo->exportmode = 2;}
			if (IsDlgButtonChecked(hWnd,IDC_CHECK1)){expo->fh.vertexlights = true;}else{expo->fh.vertexlights = false;}
			if (IsDlgButtonChecked(hWnd,IDC_CHECK2)){expo->fh.shadowface = true;}else{expo->fh.shadowface = false;}
			if (IsDlgButtonChecked(hWnd,IDC_CHECK3)){expo->fh.tangentspace = true;}else{expo->fh.tangentspace = false;}

			
			EndDialog(hWnd, 1);
			break;
		case IDCANCEL:
			EndDialog(hWnd, 0);
			break;
		}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}  

int MyExporter::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options)
{
    TCHAR buf[256];

    // cache export session stuff for utility methods
    m_exportSelected = (options & SCENE_EXPORT_SELECTED);
    m_suppressPrompts = !!suppressPrompts;
    m_ip = i;
    m_expip = ei;
//	wthis = this;
	exportmode = 0;
	curo =curl = cure= curb =curc=0;
	bh.bonecount = 0;
	if (!DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_IM3),m_ip->GetMAXHWnd(), ExportDlgProc, (long)this)) 
	{
		return 1;
	}

    // open file
    m_fileStream = fopen(name, ("wb"));
    if (!m_fileStream) {
        ::sprintf(buf, GetString(IDS_OPENFILEERR), name);
        ::MessageBox(i->GetMAXHWnd(), buf, GetString(IDS_EXPCAPTION), MB_OK | MB_ICONSTOP);
        return FALSE; // fail
    }
	
	if (DEBUGMODE == 1 || DEBUGMODE == 3)
	{			
		DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_DEBUG),m_ip->GetMAXHWnd(), DebugDlgProc, (long)this);
	}
	else
	{

		if (exportmode == 0)
		{
			DoAll();
		}
		if (exportmode == 1)
		{
			DoSkeletal();
		}
		if (exportmode==2)
		{
			DoKeyframe();	
		}
	}

    return TRUE;
}

MyExporter::~MyExporter()
{
/*	for (int i=0;i<curo;i++)
	{
		delete [] oc[i].cr;
		delete [] oc[i].cg;
		delete [] oc[i].cb;
		oc[i].cr = 0;
		oc[i].cg = 0;
		oc[i].cb = 0;
	}*/
	if (exportmode == 0)
	{
		delete [] oc;oc = 0;
		delete [] lc;lc = 0;
		delete [] ec;ec = 0;
		delete [] tc;tc = 0;
		delete [] cc;cc = 0;
	}
	if (exportmode == 1)
	{
		delete [] bcon;bcon = 0;
	}
	//delete [] dbuffer;dbuffer = 0;
	//delete [] wthis;wthis=0;

	//
}
