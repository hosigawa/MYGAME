#include"stdafx.h"
#include"GAME_TIMER.h"

extern int GameState;
extern MAN man;
extern MAP map;
extern GAMENPC npc;

TIMER::~TIMER()
{
	for(int i=0;i<4;i++)
	{
		KillTimer(hwnd,i);
	}
}

void TIMER::Init(HWND hWnd,ACTIVITY* act,KEYPROC* key,MYBATTLE* mb)
{
	hwnd=hWnd;
	pact=act;
	pkey=key;
	pmb=mb;
	SetTimer(hwnd,0,15,NULL);//画面刷新定时器
	SetTimer(hwnd,1,200,NULL);//行走动作间隔计时器
	SetTimer(hwnd,2,15,NULL);//移动速度计时器
	SetTimer(hwnd,3,100,NULL);//战斗动画计时器
}

void TIMER::CheckTime(WPARAM wParam)
{
	switch(wParam)
	{
	case 0:
		Draw();
		break;
	case 1:
		RoleWalk();
		break;		
	case 2:
		if(GameState==NORMALMODE)
		{
			npc.NpcMove();
			man.RoleMove();
			if(!man.Getbchangemap())
				pact->MapChange();
		}
		else if(GameState==BATTLEMODE)
		{
			pmb->BattleMove();
		}
		break;
	case 3:
		if(GameState==BATTLEMODE)
		{
			pmb->UseGoods();
		}
		break;
	}
}

void TIMER::Draw()
{
	InvalidateRect(hwnd,NULL,false);
}

void TIMER::RoleWalk()
{
	if(man.GetbRolerun())
	{
		man.RoleAnima();
	}
	else
		man.SetiFrame(0);
	for(int i=0;i<npc.NpcNum;i++)
	{
		if(npc.man[i].GetbRolerun())
		{
			npc.man[i].RoleAnima();
		}
		else
			npc.man[i].SetiFrame(0);
	}
	if(pmb->GetbAtacMove()||pmb->GetbBackMove())
	{
		if(!pmb->GetbEnemyAction())
		{
			pmb->Getbattler(0).RoleAnima();
		}
		else
		{
			pmb->Getbattler(1).RoleAnima();
		}
	}
}