#pragma once

#include"GAME_ACTIVITY.h"
#include"GAME_FACE.h"
#include"GAME_BATTLE.h"
#include"GAME_GOODS.h"
#include"GAME_CONFIRM.h"
#include"GAME_STATE.h"
#include"GAME_SHOP.h"

class KEYPROC
{
private:
	ACTIVITY* pact;
	MAINFACE* pmf;
	MENUFACE* pmef;
	MYBATTLE* pmb; 
	MYGOODS* pmg;
	TEXTPRINT* ptx;
	MYCONFIRM* pmc;
	MANSTATE* pms;
	MYSHOP* pmsp;
	int Selecttx;
	//int reSelecttx;
	int iChangeCloth;
	HWND hwnd;
public:
	void Init(ACTIVITY* act,MAINFACE* mf,MENUFACE* pmef,MYBATTLE* pmb,MYGOODS* pmg,TEXTPRINT* tx,MYCONFIRM* pmc,MANSTATE* pms,MYSHOP* pmsp);
	void KeyDwon(HWND hWnd,WPARAM wParam,LPARAM lParam); 
	void KeyUp();
	void KeyNormal(HWND hWnd,WPARAM wParam,LPARAM lParam); 
	void KeyFace(HWND hWnd,WPARAM wParam);
	void KeyMenu(HWND hWnd,WPARAM wParam);
	void KeyTalk(HWND hWnd,WPARAM wParam);
	void KeyGoods(HWND hWnd,WPARAM wParam);
	void KeyBattle(HWND hWnd,WPARAM wParam);
	void KeyBattleMenu(HWND hWnd,WPARAM wParam);
	void KeyState(HWND hWnd,WPARAM wParam);
	void KeyBattleSubMenu(HWND hWnd,WPARAM wParam);
	void KeyConfirm(HWND hWnd,WPARAM wParam);
	void KeyShop(HWND hWnd,WPARAM wParam);
	void KeyShopSub(HWND hWnd,WPARAM wParam);
	void SetAction(TextData txtmp);
	void SetSelecttx(int i);
	int GetSelecttx();
};
