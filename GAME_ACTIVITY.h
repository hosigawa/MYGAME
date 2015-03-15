#pragma once

#include"GAME_MAP.h"
#include"GAME_ROLE.h"

class ACTIVITY
{
private:
	HBITMAP* hbmp;
	HDC* hdcm;
	HWND hwnd;
	int iplace;
	HDC hdc;
	HINSTANCE hins;
	char CurrentMap[32];
	bool bPlaysound;
public:
	void Init(HINSTANCE hinst,HWND hWnd,HBITMAP* hbmp,HDC* hdcm);
	void OnMap(char* path);             //�����ͼ
	void OnMan(char* path);				//������������
	void OnNpc(char* path);
	void OnAct(char* path);
	void MapChange();
	void SetCurrentMap(char* path);
	char* GetCurrentMap();
	bool GetbPlaysound();
	void SetbPlaysound(bool tf);
	int SerchText();
};