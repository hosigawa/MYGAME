#include "StdAfx.h"
#include"GAME_MAIN.h"

int GameState=2;
int oldGameState=2;
MAP map;
MAN man;
GAMENPC npc;
bool GameBool[GAMEBOOLNUM];

GAMEMAIN::~GAMEMAIN()
{
	DeleteObject(hdcmem);
	DeleteObject(hcombmp);
}

void GAMEMAIN::Init(HINSTANCE hinst,HWND hWnd,int gw,int gh)
{
	gamew=gw;
	gameh=gh;
	hins=hinst;
	hwnd=hWnd;
	hdc=GetDC(hwnd);
	hdcmem=CreateCompatibleDC(hdc);
	ReleaseDC(hwnd,hdc);
	//act.Init(hins,hwnd,&hcombmp,&hdcmem);
	tim.Init(hWnd,&act,&key,&mb);
	//mb.Init(hins,hwnd,&hcombmp,&hdcmem);
	tx.Init(hins,hwnd,&hcombmp,&hdcmem);
	mf.Init(hins,hwnd,&hcombmp,&hdcmem,&sav);
	//mef.Init(hins,hwnd,&hcombmp,&hdcmem,&sav);
	key.Init(&act,&mf,&mef,&mb,&mg,&tx,&mc,&ms,&msp);
	sav.Init(&act);
}


void GAMEMAIN::Show(HDC hDC)
{
	if(oldGameState!=GameState)
		CheckState();
	oldGameState=GameState;
	switch(GameState)
	{
	case NORMALMODE:
		map.Draw(hdcmem);
		for(int i=0;i<npc.NpcNum;i++)
		{
			npc.man[i].Draw(hdcmem,1,1);
		}
		man.Draw(hdcmem,1,1);
		BitBlt(hDC,0,0,gamew,gameh,hdcmem,map.GetView().x,map.GetView().y,SRCCOPY);
		if(tx.Getbtalk())             //
		{                        //
			tx.Setbtalk(false);         //
			GameState=TALKMODE;  //为了实现对话NPC转向
		}                       //
		if(!GameBool[0])
		{
			GameBool[0]=true;
			key.SetSelecttx(64);
			tx.SelectText(0);
			GameState=TALKMODE;
		}
		break;
	case FACEMODE:
		mf.Draw(hdcmem);
		BitBlt(hDC,0,0,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	case MENUMODE:
		mef.Draw(hdcmem);
		BitBlt(hDC,160,50,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	case TALKMODE:
		tx.Print(hdcmem);
		BitBlt(hDC,0,360,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	case GOODSMODE:
		mg.Draw(hdcmem);
		BitBlt(hDC,90,48,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	case STATEMODE:
		ms.Draw(hdcmem);
		BitBlt(hDC,140,40,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	case BATTLEMENUMODE:
	case BATTLESUBMENUMODE:
	case BATTLEMODE:
		mb.Draw(hdcmem);
		BitBlt(hDC,0,0,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	case CONFIRMMODE:
		mc.Draw(hdcmem);
		BitBlt(hDC,144,143,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	case SHOPSUBMODE:
	case SHOPMODE:
		msp.Draw(hdcmem);
		BitBlt(hDC,0,0,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	case GAMEOVER:
		mf.Draw(hdcmem);
		BitBlt(hDC,0,0,gamew,gameh,hdcmem,0,0,SRCCOPY);
	case GAMEEND:
		mf.Draw(hdcmem);
		BitBlt(hDC,0,0,gamew,gameh,hdcmem,0,0,SRCCOPY);
		break;
	}
}

void GAMEMAIN::CheckState()
{
	switch(GameState)
	{
	case NORMALMODE:
		act.Init(hins,hwnd,&hcombmp,&hdcmem);
		if(mf.GetbMapInit())
		{
			act.SetCurrentMap("maps/mainroom.map");
			act.SetbPlaysound(true);
			npc.bchange=1;
			act.OnMap(act.GetCurrentMap());
			npc.bchange=0;
			tx.Load("script/textscript.sp");
			man.SetPos(17,7);
			ManData md;
			md.Exp=1;
			md.Power=1;
			md.Define=1; 
			md.Speed=1;
			md.Level=1;
			md.Health=10;
			md.bVisible=1;
			strcpy(md.path,"pic/role/yongshi.bmp");
			sscanf("勇士小李","%s",md.name);
			man.SetMand(md);
			man.MakeSyn();
			act.OnMan(man.GetMand().path);
			for(int i=0;i<512;i++)
				GameBool[i]=false;
			Pocket pk;
			pk.ID=0;
			for(int i=0;i<20;i++)
				man.Setpk(i,pk);
			Equipe eq;
			eq.hand=0;
			eq.body=0;
			eq.foot=0;
			man.SetEquipe(eq);
			POINT pt;
			pt.x=max(min(max((man.Getpos().x+16-map.Getgamew()/2),0),32*map.Getmapw()-map.Getgamew()),0);
			pt.y=max(min(max((man.Getpos().y+32-map.Getgameh()/2),0),32*(map.Getiblocks()/map.Getmapw())-map.Getgameh()),0);
			map.SetView(pt);
			mg.LoadGoods();
			mg.List();
			mf.SetbMapInit(false);//地图初始化已经完成
		}
		else if(sav.GetiSavlod())
		{
			POINT pt;
			npc.bchange=1;
			act.SetbPlaysound(true);
			act.OnMap(act.GetCurrentMap());
			act.OnMan(man.GetMand().path);
			man.SetPos(man.Getopos().x,man.Getopos().y);
			man.MakeSyn();
			tx.Load("script/textscript.sp");
			npc.bchange=0;
			pt.x=max(min(max((man.Getpos().x+16-map.Getgamew()/2),0),32*map.Getmapw()-map.Getgamew()),0);
			pt.y=max(min(max((man.Getpos().y+32-map.Getgameh()/2),0),32*(map.Getiblocks()/map.Getmapw())-map.Getgameh()),0);
			map.SetView(pt);
			mg.LoadGoods();
			mg.List();
			sav.SetiSavlod(false);
		}
		else 
			act.OnMap(act.GetCurrentMap());
		break;
	case FACEMODE:
		mf.Init(hins,hwnd,&hcombmp,&hdcmem,&sav);
		break;
	case MENUMODE:
		mef.Init(hins,hwnd,&hcombmp,&hdcmem,&sav);
		break;
	case TALKMODE:
		tx.Init(hins,hwnd,&hcombmp,&hdcmem);
		break;
	case GOODSMODE:
		mg.List();
		mg.Init(hins,hwnd,&hcombmp,&hdcmem);
		break;
	case BATTLEMODE:
		mb.Init(hins,hwnd,&hcombmp,&hdcmem,&mg);
		break;
	case STATEMODE:
		ms.Init(hins,hwnd,&hcombmp,&hdcmem,&mg);
		break;
	case BATTLEMENUMODE:
		act.SetbPlaysound(true);
		mb.Init(hins,hwnd,&hcombmp,&hdcmem,&mg);
		break;
	case BATTLESUBMENUMODE:
		//mb.InitBattle(hins,hwnd,&hcombmp,&hdcmem);
		break;
	case CONFIRMMODE:
		mc.Init(hins,hwnd,&hcombmp,&hdcmem,&mg,&msp);
		break;
	case SHOPMODE:
		act.SetbPlaysound(true);
		msp.Init(hins,hwnd,&hcombmp,&hdcmem,&mg);
		break;
	case SHOPSUBMODE:
		msp.Init(hins,hwnd,&hcombmp,&hdcmem,&mg);
		break;
	case GAMEOVER:
		mf.Init(hins,hwnd,&hcombmp,&hdcmem,&sav);
		break;
	case GAMEEND:
		mf.Init(hins,hwnd,&hcombmp,&hdcmem,&sav);
		break;
	}
}
