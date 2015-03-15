#pragma once
#include<Windows.h>
#include"GAME_KEY.h"
#include"GAME_ROLE.h"


class TIMER
{
private:
	HWND hwnd;
	ACTIVITY* pact;
	KEYPROC* pkey;
	MYBATTLE* pmb;
	int t0,tDraw;
public:
	~TIMER();
	void Init(HWND hwnd,ACTIVITY* act,KEYPROC* key,MYBATTLE* pmb);
	void CheckTime(WPARAM wParam);
	void Draw();
	void RoleWalk();
};