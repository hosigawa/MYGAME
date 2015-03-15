#pragma once

#include "resource.h"
#include "GAME_BITMAP.h"
#include"GAME_MAP.h"
#include"GAME_ROLE.h"
#include"GAME_KEY.h"
#include"GAME_ACTIVITY.h"
#include"GAME_TIMER.h"
#include"GAME_TEXT.h"
#include"GAME_FACE.h"
#include"GAME_SAVE.h"
#include"GAME_GOODS.h"
#include"GAME_BATTLE.h"
#include"GAME_STATE.h"
#include"GAME_CONFIRM.h"
#include"GAME_SHOP.h"
#include<Windows.h>

class GAMEMAIN
{
public:
	ACTIVITY act;
	KEYPROC key;
	HINSTANCE hins;
	HWND hwnd;
	HBITMAP hcombmp;
	HDC hdc,hdcmem;
	TIMER tim;
	MAINFACE mf;
	MENUFACE mef;
	SAVEGAME sav;
	MYGOODS mg;
	MYBATTLE mb;
	MANSTATE ms;
	MYCONFIRM mc;
	MYSHOP msp;
	TEXTPRINT tx;
	int gamew,gameh;
public:
	~GAMEMAIN();
	void Init(HINSTANCE,HWND,int gamew,int gameh);
	void Show(HDC);
	void CheckState();
};
