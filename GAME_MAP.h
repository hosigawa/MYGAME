#pragma once

#include"GAME_BITMAP.h"

struct MapData
{
	int iGroud;
	int iSecond;
	int iThird;
	int ispecial;
	int iMapPoint;
	char MapName[32];
};

class MAP:public MYBITMAP
{
private:
	POINT View;
	HWND hwnd;
	int gamew,gameh;
	int mapw,iblocks,sourcew;
	MapData* mapd;
	char Music[32];
public:	
	MAP();
	~MAP();
	void GetClntInfo(HWND hwnd,LPARAM lParam);
	void Init(HINSTANCE hinstance,char* pchar);
	void Device(HDC hdc);
	void Draw(HDC hdc);
	int Getiblocks();
	int Getmapw();
	int Getgamew();
	int Getgameh();
	void SetView(POINT pt);
	POINT GetView();
	MapData Getmapd(int seq);
	char* GetMusic();
};
