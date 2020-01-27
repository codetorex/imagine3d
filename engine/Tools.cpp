#include "tools.h"
#include <windows.h>

void LongToChar(unsigned char* bytearray,int value,int start)
{
	unsigned char* temp;
	temp = new unsigned char [4];
	memcpy(temp,&value,4);
	bytearray[start + 0] = temp[0];
	bytearray[start + 1] = temp[1];
	bytearray[start + 2] = temp[2];
	bytearray[start + 3] = temp[3];
	delete [] temp;
};

void wastemem(unsigned char* bytearray,int sizeb)
{
	for (int i=0;i<sizeb;i++)
	{
		bytearray[i] = 0x00;
	};
};

int GenID(char* st)
{
	int te=0;
	for (int i=0;i<strlen(st);i++)
	{
		te += st[i];
	}
	return te;
}

void LTC(unsigned char* bytearray,int value,int start)
{
	unsigned char* temp;
	temp = new unsigned char [4];
	memcpy(temp,&value,4);
	bytearray[start + 0] = temp[0];
	bytearray[start + 1] = temp[1];
	bytearray[start + 2] = temp[2];
	bytearray[start + 3] = temp[3];
	delete [] temp;
};
