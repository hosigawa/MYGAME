#pragma once

#include"GAME_BITMAP.h"
#include"GAME_GOODS.h"
#include"GAME_TEXT.h"
#include"GAME_SHOP.h"

class MYCONFIRM : public MYBITMAP
{
private:
	HBITMAP* phcombmp;
	HDC* phdcmem;
	HWND hwnd;
	MYGOODS* pmg;
	MYSHOP* pmsp;
	TEXTPRINT txtool;
	int igamestate;
	int iSelect;
	int param1,param2;
public:
	void Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme,MYGOODS* pmg,MYSHOP* msp);
	void Draw(HDC hdc);
	void Confirm(int igamestate);
	void Confirm(int igamestate,int param);
	void Confirm(int igamestate,int param1,int param2);
	void SelectCur(int selc);
	void entry();
	int Getigamestate();
};