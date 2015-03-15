#pragma once

#include"GAME_BITMAP.h"
#include<stdio.h>
#include"GAME_ROLE.h"
#include"GAME_TEXT.h"
#include"GAME_MAP.h"

struct GOODS
{
	bool ID;
	char name[32];
	int namelenth;
	int bUseful;
	int bEquipe;
	int fun;
	int param1;
	int param2;
	int param3;
};

struct ShowGoods
{
	int seq;
	GOODS gd;
	int num;
};

class MYGOODS :public MYBITMAP
{
private:
	GOODS gd[GOODSNUM];  
	HBITMAP* phcombmp;
	HDC* phdcmem;
	HWND hwnd;
	int goodsnum;
	TEXTPRINT txtool;
	ShowGoods gshow[5];
	GOODS empty,equipe[3];
	int iSelect;
	bool bcontinueUP;
	bool bcontinueDOWN;
public:
	void Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombmp,HDC* hdcmem);
	void LoadGoods();
	void Draw(HDC hdc);
	void List();
	void SelectCur(int selc);
	bool UseGoods();
	bool AddGoods(int ID,int num);
	void DeleteGoods(int seq);
	void DeleteGoods(int seq,int num);
	bool GetbcontinueUP();
	bool GetbcontinueDOWN();
	ShowGoods Getgshow(int seq);
	GOODS Getequipe(int seq);
	GOODS Getgd(int seq);
};