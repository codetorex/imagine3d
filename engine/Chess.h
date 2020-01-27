#ifndef CHESS_AI
#define CHESS_AI

#define BOS		0x00
#define BPIYON	0x01
#define BAT		0x02
#define	BFIL	0x03
#define	BKALE	0x04
#define	BSAH	0x05
#define	BVEZIR	0x06
#define SPIYON	0x07
#define SAT		0x08
#define	SFIL	0x09
#define	SKALE	0x10
#define	SSAH	0x1A
#define	SVEZIR	0x1B

void Start(char* m);
bool IsValid(char* m,char sx,char sy,char dx,char dy);		// Hareket dogrumu degilmi
char C(char src);											// Src de ne var 0 = Siyah 1=Beyaz -1=Bos
char P(char x,char y);										// X,Y ye gore pozisyon
int  GetID(char* m);										// Masanin o anki id sini alir
char* N(char src);											// tasin ismini verir ornegin beyaz piyon P siyah p gibi
char GX(char src);
char GY(char src);
#endif