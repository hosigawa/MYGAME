#pragma once

#include"GAME_MAP.h"
#include"GAME_ROLE.h"
#include"GAME_ACTIVITY.h"
#include<fstream>
#include<iostream>
#include<stdlib.h>

struct SAVEDATA
{
	char mappath[32];
	POINT pt;
};

class SAVEGAME
{
private:
	SAVEDATA savedata;
	ACTIVITY* act;
	bool iSavlod;
public:
	void Init(ACTIVITY* act);
	void Savegame();
	void Loadgame();
	void SetiSavlod(bool tf);
	bool GetiSavlod();
};