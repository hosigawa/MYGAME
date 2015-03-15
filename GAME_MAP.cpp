#include "StdAfx.h"
#include<stdio.h>
#include"GAME_MAP.h"
#include"GAME_ROLE.h"

extern int GameState;
extern MAN man;
extern GAMENPC npc;


MAP::MAP()
{
	mapd=NULL;
}

MAP::~MAP()
{
	if(mapd)
	{
		free(mapd);
		mapd=NULL;
	}
}

void MAP::GetClntInfo(HWND hWnd,LPARAM lParam)
{
	gamew=LOWORD(lParam);
	gameh=HIWORD(lParam);
	hwnd=hWnd;
}


int MAP::Getiblocks()
{
	return iblocks;
}

int MAP::Getmapw()
{
	return mapw;
}

void MAP::SetView(POINT pt)
{
	View=pt;
}

POINT MAP::GetView()
{
	return View;
}

MapData MAP::Getmapd(int seq)
{
	return mapd[seq];
}

int MAP::Getgamew()
{
	return gamew;
}

int MAP::Getgameh()
{
	return gameh;
}

char* MAP::GetMusic()
{
	return Music;
}

void MAP::Init(HINSTANCE hinstance,char* pchar)
{
	FILE *fp=NULL;
	char path[32]={};
	fp=fopen(pchar,"rb+");
	char temp[512]={};
	fgets(temp,32,fp);
	strcpy(path,"pic/bkground/");
	sscanf(temp,"%s",path+13);
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(hinstance,path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	GetObject(hbmp,sizeof(BITMAP),&bm);
	cxBmp=bm.bmWidth;
	cyBmp=bm.bmHeight;
	fgets(temp,32,fp);
	strcpy(Music,"sound/");
	sscanf(temp,"%s",Music+6);
	fgets(temp,3*sizeof(int),fp);
	sscanf(temp,"%d%d%d",&iblocks,&mapw,&sourcew);
	if(mapd)
	{
		free(mapd);
		mapd=NULL;
	}
	mapd=(MapData*)malloc(sizeof(MapData)*iblocks);
	for(int i=0;i<iblocks;i++)
	{
		fgets(temp,sizeof(MapData),fp);
		if(temp[0]==*";")
			fgets(temp,sizeof(MapData),fp);
		strcpy(mapd[i].MapName,"maps/");
		sscanf(temp,"%d%d%d%d%d%s",&mapd[i].iGroud,&mapd[i].iSecond,&mapd[i].iThird,&mapd[i].ispecial,&mapd[i].iMapPoint,mapd[i].MapName+5);
	}
		
	if(npc.bchange)
	{
		fgets(temp,sizeof(int),fp);
		sscanf(temp,"%d",&npc.NpcNum);
		HDC	hdc=GetDC(hwnd);
		for(int i=0;i<npc.NpcNum;i++)
		{
			ManData md;
			POINT pt;
			fgets(temp,512,fp);
			strcpy(md.path,"pic/role/");
			sscanf(temp,"%d%s%s%d%d%s%d%d%d%d%d%d%d%d%d",&md.Id,md.name,md.path+9,
				&pt.x,&pt.y,md.sex,&md.bVisible,&md.enemy,
				&md.bWalk,&md.Level,&md.Health,&md.Power,&md.Define,
				&md.Magic,&md.Speed);
			npc.man[i].SetbRolerun(false);
			npc.man[i].SetMand(md);
			npc.man[i].Init(hinstance,npc.man[i].GetMand().path,4,4);
			npc.man[i].Setwens(md.enemy);
			npc.man[i].SetiFrame(md.Level);
			npc.man[i].Device(hdc);
			npc.man[i].SetPos(pt.x,pt.y);
		}
		ReleaseDC(hwnd,hdc);
	}
	fclose(fp);
}

void MAP::Device(HDC hdc)
{
	if(hcombmp)
		DeleteObject(hcombmp);
	hcombmp=CreateCompatibleBitmap(hdc,32*mapw,32*((iblocks-1)/mapw+1));
	if(hmask)
		DeleteObject(hmask);
	hmask=CreateBitmap(cxBmp,cyBmp,1,1,NULL);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdc);
	if(hdcmask)
		DeleteDC(hdcmask);
	hdcmask=CreateCompatibleDC(hdc);
	if(hdcsrc)
		DeleteDC(hdcsrc);
	hdcsrc=CreateCompatibleDC(hdc);
	SelectObject(hdcmask,hmask);
	SelectObject(hdcsrc,hbmp);
	oldColor=SetBkColor(hdcsrc,RGB(0,1,0));
	BitBlt(hdcmask,0,0,cxBmp,cyBmp,hdcsrc,0,0,SRCINVERT);
	SetBkColor(hdcsrc,oldColor);
	SelectObject(hdcdest,hcombmp);
	for(int i=0;i<iblocks;i++)
	{
		BitBlt(hdcdest,(i%mapw)*32,(i/mapw)*32,32,32,hdcsrc,mapd[i].iGroud%sourcew*32,mapd[i].iGroud/sourcew*32,SRCCOPY);
	}
	for(int i=0;i<iblocks;i++)
	{
		if(mapd[i].iSecond)
		{
			BitBlt(hdcdest,(i%mapw)*32,(i/mapw)*32,32,32,hdcmask,mapd[i].iSecond%sourcew*32,mapd[i].iSecond/sourcew*32,SRCAND);
			BitBlt(hdcdest,(i%mapw)*32,(i/mapw)*32,32,32,hdcsrc,mapd[i].iSecond%sourcew*32,mapd[i].iSecond/sourcew*32,SRCPAINT);
		}
		if(mapd[i].iThird)
		{
			BitBlt(hdcdest,(i%mapw)*32,(i/mapw)*32,32,32,hdcmask,mapd[i].iThird%sourcew*32,mapd[i].iThird/sourcew*32,SRCAND);
			BitBlt(hdcdest,(i%mapw)*32,(i/mapw)*32,32,32,hdcsrc,mapd[i].iThird%sourcew*32,mapd[i].iThird/sourcew*32,SRCPAINT);
		}
	}
}

void MAP::Draw(HDC hdc)
{	
	BitBlt(hdc,0,0,32*mapw,32*((iblocks-1)/mapw+1),hdcdest,0,0,SRCCOPY);
}
