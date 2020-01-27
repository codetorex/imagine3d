#include "cbone.h"
#include <fstream.h>
#include "cvision.h"
#include "cvector3f.h"
#include "cgui.h"

char bug[100];
void addbug();




void addbug()
{
	FILE * b= 0;
	b = fopen("c://bug.log","a+");
	fprintf(b,"%s\n",bug);
	fclose(b);
}