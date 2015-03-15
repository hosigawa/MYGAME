#pragma once
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include "Resource.h"
#include<Windows.h>


class MYBITMAP  
{
protected:
	HDC hdcdest,hdcsrc,hdcmask;
	HBITMAP hbmp,hcombmp,hmask;
	BITMAP bm;
	HFONT hfont;
	int cxBmp,cyBmp;
	POINT pos;
	int ixNum,iyNum;     //横竖方向图片的个数
	COLORREF oldColor;
public:
	MYBITMAP();
	~MYBITMAP();
	void Init(HINSTANCE hinstance,char* str);
	void Device(HDC hdc);
	void SetPos(int xpos,int ypos);
	POINT Getpos();
	void Draw(HDC,float xMultiple,float yMultiple);
};







