#ifndef texfile_h
#define texfile_H



struct TexHeader
{
	long signature;
	long filecount;
};
struct TexFiles
{
	long id;
	char path[64];
	long position;
	long leng;
};

class TexFile // texture container file format
{
private:
	TexHeader header;
	TexFiles* myfiles;

public:
	void LoadTex(char* fname);
	void SaveTex(char* fname);
	void GetTexPos(char* texname);
	void LoadAll();
	void AddFile(char* fname);
	int LoadTexs(char* texname);
};

#endif