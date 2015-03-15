#include"stdafx.h"
#include"GAME_FACE.h"
#include"GAME_MAP.h"

extern int GameState;
extern MAP map;

void MAINFACE::Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme,SAVEGAME* sa)
{
	save=sa;
	phdcmem=hdcme;
	phcombmp=hcombm;
	hwnd=hWnd;
	hdcsrc=GetDC(hWnd);
	if(*phcombmp)
		DeleteObject(*phcombmp);
	*phcombmp=CreateCompatibleBitmap(hdcsrc,640,480);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdcsrc);
	SelectObject(hdcdest,hcombmp);
	SelectObject(*phdcmem,*phcombmp);
	ReleaseDC(hWnd,hdcsrc);
	if(hbmp)
		DeleteObject(hbmp);
	if(GameState==FACEMODE)
	{
		hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/face.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		PlaySound("sound/face.wav",NULL,SND_LOOP|SND_ASYNC);
		iSelcNum=0;
	}
	else if(GameState==GAMEEND)
	{
		hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/gameend.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		PlaySound("sound/tragical.wav",NULL,SND_LOOP|SND_ASYNC);
	}
	else
	{
		hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/gameover.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		PlaySound("sound/gameover.wav",NULL,SND_LOOP|SND_ASYNC);
	}
	SelectObject(hdcdest,hbmp);
}

void MAINFACE::Draw(HDC hdc)
{
	if(GameState==FACEMODE)
	{
		switch(iSelcNum)
		{
		case 0:
			oldColor=SetBkColor(hdcdest,RGB(255,0,0));
			TextOut(hdcdest,300,200,"新的开始",sizeof("新的开始")-1);
			SetBkColor(hdcdest,oldColor);
			TextOut(hdcdest,300,220,"旧的回忆",sizeof("新的开始")-1);
			TextOut(hdcdest,300,240,"退出游戏",sizeof("新的开始")-1);
			break;
		case 1:
			TextOut(hdcdest,300,200,"新的开始",sizeof("新的开始")-1);
			oldColor=SetBkColor(hdcdest,RGB(255,0,0));
			TextOut(hdcdest,300,220,"旧的回忆",sizeof("新的开始")-1);
			SetBkColor(hdcdest,oldColor);
			TextOut(hdcdest,300,240,"退出游戏",sizeof("新的开始")-1);
			break;
		case 2:
			TextOut(hdcdest,300,200,"新的开始",sizeof("新的开始")-1);
			TextOut(hdcdest,300,220,"旧的回忆",sizeof("新的开始")-1);
			oldColor=SetBkColor(hdcdest,RGB(255,0,0));
			TextOut(hdcdest,300,240,"退出游戏",sizeof("新的开始")-1);
			SetBkColor(hdcdest,oldColor);
			break;
		}
	}
	BitBlt(hdc,0,0,640,480,hdcdest,0,0,SRCCOPY);
}

void MAINFACE::SetbMapInit(bool tf)
{
	bMapInit=tf;
}

bool MAINFACE::GetbMapInit()
{
	return bMapInit;
}

void MAINFACE::SelectCur(int selc,int iMax)
{
	switch(selc)
	{
	case 0:
		iSelcNum--;
		if(iSelcNum==-1)
			iSelcNum=iMax-1;
		break;
	case 1:
		iSelcNum++;
		if(iSelcNum==iMax)
			iSelcNum=0;
		break;
	}
}

void MAINFACE::Entry()
{
	switch(iSelcNum)
	{
	case 0:
		InvalidateRect(hwnd,NULL,true);
		GameState=NORMALMODE;
		bMapInit=true;
		break;
	case 1:
		save->Loadgame();
		InvalidateRect(hwnd,NULL,true);
		GameState=NORMALMODE;
		break;
	case 2:
		SendMessage(hwnd,WM_DESTROY,NULL,NULL);
		break;
	}
}

void MENUFACE::Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme,SAVEGAME* sa)
{
	save=sa;
	phdcmem=hdcme;
	phcombmp=hcombm;
	hwnd=hWnd;
	hdcsrc=GetDC(hWnd);
	if(*phcombmp)
		DeleteObject(*phcombmp);
	*phcombmp=CreateCompatibleBitmap(hdcsrc,320,350);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdcsrc);
	SelectObject(hdcdest,hcombmp);
	SelectObject(*phdcmem,*phcombmp);
	ReleaseDC(hWnd,hdcsrc);
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/menu.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	SelectObject(hdcdest,hbmp);
	iSelcNum=0;
}

void MENUFACE::Draw(HDC hdc)
{
	switch(iSelcNum)
	{
	case 0:
		oldColor=SetBkColor(hdcdest,RGB(255,0,0));
		TextOut(hdcdest,120,60,"人物状态",sizeof("新的开始")-1);
		SetBkColor(hdcdest,oldColor);
		TextOut(hdcdest,120,100,"物品装备",sizeof("新的开始")-1);
		TextOut(hdcdest,120,140,"保存进度",sizeof("新的开始")-1);
		TextOut(hdcdest,120,180,"读取游戏",sizeof("新的开始")-1);
		TextOut(hdcdest,120,220,"回主菜单",sizeof("新的开始")-1);
		TextOut(hdcdest,120,260,"返回游戏",sizeof("新的开始")-1);
		break;
	case 1:
		TextOut(hdcdest,120,60,"人物状态",sizeof("新的开始")-1);
		oldColor=SetBkColor(hdcdest,RGB(255,0,0));
		TextOut(hdcdest,120,100,"物品装备",sizeof("新的开始")-1);
		SetBkColor(hdcdest,oldColor);
		TextOut(hdcdest,120,140,"保存进度",sizeof("新的开始")-1);
		TextOut(hdcdest,120,180,"读取游戏",sizeof("新的开始")-1);
		TextOut(hdcdest,120,220,"回主菜单",sizeof("新的开始")-1);
		TextOut(hdcdest,120,260,"返回游戏",sizeof("新的开始")-1);
		break;
	case 2:
		TextOut(hdcdest,120,60,"人物状态",sizeof("新的开始")-1);
		TextOut(hdcdest,120,100,"物品装备",sizeof("新的开始")-1);
		oldColor=SetBkColor(hdcdest,RGB(255,0,0));
		TextOut(hdcdest,120,140,"保存进度",sizeof("新的开始")-1);
		SetBkColor(hdcdest,oldColor);
		TextOut(hdcdest,120,180,"读取游戏",sizeof("新的开始")-1);
		TextOut(hdcdest,120,220,"回主菜单",sizeof("新的开始")-1);
		TextOut(hdcdest,120,260,"返回游戏",sizeof("新的开始")-1);
		break;
	case 3:
		
		TextOut(hdcdest,120,60,"人物状态",sizeof("新的开始")-1);
		TextOut(hdcdest,120,100,"物品装备",sizeof("新的开始")-1);
		TextOut(hdcdest,120,140,"保存进度",sizeof("新的开始")-1);
		oldColor=SetBkColor(hdcdest,RGB(255,0,0));
		TextOut(hdcdest,120,180,"读取游戏",sizeof("新的开始")-1);
		SetBkColor(hdcdest,oldColor);
		TextOut(hdcdest,120,220,"回主菜单",sizeof("新的开始")-1);
		TextOut(hdcdest,120,260,"返回游戏",sizeof("新的开始")-1);
		break;
	case 4:
		TextOut(hdcdest,120,60,"人物状态",sizeof("新的开始")-1);
		TextOut(hdcdest,120,100,"物品装备",sizeof("新的开始")-1);
		TextOut(hdcdest,120,140,"保存进度",sizeof("新的开始")-1);
		TextOut(hdcdest,120,180,"读取游戏",sizeof("新的开始")-1);
		oldColor=SetBkColor(hdcdest,RGB(255,0,0));
		TextOut(hdcdest,120,220,"回主菜单",sizeof("新的开始")-1);
		SetBkColor(hdcdest,oldColor);
		TextOut(hdcdest,120,260,"返回游戏",sizeof("新的开始")-1);
		break;
	case 5:
		TextOut(hdcdest,120,60,"人物状态",sizeof("新的开始")-1);
		TextOut(hdcdest,120,100,"物品装备",sizeof("新的开始")-1);
		TextOut(hdcdest,120,140,"保存进度",sizeof("新的开始")-1);
		TextOut(hdcdest,120,180,"读取游戏",sizeof("新的开始")-1);
		TextOut(hdcdest,120,220,"回主菜单",sizeof("新的开始")-1);
		oldColor=SetBkColor(hdcdest,RGB(255,0,0));
		TextOut(hdcdest,120,260,"返回游戏",sizeof("新的开始")-1);
		SetBkColor(hdcdest,oldColor);
		break;
	}
	BitBlt(hdc,0,0,640,480,hdcdest,0,0,SRCCOPY);
}

void MENUFACE::Entry()
{
	switch(iSelcNum)
	{
	case 0:
		GameState=STATEMODE;
		break;
	case 1:
		GameState=GOODSMODE;
		break;
	case 2:
		save->Savegame();
		GameState=NORMALMODE;
		break;
	case 3:
		save->Loadgame();
		GameState=NORMALMODE;
		break;
	case 4:
		GameState=FACEMODE;
		break;
	case 5:
		//InvalidateRect(hwnd,NULL,true);
		GameState=NORMALMODE;
		break;
	}
}