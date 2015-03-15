#pragma once

#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#include"GAME_BITMAP.h"
#include"GAME_MAP.h"

struct ManData
{
	char name[32];
	char path[32];
	char sex[2];
	int bVisible;
	int bWalk;
	int enemy;
	int Id;
	int Level;
	int Exp;
	int Health;
	int Power;
	int Define;
	int Magic;
	int Speed;
};

struct Pocket
{
	int ID;
	int num;
};

struct Equipe
{
	int hand;
	int body;
	int foot;
};

class MAN : public MYBITMAP
{
private:
	bool bRolerun;
	bool bchangemap;             //判断是否刚切换地图
	int iFrame,wens;
	POINT opos;					//用来判断前进的距离是否达到32
	ManData mand;
	Pocket pk[20];
	Equipe eq;
	int money;
public:
	void Init(HINSTANCE hinstance,char* pchar,int ixNum,int iyNum);
	void Draw(HDC hdc,float xMultiple,float yMultiple);
	void RoleMove();
	ManData GetMand();
	void SetMand(ManData md);
	void Setpk(int seq,Pocket pk);
	Pocket Getpk(int seq);
	void SetEquipe(Equipe eq);
	Equipe GetEquipe();
	void SetMoney(int money);
	int GetMoney();
	void SetbRolerun(bool);
	bool GetbRolerun();
	void Setbchangemap(bool);
	bool Getbchangemap();
	void Setwens(int wens);
	int Getwens();
	void SetiFrame(int frame);
	void RoleAnima();
	void MovePos(int x,int y);
	void MakeSyn();       //把当前坐标赋给old坐标
	POINT Getopos();
	void Setopos(int x,int y);
	bool NoNPC(int wens);
	void MovePlace(int wens);
};

class GAMENPC
{
public:
	MAN man[64];
	int NpcNum;
	bool bchange;
public:
	//void LoadNpc(HINSTANCE instance,char* pchar);
	void NpcMove();
};

