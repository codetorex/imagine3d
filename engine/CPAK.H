
#ifndef CPAK_H
#define CPAK_H


struct pakheader
{
	int signature;
	int diroffset;
	int dirlength;
};

struct pakdir
{
	char filename[56];
	int filepos;
	int filelength;
};

class CPak
{
private:
	pakheader	hPAK;
	pakdir*		dPAK;
	int filecount;
	char* curfile;

public:
	void OpenPak (char* filename);
	int ReturnPos (char* fname);
};


#endif