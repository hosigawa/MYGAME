#pragma once

#include"GAME_BITMAP.h"
#include"GAME_SAVE.h"
#include"GAME_ROLE.h"
#include"GAME_TEXT.h"
#include"GAME_GOODS.h"

class MANSTATE : public MYBITMAP
{
private:
	HBITMAP* phcombmp;
	HDC* phdcmem;
	HWND hwnd;
	int iSelect;
	MYGOODS* pmg;
	TEXTPRINT txtool;
public:
	void Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombmp,HDC* hdcmem,MYGOODS* pmg);
	void Draw(HDC hdc);
	void SetCur(int select);
	int GetiSelect();
};