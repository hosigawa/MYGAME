#pragma once

#define BATTLERNUM 2
#include"GAME_BITMAP.h"
#include"GAME_ROLE.h"
#include"GAME_TEXT.h"
#include"GAME_GOODS.h"

class MYBATTLE : public MYBITMAP
{
private:
	HBITMAP* phcombmp;
	HDC* phdcmem;
	HWND hwnd;
	HDC hdcbattle;
	HBITMAP hbmpbattle;
	MYGOODS* pmg;
	MAN battler[BATTLERNUM];
	MAN Anima[10];
	int enemyID,igamebool;
	int iSelect,iSelectTools;
	int iAnimaTime;
	bool bEnemyAction,bAtacMove,bBackMove,bAttack,bUseGoods[4],bwin,bupdate;
	TEXTPRINT txtool;
public:
	~MYBATTLE();
	void Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombmp,HDC* hdcmem,MYGOODS* pmg);
	void Draw(HDC hdc);
	void GetEnemy(int enemyID,int iGamebool);
	void Entry();
	void SelectCur(int selc,int iMax);
	void Attack();
	void BattleMove();
	void UseGoods();
	bool GetbUseGoods(int seq);
	void SetbUseGoods(int seq,bool tf);
	bool Getbwin();
	MAN & Getbattler(int seq);
	void SetbEnemyAction(bool tf);
	bool GetbEnemyAction();
	void SetbAtacMove(bool tf);
	bool GetbAtacMove();
	void SetbBackMove(bool tf);
	bool GetbBackMove();
};