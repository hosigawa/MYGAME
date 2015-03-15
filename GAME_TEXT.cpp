#include "StdAfx.h"
#include"GAME_TEXT.h"
#include"GAME_ROLE.h"

extern int GameState;
extern MAN man;
extern MAP map;
extern GAMENPC npc;

extern bool GameBool[GAMEBOOLNUM]; 

TEXTPRINT::TEXTPRINT()
{
	
}

TEXTPRINT::~TEXTPRINT()
{
	DeleteObject(hfont);
}
void TEXTPRINT::Load(char* textpath)
{
	textnum=0;
	FILE* fp;
	bool bread=0;
	fp=fopen(textpath,"rb+");
	char temp[600]={};
	for(int i=0;i<TEXTNUM;i++)
	{
		if(txd[i].size)
			txd[i].size=0;
		fgets(temp,600,fp);
		if(temp[0]==*"~")
			break;
		if(temp[0]==*"*")
			fgets(temp,600,fp);
		sscanf(temp,"%d%d%s%d%d%d%d",&txd[i].TextID,&txd[i].termform,txd[i].TextTemp,&txd[i].fun,&txd[i].param1,&txd[i].param2,&txd[i].param3);
		textnum++;
		for(int j=0;j<600;j++)
		{
			if(temp[j]=='[')
				bread=1;
			if(bread)
				txd[i].size++;
			if(temp[j]==']')
			{
				txd[i].size-=2;
				bread=0;
				break;
			}
		}
	}
	fclose(fp);
}

void TEXTPRINT::Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme)
{
	phdcmem=hdcme;
	phcombmp=hcombm;
	hwnd=hWnd;
	hdcsrc=GetDC(hWnd);
	if(*phcombmp)
		DeleteObject(*phcombmp);
	*phcombmp=CreateCompatibleBitmap(hdcsrc,640,120);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdcsrc);
	SelectObject(hdcdest,hcombmp);
	SelectObject(*phdcmem,*phcombmp);
	ReleaseDC(hWnd,hdcsrc);
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/TalkBar.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	SelectObject(hdcdest,hbmp);
}


void TEXTPRINT::SelectText(int id)
{
	int num=0;
	TextData tmp;
	for(int i=0;i<textnum;i++)
	{
		if(txd[i].TextID==id)
		{
			txtmp[num]=txd[i];
			num++;
		}
	}	
	for(int i=0;i<num-1;i++)
	{
		for(int j=0;j<num-1-i;j++)
		{
			if(txtmp[j].termform<txtmp[j+1].termform);
			{
				tmp=txtmp[j];
				txtmp[j]=txtmp[j+1];
				txtmp[j+1]=tmp;
			}
		}
	}
	for(int i=0;i<num;i++)
	{
		if(GameBool[txtmp[i].termform])
		{
			for(int j=0;j<512;j++)
				text[j]=txtmp[i].TextTemp[j];
			Size=txtmp[i].size;
			txtemp=txtmp[i];
			break;
		}
	}
}

void TEXTPRINT::Print(HDC hdc)
{
	BitBlt(hdc,0,0,640,120,hdcdest,0,0,SRCCOPY);
	Font ft=SetFont(RGB(255,255,255),20,10);
	if(Size<=50)
	TextOutTx(hdc,20,20,text+1,Size,ft);
	else if(Size>50&&Size<=100)
	{
		TextOutTx(hdc,20,20,text+1,50,ft);
		TextOutTx(hdc,20,40,text+51,Size-50,ft);
	}
	else
	{
		TextOutTx(hdc,20,20,text+1,50,ft);
		TextOutTx(hdc,20,40,text+51,50,ft);
		TextOutTx(hdc,20,60,text+101,Size-100,ft);
	}
}

IToS TEXTPRINT::itos(int i)
{
	IToS temp;
	sprintf(temp.snum,"%d",i);
	if(i<10)
		temp.lenth=1;
	else if(10<=i&&i<100)
		temp.lenth=2;
	else if(100<=i&&i<1000)
		temp.lenth=3;
	else if(1000<=i&&i<10000)
		temp.lenth=4;
	else if(10000<=i&&i<100000)
		temp.lenth=5;
	else if(100000<=i&&i<1000000)
		temp.lenth=6;
	return temp;
}


Font TEXTPRINT::SetFont(COLORREF textColor,int height,int wight)
{
	Font ft;
	ft.textColor=textColor;
	ft.height=height;
	ft.wight=wight;
	ft.bTransparentMode=1;
	return ft;
}

Font TEXTPRINT::SetFont(COLORREF textColor,COLORREF BkColor,int height,int wight)
{
	Font ft;
	ft.textColor=textColor;
	ft.height=height;
	ft.wight=wight;
	ft.BkColor=BkColor;
	ft.bTransparentMode=0;
	return ft;
}

void TEXTPRINT::TextOutTx(__in HDC hdc, __in int x, __in int y, __in_ecount(c) LPCSTR lpString, __in int c,Font ft)
{
	if(ft.bTransparentMode)
		SetBkMode(hdc,1);
	else
		ft.tmpbkcolor=SetBkColor(hdc,ft.BkColor);
	ft.tmptxcolor=SetTextColor(hdc,ft.textColor);
	if(ft.temphfont)
		DeleteObject(ft.temphfont);
	if(ft.hfont)
		DeleteObject(ft.hfont);
	ft.hfont=CreateFont(ft.height,ft.wight,0,0,0,0,0,0,0,0,0,0,0,NULL);
	ft.temphfont=(HFONT)SelectObject(hdc,ft.hfont);
	TextOut(hdc,x,y,lpString,c);
	if(ft.bTransparentMode)
		SetBkMode(hdc,2);
	else
		SetBkColor(hdc,ft.tmpbkcolor);
	SetTextColor(hdc,ft.tmptxcolor);
	SelectObject(hdc,ft.temphfont);
	DeleteObject(ft.hfont);
}


void TEXTPRINT::SetText(char* ch,int size)
{
	for(int i=0;i<512;i++)
		text[i]=ch[i];
	Size=size;
}


TextData TEXTPRINT::Gettxtemp()
{
	return txtemp;
}

bool TEXTPRINT::Getbtalk()
{
	return btalk;
}

void TEXTPRINT::Setbtalk(bool tf)
{
	btalk=tf;
}