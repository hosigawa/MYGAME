#include"stdafx.h"
#include"GAME_ROLE.h"
#include<stdio.h>

extern int GameState;
extern MAN man;
extern MAP map;
extern GAMENPC npc;


void MAN::Init(HINSTANCE instance,char* pchar,int x,int y)
{
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(instance,pchar,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	GetObject(hbmp,sizeof(BITMAP),&bm);
	cxBmp=bm.bmWidth;
	cyBmp=bm.bmHeight;
	ixNum=x;
	iyNum=y;
	iFrame=0;
}

void MAN::Draw(HDC hdc,float x,float y)
{
		SelectObject(hdcdest,hcombmp);
		SelectObject(hdcsrc,hbmp);
		BitBlt(hdcdest,0,0,cxBmp/ixNum,cyBmp/iyNum,hdcsrc,iFrame*cxBmp/ixNum,wens*cyBmp/iyNum,SRCCOPY);
		SelectObject(hdcsrc,hmask);
	if(mand.bVisible)
	{
		StretchBlt(hdc,pos.x,pos.y,x*cxBmp/ixNum,y*cyBmp/iyNum,hdcsrc,iFrame*cxBmp/ixNum,wens*cyBmp/iyNum,cxBmp/ixNum,cyBmp/iyNum,SRCAND);
		StretchBlt(hdc,pos.x,pos.y,x*cxBmp/ixNum,y*cyBmp/iyNum,hdcdest,0,0,cxBmp/ixNum,cyBmp/iyNum, SRCPAINT);	
	}
}


void MAN::RoleMove()
{
	if(bRolerun==1)
	{
		POINT pt;
		switch(wens)
		{
		case DOWN:
			if(!map.Getmapd(((pos.x+16)/32+(pos.y+48)/32*map.Getmapw())).iSecond&&pos.y+17<=(map.Getiblocks()/map.Getmapw()-1)*32&&NoNPC(DOWN))
			{
				pos.y+=1;
				if(pos.y+32-map.Getgameh()/2>=0)
				{
					pt=map.GetView();
					pt.y=max(min(pos.y+32-map.Getgameh()/2,(map.Getiblocks()/map.Getmapw())*32-map.Getgameh()),0);
					map.SetView(pt);
				}
				if(pos.y-opos.y==32)
				{
					bRolerun=0;
					opos=pos;
					man.bchangemap=0;
				}
			}
			else
			bRolerun=0;
			break;
		case LEFT:
			if(!map.Getmapd(((pos.x-1)/32+(pos.y+32)/32*map.Getmapw())).iSecond&&pos.x-1>=0&&NoNPC(LEFT))
			{
				pos.x-=1;
				if(map.Getmapw()*32-pos.x-16>=map.Getgamew()/2)
				{
					pt=map.GetView();
					pt.x=max(0,pos.x+16-map.Getgamew()/2);
					map.SetView(pt);
				}
				if(opos.x-pos.x==32)
				{
					bRolerun=0;
					opos=pos;
					man.bchangemap=0;
				}
			}
			else 
			bRolerun=0;
			break;
		case RIGHT:
			if(!map.Getmapd(((pos.x+32)/32+(pos.y+32)/32*map.Getmapw())).iSecond&&pos.x+33<=map.Getmapw()*32&&NoNPC(RIGHT))
			{
				pos.x+=1;
				if(pos.x+16>=map.Getgamew()/2)
				{
					pt=map.GetView();
					pt.x=max(0,min(pos.x+16-map.Getgamew()/2,map.Getmapw()*32-map.Getgamew()));
					map.SetView(pt);
				}
				if(pos.x-opos.x==32)
				{
					bRolerun=0;
					opos=pos;
					man.bchangemap=0;
				}
			}
			else 
				bRolerun=0;
			break;
		case UP:
			if(!map.Getmapd(((pos.x+16)/32+(pos.y+15)/32*map.Getmapw())).iSecond&&pos.y+15>=0&&NoNPC(UP))
			{
				pos.y-=1;
				if((map.Getiblocks()/map.Getmapw())*32-pos.y-32>=map.Getgameh()/2)
				{
					pt=map.GetView();
					pt.y=max(0,pos.y+32-map.Getgameh()/2);
					map.SetView(pt);
				}
				if(opos.y-pos.y==32)
				{
					bRolerun=0;
					opos=pos;
					man.bchangemap=0;
				}
			}
			else 
				bRolerun=0;
			break;
		}
	}
}

ManData MAN::GetMand()
{
	return mand;
}

void MAN::SetMand(ManData md)
{
	mand=md;
}
void MAN::Setpk(int seq,Pocket pok)
{
	pk[seq]=pok;
}

Pocket MAN::Getpk(int seq)
{
	return pk[seq];
}

void MAN::SetEquipe(Equipe e)
{
	eq=e;
}

Equipe MAN::GetEquipe()
{
	return eq;
}

void MAN::SetMoney(int mony)
{
	money=mony;
}

int MAN::GetMoney()
{
	return money;
}

void MAN::MakeSyn()
{
	opos=pos;
}

void MAN::SetbRolerun(bool tf)
{
	bRolerun=tf;
}

bool MAN::GetbRolerun()
{
	return bRolerun;
}

void MAN::Setbchangemap(bool tf)
{
	bchangemap=tf;
}

bool MAN::Getbchangemap()
{
	return bchangemap;
}

void MAN::Setwens(int wen)
{
	wens=wen;
}

int MAN::Getwens()
{
	return wens;
}

void MAN::SetiFrame(int frame)
{
	iFrame=frame;
}

void MAN::RoleAnima()
{
	iFrame++;
	if(iFrame==ixNum)
		iFrame=0;
}

void MAN::MovePos(int x,int y)
{
	pos.x+=x;
	pos.y+=y;
}

POINT MAN::Getopos()
{
	return opos;
}

void MAN::Setopos(int x,int y)
{
	opos.x=x;
	opos.y=y;
}

void GAMENPC::NpcMove()
{
	int ran;
	for(int i=0;i<NpcNum;i++)
	{
		ran=rand()%1000;
		if(ran>=990&&man[i].GetbRolerun()==false)
		{
			if(man[i].GetMand().bWalk)
			{
				man[i].SetbRolerun(true);
				man[i].MakeSyn();
				man[i].Setwens(rand()%4);
			}
		}
		if(man[i].GetbRolerun())
		{
			switch(man[i].Getwens())
			{
			case DOWN:
				if(!map.Getmapd(((man[i].Getpos().x+16)/32+(man[i].Getpos().y+48)/32*map.Getmapw())).iSecond&&man[i].Getpos().y+17<=(map.Getiblocks()/map.Getmapw()-1)*32)
				{
					man[i].MovePos(0,1);
					if(man[i].Getpos().y-man[i].Getopos().y==32)
						man[i].SetbRolerun(false);
				}
				else
					man[i].SetbRolerun(false);
				break;
			case LEFT:
				if(!map.Getmapd(((man[i].Getpos().x-1)/32+(man[i].Getpos().y+32)/32*map.Getmapw())).iSecond&&man[i].Getpos().x-1>=0)
				{
					man[i].MovePos(-1,0);
					if(man[i].Getopos().x-man[i].Getpos().x==32)
						man[i].SetbRolerun(false);
				}
				else 
					man[i].SetbRolerun(false);
				break;
			case RIGHT:
				if(!map.Getmapd(((man[i].Getpos().x+32)/32+(man[i].Getpos().y+32)/32*map.Getmapw())).iSecond&&man[i].Getpos().x+33<=map.Getmapw()*32)
				{
					man[i].MovePos(1,0);
					if(man[i].Getpos().x-man[i].Getopos().x==32)
						man[i].SetbRolerun(false);
				}
				else
					man[i].SetbRolerun(false);
				break;
			case UP:
				if(!map.Getmapd(((man[i].Getpos().x+16)/32+(man[i].Getpos().y+15)/32*map.Getmapw())).iSecond&&man[i].Getpos().y+15>=0)
				{
					man[i].MovePos(0,-1);
					if(man[i].Getopos().y-man[i].Getpos().y==32)
						man[i].SetbRolerun(false);
				}
				else
					man[i].SetbRolerun(false);
				break;
			}
		}
	}
}

bool MAN::NoNPC(int wens)
{
	for(int i=0;i<npc.NpcNum;i++)
	{
		if(npc.man[i].GetMand().bVisible)
		{
			switch(wens)
			{
			case 0:
				if(((man.Getpos().x+16)/32+(man.Getpos().y+48)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					return false;
				}
				break;
			case 1:
				if(((man.Getpos().x-1)/32+(man.Getpos().y+32)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{	
					return false;
				}
				break;
			case 2:
				if(((man.Getpos().x+32)/32+(man.Getpos().y+32)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{
					return false;
				}
				break;
			case 3:
				if(((man.Getpos().x+16)/32+(man.Getpos().y+15)/32*map.Getmapw())==((npc.man[i].Getpos().x+16)/32+(npc.man[i].Getpos().y+32)/32*map.Getmapw()))
				{
					return false;
				}
				break;
			}
		}
	}
	return true;
}

void MAN::MovePlace(int wens)
{
	MakeSyn();
	Setwens(wens);
	SetbRolerun(true);
}