#include"stdafx.h"
#include<stdio.h>
#include"GAME_ACTIVITY.h"


extern int GameState;
extern MAN man;
extern MAP map;
extern GAMENPC npc;


void ACTIVITY::Init(HINSTANCE hinst,HWND hWnd,HBITMAP* hbitm,HDC* hdcmem)
{
	hwnd=hWnd;
	hins=hinst;
	hbmp=hbitm;
	hdcm=hdcmem;
}



void ACTIVITY::OnMap(char* path)
{
	hdc=GetDC(hwnd);
	map.Init(hins,path);
	map.Device(hdc);
	if(bPlaysound)
	{
		PlaySound(map.GetMusic(),NULL,SND_LOOP|SND_ASYNC);
		bPlaysound=false;
	}
	if(*hbmp)
		DeleteObject(*hbmp);
	*hbmp=CreateCompatibleBitmap(hdc,32*map.Getmapw(),32*((map.Getiblocks()-1)/map.Getmapw()+1));
	SelectObject(*hdcm,*hbmp);
	ReleaseDC(hwnd,hdc);
}

void ACTIVITY::OnMan(char* path)
{
	hdc=GetDC(hwnd);
	man.Init(hins,path,4,4);
	man.Device(hdc);
	ReleaseDC(hwnd,hdc);
}

void ACTIVITY::SetCurrentMap(char* path)
{
	strcpy(CurrentMap,path);
}

char* ACTIVITY::GetCurrentMap()
{
	return CurrentMap;
}

void ACTIVITY::MapChange()
{
	if(!man.GetbRolerun())
	{
		if(map.Getmapd(((man.Getpos().x+16)/32)%map.Getmapw()+((man.Getpos().y+32)/32)*map.Getmapw()).iMapPoint)
		{
			bPlaysound=true;
			iplace=map.Getmapd(((man.Getpos().x+16)/32)%map.Getmapw()+((man.Getpos().y+32)/32)*map.Getmapw()).iMapPoint;
			OnAct(map.Getmapd(((man.Getpos().x+16)/32)%map.Getmapw()+((man.Getpos().y+32)/32)*map.Getmapw()).MapName);
		}
	}
}

void ACTIVITY::OnAct(char* path)
{
	char mappath[32];
	strcpy(mappath,path);
	npc.bchange=1;
	OnMap(mappath);
	npc.bchange=0;
	strcpy(CurrentMap,mappath);
	OnMan(man.GetMand().path);
	for(int i=0;i<map.Getiblocks();i++)
	{
		if(map.Getmapd(i).iMapPoint==iplace)
		{
			man.SetPos(i%map.Getmapw(),i/map.Getmapw());
			man.MakeSyn();
			POINT pt;
			pt.x=max(min(max((man.Getpos().x+16-map.Getgamew()/2),0),32*map.Getmapw()-map.Getgamew()),0);
			pt.y=max(min(max((man.Getpos().y+32-map.Getgameh()/2),0),32*(map.Getiblocks()/map.Getmapw())-map.Getgameh()),0);
			map.SetView(pt);
			break;
		}
	}
	man.Setbchangemap(true);
}

bool ACTIVITY::GetbPlaysound()
{
	return bPlaysound;
}

void ACTIVITY::SetbPlaysound(bool tf)
{
	bPlaysound=tf;
}

int ACTIVITY::SerchText()
{
	for(int i=0;i<npc.NpcNum;i++)
	{	
		if(npc.man[i].GetMand().bVisible)
		{
			switch(man.Getwens())
			{
			case 0:
				if(((man.Getpos().x+16)/32+(man.Getpos().y+64)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					if(*npc.man[i].GetMand().sex!=*"物")
					npc.man[i].Setwens(3);
					return i;
				}
				break;
			case 1:
				if(((man.Getpos().x-16)/32+(man.Getpos().y+32)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					if(*npc.man[i].GetMand().sex!=*"物")
						npc.man[i].Setwens(2);
					return i;
				}
				break;
			case 2:
				if(((man.Getpos().x+48)/32+(man.Getpos().y+32)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					if(*npc.man[i].GetMand().sex!=*"物")
						npc.man[i].Setwens(1);
					return i;
				}
				break;
			case 3:
				if(((man.Getpos().x+16)/32+(man.Getpos().y)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					if(*npc.man[i].GetMand().sex!=*"物")
						npc.man[i].Setwens(0);
					return i;
				}
				break;
			}
		}
		/*
		else if(mode==1&&npc.man[i].GetMand().enemy)
		{
			switch(man.Getwens())
			{
			case 0:
				if(((man.Getpos().x+16)/32+(man.Getpos().y+32)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					npc.man[i].Setwens(3);
					return i;
				}
				break;
			case 1:
				if(((man.Getpos().x+16)/32+(man.Getpos().y+32)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					npc.man[i].Setwens(2);
					return i;
				}
				break;
			case 2:
				if(((man.Getpos().x+16)/32+(man.Getpos().y+32)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					npc.man[i].Setwens(1);
					return i;
				}
				break;
			case 3:
				if(((man.Getpos().x+16)/32+(man.Getpos().y+32)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					npc.man[i].Setwens(0);
					return i;
				}
				break;
			}
		}
		*/
	}
	return -1;
}