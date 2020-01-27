#include "chess.h"

bool IsValid(char* m,char sx,char sy,char dx,char dy)
{
	if (P(sx,sy) == -1 || P(dx,dy) == -1) return false;
	char t1,t2; // types
	t1 = m[P(sx,sy)];
	t2 = m[P(dx,dy)];
	int i;
	bool tb=true;
	if (C(t1) == C(t2)) return false; // bos-bos beyaz-beyaz siyah-siyah oynamak yasak
	if (t1 == BPIYON)
	{
		if (sy==1 && dy-sy==2 && sx==dx && t2 == BOS && m[P(dx,dy-1)] == BOS) return true;
		if ((dx==sx-1 || dx==sx+1) && dy==sy+1 && C(t2) == 0) return true;
		if (dx==sx && dy==sy+1 && t2 == BOS) return true;
	}
	if (t1 == SPIYON)
	{
		if (sy==6 && sy-dy==2 && sx==dx && t2 == BOS && m[P(dx,dy+1)] == BOS) return true;
		if ((dx==sx-1 || dx==sx+1) && dy==sy-1 && C(t2) == 1) return true;
		if (dx==sx && dy==sy-1 && t2 == BOS) return true;
	}
	if (t1 == BAT || t1 == SAT)
	{
		if (((dy-sy==2 ||sy-dy==2) && (dx==sx+1 || dx==sx-1)) || ((dy-sy==1 || sy-dy==1) && (dx==sx+2 || dx==sx-2)))
			return true;
	}
	if (t1 == BFIL || t1 == SFIL || t1 == BVEZIR || t1 == SVEZIR)
	{
		if (sx-dx == sy-dy ||sx-dx == -sy-dy)
		{
			return true;
		}
		else
		{
			return false;
		}

		//pop 2
	}
	if ((t1 == BKALE || t1 == SKALE || t1 == BVEZIR || t1 == SVEZIR) && (dx==sx || sy==dy))
	{
		if (dy-sy>0){
			for(i=sy;i<dy;i++){
				if(m[P(sx,i)] != BOS) tb = false;}
			if(tb=true) return true;
		}
		if (dy-sy<0){
			for(i=dy;i<sy;i++){
				if(m[P(sx,i)] != BOS) tb = false;}
			if(tb=true) return true;
		}
		if (dx-sx>0){
			for(i=sx;i<dx;i++){
				if(m[P(i,sy)] != BOS) tb = false;}
			if(tb=true) return true;
		}
		if (dx-sx<0){
			for(i=dx;i<sx;i++){
				if(m[P(i,sy)] != BOS) tb = false;}
			if(tb=true) return true;
		}
	}
	if (t1 == SSAH || t1 == BSAH)
	{
		//if(IsCheck(dx,dy) == false) return false;
		if((dx==sx && (dy==sy+1 || dy==sy-1)) || (dy==sy && (dx==sx+1 || dx==sx-1)) || ((dx==sx+1 || dx==sx-1) && (dy==sy+1 || dy==sy-1)) && (C(t2)==0 || t2 == BOS))
			return true;
	}

	return false;
}

char C(char src)
{
	switch (src)
	{
	case BPIYON:
	case BAT:
	case BFIL:
	case BKALE:
	case BSAH:
	case BVEZIR:
		return 1;
		break;
	case SPIYON:
	case SAT:
	case SFIL:
	case SKALE:
	case SSAH:
	case SVEZIR:
		return 0;
		break;
	default:
		return -1;
		break;
	}
} // 1 = beyaz 0= siyah -1=tas yok

char P(char x,char y)
{
	if (x <0 || x>64) return -1;
	if (y <0 || y>64) return -1;
	return (8 * y) + x;
}

void Start(char* m)
{
	for (int i=0;i<64;i++) 
	{
		m[i] = BOS;
	};
	m[P(0,0)] = BKALE;		m[P(0,7)] = SKALE;
	m[P(1,0)] = BAT;		m[P(1,7)] = SAT;
	m[P(2,0)] = BFIL;		m[P(2,7)] = SFIL;
	m[P(3,0)] = BVEZIR;		m[P(3,7)] = SVEZIR;
	m[P(4,0)] = BSAH;		m[P(4,7)] = SSAH;
	m[P(5,0)] = BFIL;		m[P(5,7)] = SFIL;
	m[P(6,0)] = BAT;		m[P(6,7)] = SAT;
	m[P(7,0)] = BKALE;		m[P(7,7)] = SKALE;
	m[P(0,1)] = BPIYON;		m[P(0,6)] = SPIYON;
	m[P(1,1)] = BPIYON;		m[P(1,6)] = SPIYON;
	m[P(2,1)] = BPIYON;		m[P(2,6)] = SPIYON;
	m[P(3,1)] = BPIYON;		m[P(3,6)] = SPIYON;
	m[P(4,1)] = BPIYON;		m[P(4,6)] = SPIYON;
	m[P(5,1)] = BPIYON;		m[P(5,6)] = SPIYON;
	m[P(6,1)] = BPIYON;		m[P(6,6)] = SPIYON;
	m[P(7,1)] = BPIYON;		m[P(7,6)] = SPIYON;
}

int  GetID(char* m)
{
	int a=0;
	for (int i =0;i<64;i++)
	{
		a+=m[i];
	}
	return a;
}

char* N(char src)
{
	switch (src)
	{
	case BPIYON:
		return "P";
		break;
	case BAT:
		return "A";
		break;
	case BFIL:
		return "F";
		break;
	case BKALE:
		return "K";
		break;
	case BSAH:
		return "S";
		break;
	case BVEZIR:
		return "V";
		break;
	case SPIYON:
		return "p";
		break;
	case SAT:
		return "a";
		break;
	case SFIL:
		return "f";
		break;
	case SKALE:
		return "k";
		break;
	case SSAH:
		return "s";
		break;
	case SVEZIR:
		return "v";
		break;
	case BOS:
		return " ";
		break;
	}
}

char GX(char src)
{
	return src%8;
}

char GY(char src)
{
	return (src-src%8)/8;
}