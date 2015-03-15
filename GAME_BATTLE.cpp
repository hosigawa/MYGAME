#include "StdAfx.h"
#include<stdio.h>
#include"GAME_BATTLE.h"

extern MAN man;
extern GAMENPC npc;
extern int GameState;
extern bool GameBool[512];

MYBATTLE::~MYBATTLE()
{
	DeleteDC(hdcbattle);
	DeleteObject(hbmpbattle);
}

void MYBATTLE::Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme,MYGOODS* mg)
{
	phdcmem=hdcme;
	phcombmp=hcombm;
	hwnd=hWnd;
	pmg=mg;
	HDC hdc=GetDC(hWnd);
	if(*phcombmp)
		DeleteObject(*phcombmp);
	*phcombmp=CreateCompatibleBitmap(hdc,640,480);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdc);
	SelectObject(*phdcmem,*phcombmp);
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/battlebmp.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	SelectObject(hdcdest,hbmp);
	ManData md;
	md=man.GetMand();
	md.bVisible=1;
	battler[0].SetMand(md);
	battler[0].Init(hinstance,man.GetMand().path,4,4);
	battler[0].Device(hdc);
	battler[0].SetPos(5,5);
	md.bVisible=0;
	Anima[0].Init(hinstance,"pic/role/attack.bmp",5,2);
	Anima[0].Setwens(LEFT);
	Anima[0].SetiFrame(1);
	Anima[0].SetMand(md);
	Anima[1].Init(hinstance,"pic/role/box.bmp",4,4);
	Anima[1].Setwens(0);
	Anima[1].SetiFrame(1);
	Anima[1].SetMand(md);
	for(int i=0;i<2;i++)
		Anima[i].Device(hdc);
	iAnimaTime=0;
	if(!bwin)
		battler[0].Setwens(RIGHT);
	battler[1].Init(hinstance,battler[1].GetMand().path,4,4);
	battler[1].Device(hdc);
	battler[1].SetPos(13,5);
	battler[1].Setwens(LEFT);
	ReleaseDC(hwnd,hdc);
}

void MYBATTLE::GetEnemy(int enemy,int gamebool)
{
	enemyID=enemy;
	igamebool=gamebool;
	/*
	battler[0].mand.Power=man.mand.Power+pmg->Equipe[0].param1;
	battler[0].mand.Define=man.mand.Define+pmg->Equipe[1].param1;
	battler[0].mand.Speed=man.mand.Speed+pmg->Equipe[2].param1;
	*/
	battler[1].SetMand(npc.man[enemyID].GetMand());
	bwin=0;
	bupdate=0;
	PlaySound("sound/battle02.wav",NULL,SND_LOOP|SND_ASYNC);
}

void MYBATTLE::SelectCur(int selc,int iMax)
{
	switch(selc)
	{
	case 0:
		iSelect--;
		if(iSelect==-1)
			iSelect=iMax-1;
		break;
	case 1:
		iSelect++;
		if(iSelect==iMax)
			iSelect=0;
		break;
	}
}


void MYBATTLE::Draw(HDC hdc)
{
	BitBlt(hdc,0,0,640,480,hdcdest,0,0,SRCCOPY);
	for(int i=0;i<BATTLERNUM;i++)
			battler[i].Draw(hdc,1.4,1.4);
	for(int i=0;i<5;i++)
			Anima[i].Draw(hdc,1,1);
	if(!bwin)
	{
		txtool.TextOutTx(hdc,430,350,"生命值：",sizeof("生命值：")-1,txtool.SetFont(RGB(255,255,255),20,10));
		txtool.TextOutTx(hdc,520,350,txtool.itos(man.GetMand().Health).snum,txtool.itos(man.GetMand().Health).lenth,txtool.SetFont(RGB(255,255,255),20,10));
		txtool.TextOutTx(hdc,530+10*txtool.itos(man.GetMand().Health).lenth,350,"/",1,txtool.SetFont(RGB(255,255,255),20,10));
		txtool.TextOutTx(hdc,540+10*txtool.itos(man.GetMand().Health).lenth,350,txtool.itos(man.GetMand().Level*10).snum,txtool.itos(man.GetMand().Level*10).lenth,txtool.SetFont(RGB(255,255,255),20,10));
	}
	if(GameState==BATTLEMENUMODE)
	{
		if(!bwin)
		{
			switch(iSelect)
			{
			case 0:
				txtool.TextOutTx(hdc,50,350,"战斗",sizeof("战斗")-1,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				txtool.TextOutTx(hdc,50,370,"物品",sizeof("物品")-1,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,50,390,"逃跑",sizeof("逃跑")-1,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				break;
			case 1:
				txtool.TextOutTx(hdc,50,350,"战斗",sizeof("战斗")-1,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,50,370,"物品",sizeof("物品")-1,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				txtool.TextOutTx(hdc,50,390,"逃跑",sizeof("逃跑")-1,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				break;
			case 2:
				txtool.TextOutTx(hdc,50,350,"战斗",sizeof("战斗")-1,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,50,370,"物品",sizeof("物品")-1,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,50,390,"逃跑",sizeof("逃跑")-1,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				break;
			}
		}
		else
		{
			txtool.TextOutTx(hdc,50,350,"战斗胜利！",sizeof("战斗胜利！")-1,txtool.SetFont(RGB(255,255,255),20,12));
			if(bupdate)
				txtool.TextOutTx(hdc,50,400,"经过不断磨练，战斗力更加精进了！",sizeof("经过不断磨练，战斗力更加精进了！")-1,txtool.SetFont(RGB(255,255,255),20,12));
		}
	}
	else if(GameState==BATTLESUBMENUMODE)
	{
		txtool.TextOutTx(hdc,50,350,"战斗",sizeof("战斗")-1,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
		txtool.TextOutTx(hdc,50,370,"物品",sizeof("物品")-1,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
		txtool.TextOutTx(hdc,50,390,"逃跑",sizeof("逃跑")-1,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
		txtool.TextOutTx(hdc,150,350,pmg->Getgshow(0).gd.name,pmg->Getgshow(0).gd.namelenth,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),15,12));
		if(pmg->Getgshow(0).gd.ID)
			txtool.TextOutTx(hdc,160+pmg->Getgshow(0).gd.namelenth*12,350,txtool.itos(pmg->Getgshow(0).num).snum,txtool.itos(pmg->Getgshow(0).num).lenth,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),15,12));
		for(int i=1;i<5;i++)
		{
			if(pmg->Getgshow(i).gd.ID)
			{
				txtool.TextOutTx(hdc,150,350+i*15,pmg->Getgshow(i).gd.name,pmg->Getgshow(i).gd.namelenth,txtool.SetFont(RGB(255,255,255),15,12));
				txtool.TextOutTx(hdc,160+pmg->Getgshow(i).gd.namelenth*12,350+i*15,txtool.itos(pmg->Getgshow(i).num).snum,txtool.itos(pmg->Getgshow(i).num).lenth,txtool.SetFont(RGB(255,255,255),15,12));
			}
		}
		if(pmg->GetbcontinueUP())
			txtool.TextOutTx(hdc,210,330,"▲",2,txtool.SetFont(RGB(255,255,255),20,10));
		if(pmg->GetbcontinueDOWN())
			txtool.TextOutTx(hdc,210,430,"▼",2,txtool.SetFont(RGB(255,255,255),20,10));
	}
}

bool MYBATTLE::GetbUseGoods(int seq)
{
	return bUseGoods[seq];
}

void MYBATTLE::SetbUseGoods(int seq,bool tf)
{
	bUseGoods[seq]=tf;
}

bool MYBATTLE::Getbwin()
{
	return bwin;
}

void MYBATTLE::SetbEnemyAction(bool tf)
{
	bEnemyAction=tf;
}

bool MYBATTLE::GetbEnemyAction()
{
	return bEnemyAction;
}

void MYBATTLE::SetbAtacMove(bool tf)
{
	bAtacMove=tf;
}

bool MYBATTLE::GetbAtacMove()
{
	return bAtacMove;
}

void MYBATTLE::SetbBackMove(bool tf)
{
	bBackMove=tf;
}

bool MYBATTLE::GetbBackMove()
{
	return bBackMove;
}

MAN & MYBATTLE::Getbattler(int seq)
{
	return battler[seq];
}

void MYBATTLE::Attack()
{
	char temp[32]={};
	int iHurt;
	if(!bEnemyAction)
	{
		float ranA=(75+rand()%50);
		float ranD=(90+rand()%20);
		iHurt=((man.GetMand().Power+pmg->Getequipe(0).param1)*ranA-battler[1].GetMand().Define*ranD)/100;
		if(iHurt<=0)
			iHurt=1;
	}
	else if(bEnemyAction)
	{
		float ranA=(75+rand()%50);
		float ranD=(90+rand()%20);
		iHurt=(battler[1].GetMand().Power*ranA-(man.GetMand().Define+pmg->Getequipe(1).param1)*ranD)/100;
		if(iHurt<=0)
			iHurt=1;
	}
	
	sscanf("-","%s",temp);
	sscanf(txtool.itos(iHurt).snum,"%s",temp+1);
	if(!bEnemyAction)
	{
		int ran=rand()%100;
		ManData md;
		if(ran<=(100*(man.GetMand().Speed+pmg->Getequipe(2).param1)/((man.GetMand().Speed+pmg->Getequipe(2).param1)+battler[1].GetMand().Speed)))
		{
			txtool.TextOutTx(hdcdest,416,80,temp,txtool.itos(iHurt).lenth+1,txtool.SetFont(RGB(255,0,0),30,20));
			md=battler[1].GetMand();
			md.Health=max(0,md.Health-iHurt);
			battler[1].SetMand(md);
		}
		else
		{
			txtool.TextOutTx(hdcdest,416,80,"MISS",4,txtool.SetFont(RGB(0,0,255),25,15));
		}
	}
	else
	{
		int ran=rand()%100;
		ManData md;
		if(ran<=(100*battler[1].GetMand().Speed/((man.GetMand().Speed+pmg->Getequipe(2).param1)+battler[1].GetMand().Speed)))
		{
			txtool.TextOutTx(hdcdest,160,80,temp,txtool.itos(iHurt).lenth+1,txtool.SetFont(RGB(255,0,0),30,20));
			md=man.GetMand();
			md.Health=max(0,md.Health-iHurt);
			man.SetMand(md);
		}
		else
		{
			txtool.TextOutTx(hdcdest,160,80,"MISS",4,txtool.SetFont(RGB(0,0,255),25,15));
		}
	}
	
	if(battler[1].GetMand().Health<=0)
	{
		PlaySound("sound/celebration.wav",NULL,SND_LOOP|SND_ASYNC);
		ManData md;
		md=battler[1].GetMand();
		md.bVisible=false;
		battler[1].SetMand(md);
		bwin=1;
		md=man.GetMand();
		md.Exp++;
		if(md.Exp==man.GetMand().Level+1)
		{
			bupdate=1;
			md.Power+=md.Level;
			md.Define+=md.Level/2;
			md.Speed+=md.Level/5;
			md.Level++;
			md.Exp=0;
		}
		man.SetMand(md);
		md=npc.man[enemyID].GetMand();
		md.bVisible=0;
		npc.man[enemyID].SetMand(md);
		if(igamebool!=0)
			GameBool[igamebool]=true;
	}
}

void MYBATTLE::Entry()
{
	ManData md;
	switch(iSelect)
	{
	case 0:
		bAtacMove=1;
		GameState=BATTLEMODE;
		break;
	case 1:
		GameState=BATTLESUBMENUMODE;
		break;
	case 2:
		GameState=NORMALMODE;
		break;
	}
}

void MYBATTLE::BattleMove()
{
	if(bAtacMove)
	{
		if(!bEnemyAction)
			battler[0].MovePos(3,0);
		else
			battler[1].MovePos(-3,0);
		if(battler[0].Getpos().x>=384)
		{
			ManData md;
			bAtacMove=0;
			Anima[0].SetPos(11,3);
			md.bVisible=1;
			Anima[0].SetMand(md);
			bAttack=1;
		}
		else if(battler[1].Getpos().x<=192)
		{
			ManData md;
			bAtacMove=0;
			Anima[0].SetPos(3,3);
			md.bVisible=1;
			Anima[0].SetMand(md);
			bAttack=1;
		}
	} 
	else if(bAttack)
	{
		iAnimaTime++;
		if(iAnimaTime==20)
		{
			ManData md;
			iAnimaTime=0;
			Attack();
			md.bVisible=0;
			Anima[0].SetMand(md);
			bAttack=0;
			if(man.GetMand().Health<=0)
			{
				//bBackMove=0;
				bEnemyAction=0;
				GameState=GAMEOVER;
				InvalidateRect(hwnd,NULL,true);
			}
			else
				bBackMove=1;
			if(battler[0].Getpos().x>=384)
				battler[0].Setwens(LEFT);
			if(battler[1].Getpos().x<=192)
				battler[1].Setwens(RIGHT);
		}
	}
	else if(bBackMove)
	{
		if(!bEnemyAction)
			battler[0].MovePos(-3,0);
		else
			battler[1].MovePos(3,0);
		if(bEnemyAction==0&&battler[0].Getpos().x<=160)
		{
			bBackMove=0;
			battler[0].Setwens(RIGHT);
			battler[0].SetiFrame(0);
			//GameState=BATTLEMENUMODE;
			if(!bwin)
			{
				bEnemyAction=1;
				bAtacMove=1;
			}
			else
			{
				battler[0].Setwens(0);
				GameState=BATTLEMENUMODE;
			}
		}
		else if(battler[1].Getpos().x>=416&&bEnemyAction)
		{
			bBackMove=0;
			bEnemyAction=0;
			battler[1].Setwens(LEFT);
			battler[1].SetiFrame(0);
			GameState=BATTLEMENUMODE;
		}
	}
}

void MYBATTLE::UseGoods()
{
	ManData md;
	if(bUseGoods[0])
	{
		Anima[1].SetPos(5,5);
		md.bVisible=1;
		Anima[1].SetMand(md);
		bUseGoods[0]=0;
		bUseGoods[1]=1;
	}
	else if(bUseGoods[1])
	{
		Anima[1].Setwens(1);
		md.bVisible=1;
		Anima[1].SetMand(md);
		bUseGoods[1]=0;
		bUseGoods[2]=1;
	}
	else if(bUseGoods[2])
	{
		Anima[1].Setwens(2);
		md.bVisible=1;
		Anima[1].SetMand(md);
		bUseGoods[2]=0;
		bUseGoods[3]=1;
	}
	else if(bUseGoods[3])
	{
		char temp[32];
		Anima[1].Setwens(3);
		md.bVisible=1;
		Anima[1].SetMand(md);
		sscanf("+","%s",temp);
		sscanf(txtool.itos(pmg->Getgshow(0).gd.param1).snum,"%s",temp+1);
		txtool.TextOutTx(hdcdest,160,80,temp,txtool.itos(pmg->Getgshow(0).gd.param1).lenth+1,txtool.SetFont(RGB(255,0,0),30,20));
		iAnimaTime++;
		if(iAnimaTime>=10)
		{	
			bUseGoods[3]=0;
			md.bVisible=0;
			Anima[1].SetMand(md);
			GameState=BATTLEMENUMODE;
		}
	}
}