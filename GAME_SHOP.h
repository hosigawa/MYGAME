#pragma once

#include"GAME_BITMAP.h"
#include"GAME_SAVE.h"
#include"GAME_ROLE.h"
#include"GAME_TEXT.h"
#include"GAME_GOODS.h"


struct ShopGoods
{
	int ID;
	int price;
};

class MYSHOP : public MYBITMAP
{
private:
	HBITMAP* phcombmp;
	HDC* phdcmem;
	HWND hwnd;
	int iSelect,iSubSelect;
	MYGOODS* pmg;
	TEXTPRINT txtool;
	ShopGoods sg[20];
	int shopmode;        //不同的商店种类
	bool nomoney;
public:
	void Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombmp,HDC* hdcmem,MYGOODS* pmg);
	void Draw(HDC hdc);
	void SetCur(int select);
	void SetSubCur(int select);
	void entry();
	Name GetName(int ID);
	void SetShopMode(int mode);
	int GetPrice();
	void BuySell(int mode);
	int GetiSelect();
	int GetiSubSelect();
	bool Getnomoney();
	ShopGoods Getsg(int seq);
};