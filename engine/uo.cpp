#include "uo.h"



long c16to32(uword color16)
{
	return ( (((color16 >> 10) & 0x1F) * 0xFF / 0x1F) | ((((color16 >> 5) & 0x1F) * 0xFF / 0x1F) << 8) | ((( color16 & 0x1F) * 0xFF / 0x1F) << 16));
}

void testt()
{
	IBitmap bmap;
	FILE* map0;
	FILE* radarcol;
	map0 = fopen("C://program files//ultima online//map0.mul","rb");
	radarcol = fopen("C://program files//ultima online//radarcol.mul","rb");
	long wi = 768;
	long hi = 512;
	map_block blocks[16];




	//((XBlock * BlockHeight) + YBlock) * 196
	//((CellY * 8) + CellX) * 3

	fclose(map0);
	fclose(radarcol);



}