#include "StdAfx.h"
#include"GAME_CONFIRM.h"

extern int GameState;
extern MAN man;

void MYCONFIRM::Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme,MYGOODS* mg,MYSHOP* msp)
{
	pmg=mg;
	pmsp=msp;
	phdcmem=hdcme;
	phcombmp=hcombm;
	hwnd=hWnd;
	hdcsrc=GetDC(hWnd);
	if(*phcombmp)
		DeleteObject(*phcombmp);
	*phcombmp=CreateCompatibleBitmap(hdcsrc,352,194);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdcsrc);
	SelectObject(hdcdest,hcombmp);
	SelectObject(*phdcmem,*phcombmp);
	ReleaseDC(hWnd,hdcsrc);
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/confirm.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	SelectObject(hdcdest,hbmp);
	iSelect=0;
}

void MYCONFIRM::Draw(HDC hdc)
{
	BitBlt(hdc,0,0,352,194,hdcdest,0,0,SRCCOPY);
	if(igamestate==CONFIRMMODE)
	{
		txtool.TextOutTx(hdc,30,50,"将全部丢弃，确定吗？",18,txtool.SetFont(RGB(255,255,255),20,12));
			if(!iSelect)
			{
				txtool.TextOutTx(hdc,80,120,"是",2,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				txtool.TextOutTx(hdc,230,120,"否",2,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
			}
			else
			{
				txtool.TextOutTx(hdc,80,120,"是",2,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,230,120,"否",2,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
			}
	}
	else if(igamestate==STATEMODE)
	{
		txtool.TextOutTx(hdc,30,50,"要卸下这件装备吗？",17,txtool.SetFont(RGB(255,255,255),20,12));
			if(!iSelect)
			{
				txtool.TextOutTx(hdc,80,120,"是",2,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				txtool.TextOutTx(hdc,230,120,"否",2,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
			}
			else
			{
				txtool.TextOutTx(hdc,80,120,"是",2,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,230,120,"否",2,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
			}
	}
	else if(igamestate==GOODSMODE)
	{
		if(pmg->Getgshow(0).gd.bUseful)
		{
			txtool.TextOutTx(hdc,30,50,"想要做什么呢？",13,txtool.SetFont(RGB(255,255,255),20,12));
			if(!iSelect)
			{
				txtool.TextOutTx(hdc,80,120,"使用",4,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				txtool.TextOutTx(hdc,230,120,"丢弃",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
			}
			else
			{
				txtool.TextOutTx(hdc,80,120,"使用",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,230,120,"丢弃",4,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
			}
		}
		else if(pmg->Getgshow(0).gd.bEquipe)
		{
			txtool.TextOutTx(hdc,30,50,"想要做什么呢？",13,txtool.SetFont(RGB(255,255,255),20,12));
			if(!iSelect)
			{
				txtool.TextOutTx(hdc,80,120,"装备",4,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				txtool.TextOutTx(hdc,230,120,"丢弃",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
			}
			else
			{
				txtool.TextOutTx(hdc,80,120,"装备",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,230,120,"丢弃",4,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
			}
		}
	}
	else if(igamestate==SHOPMODE)
	{
		if(param1==0)
		{
			txtool.TextOutTx(hdc,30,50,"这个卖",6,txtool.SetFont(RGB(255,255,255),20,12));
			txtool.TextOutTx(hdc,110,50,txtool.itos(pmsp->GetPrice()).snum,txtool.itos(pmsp->GetPrice()).lenth,txtool.SetFont(RGB(255,255,255),20,12));
			txtool.TextOutTx(hdc,120+txtool.itos(pmsp->GetPrice()).lenth*12,50,"钱,可以吗？",11,txtool.SetFont(RGB(255,255,255),20,12));
			if(!iSelect)
			{
				txtool.TextOutTx(hdc,80,120,"是",2,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				txtool.TextOutTx(hdc,230,120,"否",2,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
			}
			else
			{
				txtool.TextOutTx(hdc,80,120,"是",2,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,230,120,"否",2,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
			}
		}
		else if(param1==1)
		{
			txtool.TextOutTx(hdc,30,50,"这个给您",8,txtool.SetFont(RGB(255,255,255),20,12));
			txtool.TextOutTx(hdc,135,50,txtool.itos(pmsp->GetPrice()).snum,txtool.itos(pmsp->GetPrice()).lenth,txtool.SetFont(RGB(255,255,255),20,12));
			txtool.TextOutTx(hdc,140+txtool.itos(pmsp->GetPrice()).lenth*12,50,"钱,可以吗？",11,txtool.SetFont(RGB(255,255,255),20,12));
			if(!iSelect)
			{
				txtool.TextOutTx(hdc,80,120,"是",2,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
				txtool.TextOutTx(hdc,230,120,"否",2,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
			}
			else
			{
				txtool.TextOutTx(hdc,80,120,"是",2,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,12));
				txtool.TextOutTx(hdc,230,120,"否",2,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,12));
			}
		}
	}
}

void MYCONFIRM::Confirm(int igame)
{
	igamestate=igame;
	GameState=CONFIRMMODE;
}

void MYCONFIRM::Confirm(int igame,int para)
{
	igamestate=igame;
	GameState=CONFIRMMODE;
	param1=para;
}
void MYCONFIRM::Confirm(int igame,int para1,int para2)
{
	igamestate=igame;
	GameState=CONFIRMMODE;
	param1=para1;
	param2=para2;
}

void MYCONFIRM::entry()
{
	if(igamestate==GOODSMODE)
	{
		if(!iSelect)
		{
			pmg->UseGoods();	
			GameState=GOODSMODE;
		}
		else
		{
			Confirm(GameState);
		}
	}
	else if(igamestate==CONFIRMMODE)
	{
		if(!iSelect)
		{
			pmg->DeleteGoods(pmg->Getgshow(0).seq-1);	
			GameState=GOODSMODE;
		}
		else
			GameState=GOODSMODE;
	}
	else if(igamestate==STATEMODE)
	{
		if(!iSelect)
		{
			Equipe eq;
			pmg->AddGoods(pmg->Getequipe(param1).ID,1);
			switch(param1)
			{
			case 0:
				eq=man.GetEquipe();
				eq.hand=0;
				man.SetEquipe(eq);
				break;
			case 1:
				eq=man.GetEquipe();
				eq.body=0;
				man.SetEquipe(eq);
				break;
			case 2:
				eq=man.GetEquipe();
				eq.foot=0;
				man.SetEquipe(eq);
				break;
			}
			pmg->List();
			GameState=igamestate;
		}
		else
			GameState=igamestate;
	}
	else if(igamestate==SHOPMODE)
	{
		if(param1==0)
		{
			if(!iSelect)
			{
				pmsp->BuySell(0);
				GameState=igamestate;
			}
			else
				GameState=igamestate;
		}
		else if(param1==1)
		{
			if(!iSelect)
			{
				pmsp->BuySell(1);
				GameState=igamestate;
			}
			else
				GameState=igamestate;
		}
	}
}

void MYCONFIRM::SelectCur(int selc)
{
	switch(selc)
	{
	case 0:
		iSelect++;
		if(iSelect==2)
			iSelect=0;
		break;
	case 1:
		iSelect--;
		if(iSelect==-1)
			iSelect=1;
		break;
	}
}

int MYCONFIRM::Getigamestate()
{
	return igamestate;
}