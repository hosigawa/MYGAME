#include"stdafx.h"
#include"GAME_GOODS.h"

extern MAN man;
extern int GameState;

void MYGOODS::Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme)
{
	phdcmem=hdcme;
	phcombmp=hcombm;
	hwnd=hWnd;
	hdcsrc=GetDC(hWnd);
	if(*phcombmp)
		DeleteObject(*phcombmp);
	if(GameState==GOODSMODE)
		*phcombmp=CreateCompatibleBitmap(hdcsrc,480,384);
	//else if(GameState==GOODSCONFORMMODE)
		//*phcombmp=CreateCompatibleBitmap(hdcsrc,200,100);
	if(hdcdest)
		DeleteDC(hdcdest);
	hdcdest=CreateCompatibleDC(hdcsrc);
	SelectObject(hdcdest,hcombmp);
	SelectObject(*phdcmem,*phcombmp);
	ReleaseDC(hWnd,hdcsrc);
	if(hbmp)
		DeleteObject(hbmp);
	hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/goods.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	SelectObject(hdcdest,hbmp);
	iSelect=0;
	List();
	empty.ID=0;
	sscanf("无物品","%s",empty.name);
	empty.namelenth=6;
	empty.param1=0;
	empty.param2=0;
	empty.param3=0;
}

void MYGOODS::Draw(HDC hdc)
{
	BitBlt(hdc,0,0,480,384,hdcdest,0,0,SRCCOPY);
	txtool.TextOutTx(hdc,270,330,"金钱：",6,txtool.SetFont(RGB(255,0,0),30,15));
	txtool.TextOutTx(hdc,350,330,txtool.itos(man.GetMoney()).snum,txtool.itos(man.GetMoney()).lenth,txtool.SetFont(RGB(255,0,0),30,15));
	txtool.TextOutTx(hdc,30,50,txtool.itos(gshow[0].seq).snum,txtool.itos(gshow[0].seq).lenth,txtool.SetFont(RGB(255,255,0),RGB(255,0,255),30,15));
	txtool.TextOutTx(hdc,70,50,gshow[0].gd.name,gshow[0].gd.namelenth,txtool.SetFont(RGB(255,255,0),RGB(255,0,255),30,20));
	if(gshow[0].gd.ID)
		txtool.TextOutTx(hdc,400,50,txtool.itos(gshow[0].num).snum,txtool.itos(gshow[0].num).lenth,txtool.SetFont(RGB(255,255,0),RGB(255,0,255),30,15));
	for(int i=1;i<5;i++)
	{
		if(gshow[i].seq)
			txtool.TextOutTx(hdc,30,50+i*40,txtool.itos(gshow[i].seq).snum,txtool.itos(gshow[i].seq).lenth,txtool.SetFont(RGB(0,0,255),30,15));
		if(gshow[i].gd.ID)
		{
			txtool.TextOutTx(hdc,70,50+i*40,gshow[i].gd.name,gshow[i].gd.namelenth,txtool.SetFont(RGB(255,255,0),30,20));
			txtool.TextOutTx(hdc,400,50+i*40,txtool.itos(gshow[i].num).snum,txtool.itos(gshow[i].num).lenth,txtool.SetFont(RGB(255,255,0),30,15));
		}
	}
	if(bcontinueUP)
		txtool.TextOutTx(hdc,230,20,"▲",2,txtool.SetFont(RGB(255,255,0),30,20));
	if(bcontinueDOWN)
		txtool.TextOutTx(hdc,230,300,"▼",2,txtool.SetFont(RGB(255,255,0),30,20));
}

void MYGOODS::List()
{
	for(int i=0;i<GOODSNUM;i++)
	{
		if(!man.GetEquipe().hand)
			equipe[0]=empty;
		else if(gd[i].ID==man.GetEquipe().hand)
			equipe[0]=gd[i];
		if(!man.GetEquipe().body)
			equipe[1]=empty;
		else if(gd[i].ID==man.GetEquipe().body)
			equipe[1]=gd[i];
		if(!man.GetEquipe().foot)
			equipe[2]=empty;
		else if(gd[i].ID==man.GetEquipe().foot)
			equipe[2]=gd[i];
	}
	for(int i=0;i<20;i++)   //把所有的空物品栏填满
	{
		int k=0;
		if(man.Getpk(i).ID==0)
		{	
			int j=i;
			while((j+k)<20)
			{
				if(man.Getpk(j+k).ID==0)
					k++;
				else
				{
					man.Setpk(j,man.Getpk(j+k));
					Pocket pk;
					pk.ID=0;
					pk.num=0;
					man.Setpk(j+k,pk);
					j++;
				}
			}
		}
	}
	int k=0;
	for(int i=0;i<5;i++)
	{
		gshow[i].gd=empty;   //初始化显示容器
		gshow[i].seq=0;
	}
	if(iSelect<15)
	{
		for(int m=iSelect+5;m<20;m++)  //设置继续显示下光标
		{
			if(man.Getpk(m).ID!=0)
			{
				bcontinueDOWN=1;
				break;
			}
			else
				bcontinueDOWN=0;
		}
	}
	else
		bcontinueDOWN=0;
	if(iSelect>=1)
	{
		for(int m=0;m<iSelect;m++)      //设置继续显示上光标
		{
			if(man.Getpk(m).ID!=0) 
			{
				bcontinueUP=1;
				break;
			}
			else
				bcontinueUP=0;
		}
	}
	else
		bcontinueUP=0;
	for(int i=iSelect;i<20;i++)
	{
		if(man.Getpk(i).ID==0)
		{
			gshow[k].gd=empty;
			gshow[k].seq=i+1;
			k++;
			if(k==5)
				return;
		}
		else
		{
			for(int j=0;j<GOODSNUM;j++)
			{
				if(gd[j].ID==man.Getpk(i).ID)
				{
					gshow[k].gd=gd[j];
					gshow[k].seq=i+1;
					gshow[k].num=man.Getpk(i).num;
					k++;
					if(k==5)
						return;
					break;
				}
			}
		}
	}
}

void MYGOODS::LoadGoods()
{
	FILE* fp;
	fp=fopen("script/goods.sp","rb+");
	char temp[600]={};
	for(int i=0;i<GOODSNUM;i++)
	{
		fgets(temp,600,fp);
		if(temp[0]==*"*")
			fgets(temp,600,fp);
		sscanf(temp,"%d%s%d%d%d%d%d%d%d",&gd[i].ID,gd[i].name,&gd[i].namelenth,&gd[i].bUseful,&gd[i].bEquipe,&gd[i].fun,&gd[i].param1,&gd[i].param2,&gd[i].param3);
	}
	fclose(fp);
}


void MYGOODS::SelectCur(int selc)
{
	switch(selc)
	{
	case 0:
		iSelect=max(0,iSelect-1);
		break;
	case 1:
		iSelect=min(19,((man.Getpk(iSelect+1).ID!=0)?(iSelect+1):iSelect));
		break;
	}
	List();
}

bool MYGOODS::AddGoods(int ID,int num)
{
	for(int i=0;i<20;i++)
	{
		if(man.Getpk(i).ID==ID)
		{
			Pocket pk=man.Getpk(i);
			pk.num+=num;
			man.Setpk(i,pk);
			return true;
		}
	}
	for(int i=0;i<20;i++)
	{
		if(!man.Getpk(i).ID)
		{
			Pocket pk=man.Getpk(i);
			pk.ID=ID;
			pk.num=num;
			man.Setpk(i,pk);
			return true;
		}
	}
	return false;
}


bool MYGOODS::UseGoods()
{
	if(gshow[0].gd.bUseful||gshow[0].gd.bEquipe)
	{
		ManData md;
		Equipe eq;
		Pocket pk=man.Getpk(iSelect);
		pk.num--;
		switch(gshow[0].gd.fun)
		{
		case 0:
			pk.num++;
			break;
		case 1:
			md=man.GetMand();
			md.Health=min(md.Health+gshow[0].gd.param1,md.Level*10);
			man.SetMand(md);
			break;
		case 2:
			if(man.GetEquipe().hand)
				AddGoods(man.GetEquipe().hand,1);
			eq=man.GetEquipe();
			eq.hand=gshow[0].gd.ID;
			man.SetEquipe(eq);
			break;
		case 3:
			if(man.GetEquipe().body)
				AddGoods(man.GetEquipe().body,1);
			eq=man.GetEquipe();
			eq.body=gshow[0].gd.ID;
			man.SetEquipe(eq);
			break;
		case 4:
			if(man.GetEquipe().foot)
				AddGoods(man.GetEquipe().foot,1);
			eq=man.GetEquipe();
			eq.foot=gshow[0].gd.ID;
			man.SetEquipe(eq);
			break;
		}
		man.Setpk(iSelect,pk);
		List();
		if(man.Getpk(iSelect).num<=0)
			DeleteGoods(iSelect);
		return true;
	}
	else
		return false;
}


void MYGOODS::DeleteGoods(int seq)
{
	Pocket pk=man.Getpk(seq);
	pk.ID=0;
	man.Setpk(seq,pk);
	List();
}

void MYGOODS::DeleteGoods(int seq,int num)
{
	Pocket pk=man.Getpk(seq);
	pk.num-=num;
	if(pk.num<=0)
		pk.ID=0;
	man.Setpk(seq,pk);
	List();
}

bool MYGOODS::GetbcontinueUP()
{
	return bcontinueUP;
}

bool MYGOODS::GetbcontinueDOWN()
{
	return bcontinueDOWN;
}

ShowGoods MYGOODS::Getgshow(int seq)
{
	return gshow[seq];
}

GOODS MYGOODS::Getequipe(int seq)
{
	return equipe[seq];
}

GOODS MYGOODS::Getgd(int seq)
{
	return gd[seq];
}