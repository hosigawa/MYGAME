#include"stdafx.h"
#include"GAME_BITMAP.h"
MYBITMAP::MYBITMAP()
{
	ixNum=1;
	iyNum=1;
}

MYBITMAP::~MYBITMAP()
{
	DeleteObject(hbmp);
	DeleteObject(hcombmp);
	DeleteObject(hfont);
	DeleteDC(hdcsrc);
	DeleteDC(hdcdest);
	DeleteObject(hmask);
	DeleteDC(hdcmask);
}
void MYBITMAP::Init(HINSTANCE hins,char* pchar)
{
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(hins,pchar,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	GetObject(hbmp,sizeof(BITMAP),&bm);
	cxBmp=bm.bmWidth;
	cyBmp=bm.bmHeight;
}

void MYBITMAP::Device(HDC hdc)
{
	if(hcombmp)
		DeleteObject(hcombmp);
	hcombmp=CreateCompatibleBitmap(hdc,cxBmp/ixNum,cyBmp/iyNum);
	if(hmask)
		DeleteObject(hmask);
	hmask=CreateBitmap(cxBmp,cyBmp,1,1,NULL);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdc);
	if(hdcsrc)
		DeleteDC(hdcsrc);
	hdcsrc=CreateCompatibleDC(hdc);
	SelectObject(hdcsrc,hmask);
	SelectObject(hdcdest,hbmp);
	oldColor=SetBkColor(hdcdest,RGB(0,1,0));
	BitBlt(hdcsrc,0,0,cxBmp,cyBmp,hdcdest,0,0,SRCINVERT);
	SetBkColor(hdcdest,oldColor);
}

void MYBITMAP::SetPos(int x,int y)
{
	pos.x=x*32;
	pos.y=y*32-16;
}

POINT MYBITMAP::Getpos()
{
	return pos;
}

void MYBITMAP::Draw(HDC hdc,float x,float y)
{
	SelectObject(hdcdest,hcombmp);
	SelectObject(hdcsrc,hbmp);
	BitBlt(hdcdest,0,0,cxBmp,cyBmp,hdcsrc,0,0,SRCCOPY);
	StretchBlt(hdc,pos.x,pos.y,x*cxBmp,y*cyBmp,hdcdest,0,0,cxBmp,cyBmp,SRCCOPY);
}

