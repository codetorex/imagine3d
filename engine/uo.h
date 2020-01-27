#ifndef ULTIMA_ONLINE
#define ULTIMA_ONLINE

#include "cbitmap.h"

typedef unsigned short uword;


struct map_cell
{
	short TileID;
	char Z;
};

struct map_block
{
	int header;
	map_cell cells[64];
};

long c16to32(uword color16);
void testt();

 
#endif