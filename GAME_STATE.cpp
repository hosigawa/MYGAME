#include"stdafx.h"
#include"GAME_STATE.h"


extern MAN man;

void MANSTATE::Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme,MYGOODS* mg)
{
	phdcmem=hdcme;
	phcombmp=hcombm;
	hwnd=hWnd;
	pmg=mg;
	hdcsrc=GetDC(hWnd);
	if(*phcombmp)
		DeleteObject(*phcombmp);
	*phcombmp=CreateCompatibleBitmap(hdcsrc,360,400);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdcsrc);
	SelectObject(hdcdest,hcombmp);
	SelectObject(*phdcmem,*phcombmp);
	ReleaseDC(hWnd,hdcsrc);
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/state.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	SelectObject(hdcdest,hbmp);
}


void MANSTATE::Draw(HDC hdc)
{
	char temp[32]={};
	BitBlt(hdc,0,0,360,400,hdcdest,0,0,SRCCOPY);
	txtool.TextOutTx(hdc,120,40,man.GetMand().name,8,txtool.SetFont(RGB(255,0,0),20,15));
	txtool.TextOutTx(hdc,50,80,"等级：",6,txtool.SetFont(RGB(0,0,255),20,15));
	txtool.TextOutTx(hdc,250,80,txtool.itos(man.GetMand().Level).snum,txtool.itos(man.GetMand().Level).lenth,txtool.SetFont(RGB(255,0,0),20,15));
	txtool.TextOutTx(hdc,50,105,"经验：",6,txtool.SetFont(RGB(0,0,255),20,15));
	txtool.TextOutTx(hdc,250,105,txtool.itos(man.GetMand().Exp).snum,txtool.itos(man.GetMand().Exp).lenth,txtool.SetFont(RGB(255,0,0),20,15));
	txtool.TextOutTx(hdc,50,130,"生命值：",8,txtool.SetFont(RGB(0,0,255),20,15));
	txtool.TextOutTx(hdc,250+txtool.itos(man.GetMand().Health).lenth*12,130,"/",1,txtool.SetFont(RGB(0,0,255),20,10));
	txtool.TextOutTx(hdc,250,130,txtool.itos(man.GetMand().Health).snum,txtool.itos(man.GetMand().Health).lenth,txtool.SetFont(RGB(255,0,0),20,10));
	txtool.TextOutTx(hdc,260+txtool.itos(man.GetMand().Health).lenth*10,130,txtool.itos(man.GetMand().Level*10).snum,txtool.itos(man.GetMand().Level*10).lenth,txtool.SetFont(RGB(255,0,0),20,10));
	txtool.TextOutTx(hdc,50,155,"攻击力：",8,txtool.SetFont(RGB(0,0,255),20,15));
	txtool.TextOutTx(hdc,250,155,txtool.itos(man.GetMand().Power+pmg->Getequipe(0).param1).snum,txtool.itos(man.GetMand().Power+pmg->Getequipe(0).param1).lenth,txtool.SetFont(RGB(255,0,0),20,15));
	txtool.TextOutTx(hdc,50,180,"防御力：",8,txtool.SetFont(RGB(0,0,255),20,15));
	txtool.TextOutTx(hdc,250,180,txtool.itos(man.GetMand().Define+pmg->Getequipe(1).param1).snum,txtool.itos(man.GetMand().Define+pmg->Getequipe(1).param1).lenth,txtool.SetFont(RGB(255,0,0),20,15));
	txtool.TextOutTx(hdc,50,205,"速度：",6,txtool.SetFont(RGB(0,0,255),20,15));
	txtool.TextOutTx(hdc,250,205,txtool.itos(man.GetMand().Speed+pmg->Getequipe(2).param1).snum,txtool.itos(man.GetMand().Speed+pmg->Getequipe(2).param1).lenth,txtool.SetFont(RGB(255,0,0),20,15));
	txtool.TextOutTx(hdc,50,250,"武器：",6,txtool.SetFont(RGB(0,0,255),20,15));
	txtool.TextOutTx(hdc,50,275,"防具：",6,txtool.SetFont(RGB(0,0,255),20,15));
	txtool.TextOutTx(hdc,50,300,"鞋子：",6,txtool.SetFont(RGB(0,0,255),20,15));
	if(iSelect==0)
	{
		if(man.GetEquipe().hand)
			txtool.TextOutTx(hdc,160,250,pmg->Getequipe(0).name,pmg->Getequipe(0).namelenth,txtool.SetFont(RGB(255,0,0),RGB(255,255,0),20,15));
		else
			txtool.TextOutTx(hdc,160,250,"无装备",6,txtool.SetFont(RGB(80,80,80),RGB(255,255,0),20,15));
		if(man.GetEquipe().body)
			txtool.TextOutTx(hdc,160,275,pmg->Getequipe(1).name,pmg->Getequipe(1).namelenth,txtool.SetFont(RGB(255,0,0),20,15));
		else
			txtool.TextOutTx(hdc,160,275,"无装备",6,txtool.SetFont(RGB(80,80,80),20,15));
		if(man.GetEquipe().foot)
			txtool.TextOutTx(hdc,160,300,pmg->Getequipe(2).name,pmg->Getequipe(2).namelenth,txtool.SetFont(RGB(255,0,0),20,15));
		else
			txtool.TextOutTx(hdc,160,300,"无装备",6,txtool.SetFont(RGB(80,80,80),20,15));
	}
	if(iSelect==1)
	{
		if(man.GetEquipe().hand)
			txtool.TextOutTx(hdc,160,250,pmg->Getequipe(0).name,pmg->Getequipe(0).namelenth,txtool.SetFont(RGB(255,0,0),20,15));
		else
			txtool.TextOutTx(hdc,160,250,"无装备",6,txtool.SetFont(RGB(80,80,80),20,15));
		if(man.GetEquipe().body)
			txtool.TextOutTx(hdc,160,275,pmg->Getequipe(1).name,pmg->Getequipe(1).namelenth,txtool.SetFont(RGB(255,0,0),RGB(255,255,0),20,15));
		else
			txtool.TextOutTx(hdc,160,275,"无装备",6,txtool.SetFont(RGB(80,80,80),RGB(255,255,0),20,15));
		if(man.GetEquipe().foot)
			txtool.TextOutTx(hdc,160,300,pmg->Getequipe(2).name,pmg->Getequipe(2).namelenth,txtool.SetFont(RGB(255,0,0),20,15));
		else
			txtool.TextOutTx(hdc,160,300,"无装备",6,txtool.SetFont(RGB(80,80,80),20,15));
	}
	if(iSelect==2)
	{
		if(man.GetEquipe().hand)
			txtool.TextOutTx(hdc,160,250,pmg->Getequipe(0).name,pmg->Getequipe(0).namelenth,txtool.SetFont(RGB(255,0,0),20,15));
		else
			txtool.TextOutTx(hdc,160,250,"无装备",6,txtool.SetFont(RGB(80,80,80),20,15));
		if(man.GetEquipe().body)
			txtool.TextOutTx(hdc,160,275,pmg->Getequipe(1).name,pmg->Getequipe(1).namelenth,txtool.SetFont(RGB(255,0,0),20,15));
		else
			txtool.TextOutTx(hdc,160,275,"无装备",6,txtool.SetFont(RGB(80,80,80),20,15));
		if(man.GetEquipe().foot)
			txtool.TextOutTx(hdc,160,300,pmg->Getequipe(2).name,pmg->Getequipe(2).namelenth,txtool.SetFont(RGB(255,0,0),RGB(255,255,0),20,15));
		else
			txtool.TextOutTx(hdc,160,300,"无装备",6,txtool.SetFont(RGB(80,80,80),RGB(255,255,0),20,15));
	}
}

void MANSTATE::SetCur(int isele)
{
	switch(isele)
	{
	case 0:
		iSelect--;
		if(iSelect==-1)
			iSelect=2;
		break;
	case 1:
		iSelect++;
		if(iSelect==3)
			iSelect=0;
		break;
	}
}

int MANSTATE::GetiSelect()
{
	return iSelect;
}