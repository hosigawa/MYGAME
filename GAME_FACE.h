#pragma once

#include"GAME_BITMAP.h"
#include"GAME_SAVE.h"

class MAINFACE : public MYBITMAP
{
protected:
	HBITMAP* phcombmp;
	HDC* phdcmem;
	HWND hwnd;
	SAVEGAME* save;
	int iSelcNum;
	bool bMapInit;
public:
	void Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombmp,HDC* hdcmem,SAVEGAME* sa);
	void Draw(HDC hdc);
	void SelectCur(int selc,int iMax);
	void Entry();
	void SetbMapInit(bool tf);
	bool GetbMapInit();
};

class MENUFACE:public MAINFACE
{
public:
	void Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombmp,HDC* hdcmem,SAVEGAME* sa);
	void Draw(HDC hdc);
	void Entry();
};