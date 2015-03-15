#include"stdafx.h"
#include"GAME_SHOP.h"

extern int GameState;
extern MAN man;

void MYSHOP::Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme,MYGOODS* mg)
{
	phdcmem=hdcme;
	phcombmp=hcombm;
	hwnd=hWnd;
	pmg=mg;
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
	hbmp=(HBITMAP)LoadImage(hinstance,"pic/bkground/shop.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	SelectObject(hdcdest,hbmp);
	if(GameState==SHOPSUBMODE)
		iSubSelect=0;
}

void MYSHOP::Draw(HDC hdc)
{
	BitBlt(hdc,0,0,640,480,hdcdest,0,0,SRCCOPY);
	if(GameState==SHOPSUBMODE)
	{
		txtool.TextOutTx(hdc,50,350,"欢迎光临,您想做些什么呢？",24,txtool.SetFont(RGB(255,255,255),20,15));
		txtool.TextOutTx(hdc,105,120,"购物看板",8,txtool.SetFont(RGB(255,255,0),20,15));
		if(!iSubSelect)
		{
			txtool.TextOutTx(hdc,100,400,"买入",4,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,15));
			txtool.TextOutTx(hdc,300,400,"卖出",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,15));
			txtool.TextOutTx(hdc,500,400,"离开",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,15));
		}
		else if(1==iSubSelect)
		{
			txtool.TextOutTx(hdc,100,400,"买入",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,15));
			txtool.TextOutTx(hdc,300,400,"卖出",4,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,15));
			txtool.TextOutTx(hdc,500,400,"离开",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,15));
		}
		else if(2==iSubSelect)
		{
			txtool.TextOutTx(hdc,100,400,"买入",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,15));
			txtool.TextOutTx(hdc,300,400,"卖出",4,txtool.SetFont(RGB(0,0,0),RGB(255,255,255),20,15));
			txtool.TextOutTx(hdc,500,400,"离开",4,txtool.SetFont(RGB(0,0,0),RGB(255,0,0),20,15));
		}
		//txtool.TextOutTx(hdc,50,50,"kaka",4,txtool.SetFont(RGB(255,255,0),20,12));
	}
	else if(GameState==SHOPMODE)
	{
		txtool.TextOutTx(hdc,400,400,"金钱:",5,txtool.SetFont(RGB(255,255,255),20,15));
		txtool.TextOutTx(hdc,500,400,txtool.itos(man.GetMoney()).snum,txtool.itos(man.GetMoney()).lenth,txtool.SetFont(RGB(255,255,255),20,15));
		if(iSubSelect==0)
		{
			if(!nomoney)
				txtool.TextOutTx(hdc,50,350,"您需要些什么？",13,txtool.SetFont(RGB(255,255,255),20,15));
			else
				txtool.TextOutTx(hdc,50,350,"您的金钱不足！",14,txtool.SetFont(RGB(255,255,255),20,15));
			txtool.TextOutTx(hdc,60,50,"商品名",6,txtool.SetFont(RGB(255,255,0),20,15));
			txtool.TextOutTx(hdc,200,50,"单价",4,txtool.SetFont(RGB(255,255,0),20,15));
			txtool.TextOutTx(hdc,30,(iSelect%5)*30+90,"★",2,txtool.SetFont(RGB(255,0,255),20,10));
			txtool.TextOutTx(hdc,153,240,txtool.itos(iSelect/5+1).snum,1,txtool.SetFont(RGB(255,255,0),20,10));
			txtool.TextOutTx(hdc,165,240,"/4",2,txtool.SetFont(RGB(255,255,0),20,10));
			if(iSelect<5)
			{
				for(int i=0;i<5;i++)
				{
					if(sg[i].ID!=0)
					{
						txtool.TextOutTx(hdc,50,90+30*(i%5),GetName(sg[i].ID).name,GetName(sg[i].ID).lenth,txtool.SetFont(RGB(255,255,0),20,15));
						txtool.TextOutTx(hdc,220,90+30*(i%5),txtool.itos(sg[i].price).snum,txtool.itos(sg[i].price).lenth,txtool.SetFont(RGB(255,255,0),20,15));
					}
					else
						txtool.TextOutTx(hdc,50,90+30*(i%5),"已售罄",6,txtool.SetFont(RGB(180,180,180),20,15));
				}
			}
			else if(iSelect>=5&&iSelect<10)
			{
				for(int i=5;i<10;i++)
				{
					if(sg[i].ID!=0)
					{
						txtool.TextOutTx(hdc,50,90+30*(i%5),GetName(sg[i].ID).name,GetName(sg[i].ID).lenth,txtool.SetFont(RGB(255,255,0),20,15));
						txtool.TextOutTx(hdc,220,90+30*(i%5),txtool.itos(sg[i].price).snum,txtool.itos(sg[i].price).lenth,txtool.SetFont(RGB(255,255,0),20,15));
					}
					else
						txtool.TextOutTx(hdc,50,90+30*(i%5),"已售罄",6,txtool.SetFont(RGB(180,180,180),20,15));
				}
			}
			else if(iSelect>=10&&iSelect<15)
			{
				for(int i=10;i<15;i++)
				{
					if(sg[i].ID!=0)
					{
						txtool.TextOutTx(hdc,50,90+30*(i%5),GetName(sg[i].ID).name,GetName(sg[i].ID).lenth,txtool.SetFont(RGB(255,255,0),20,15));
						txtool.TextOutTx(hdc,220,90+30*(i%5),txtool.itos(sg[i].price).snum,txtool.itos(sg[i].price).lenth,txtool.SetFont(RGB(255,255,0),20,15));
					}
					else
						txtool.TextOutTx(hdc,50,90+30*(i%5),"已售罄",6,txtool.SetFont(RGB(180,180,180),20,15));
				}
			}
			else if(iSelect>=15&&iSelect<20)
			{
				for(int i=15;i<20;i++)
				{
					if(sg[i].ID!=0)
					{
						txtool.TextOutTx(hdc,50,90+30*(i%5),GetName(sg[i].ID).name,GetName(sg[i].ID).lenth,txtool.SetFont(RGB(255,255,0),20,15));
						txtool.TextOutTx(hdc,220,90+30*(i%5),txtool.itos(sg[i].price).snum,txtool.itos(sg[i].price).lenth,txtool.SetFont(RGB(255,255,0),20,15));
					}
					else
						txtool.TextOutTx(hdc,50,90+30*(i%5),"已售罄",6,txtool.SetFont(RGB(180,180,180),20,15));
				}
			}
			
		}
		else if(iSubSelect==1)
		{
			txtool.TextOutTx(hdc,50,350,"您想出售什么？",13,txtool.SetFont(RGB(255,255,255),20,15));
			txtool.TextOutTx(hdc,60,50,"所持物",6,txtool.SetFont(RGB(255,255,0),20,15));
			txtool.TextOutTx(hdc,200,50,"数量",4,txtool.SetFont(RGB(255,255,0),20,15));
			txtool.TextOutTx(hdc,50,90+30*0,pmg->Getgshow(0).gd.name,pmg->Getgshow(0).gd.namelenth,txtool.SetFont(RGB(255,255,0),RGB(255,0,255),20,15));
			if(pmg->Getgshow(0).gd.ID)
				txtool.TextOutTx(hdc,220,90+30*0,txtool.itos(pmg->Getgshow(0).num).snum,txtool.itos(pmg->Getgshow(0).num).lenth,txtool.SetFont(RGB(255,255,0),RGB(255,0,255),20,15));
			for(int i=1;i<5;i++)
			{
				if(pmg->Getgshow(i).gd.ID)
				{
					txtool.TextOutTx(hdc,50,90+30*i,pmg->Getgshow(i).gd.name,pmg->Getgshow(i).gd.namelenth,txtool.SetFont(RGB(255,255,0),20,15));
					txtool.TextOutTx(hdc,220,90+30*i,txtool.itos(pmg->Getgshow(i).num).snum,txtool.itos(pmg->Getgshow(i).num).lenth,txtool.SetFont(RGB(255,255,0),20,15));
				}
			}
			if(pmg->GetbcontinueUP())
				txtool.TextOutTx(hdc,153,70,"▲",2,txtool.SetFont(RGB(255,255,0),20,15));
			if(pmg->GetbcontinueDOWN())
				txtool.TextOutTx(hdc,153,240,"▼",2,txtool.SetFont(RGB(255,255,0),20,15));
		}
	}
}

void MYSHOP::SetSubCur(int sle)
{
	switch(sle)
	{
	case 0:
		iSubSelect++;
		if(iSubSelect==3)
			iSubSelect=0;
		break;
	case 1:
		iSubSelect--;
		if(iSubSelect==-1)
			iSubSelect=2;
		break;
	}
}

void MYSHOP::SetCur(int sle)
{
	nomoney=0;
	if(iSubSelect==0)
	{
		switch(sle)
		{
		case 0:
			iSelect=min(iSelect+1,19);
			break;
		case 1:
			iSelect=max(iSelect-1,0);
			break;
		case 2:
			iSelect=min(iSelect+5,19);
			break;
		case 3:
			iSelect=max(iSelect-5,0);
		}
	}
	else if(iSubSelect==1)
	{
		switch(sle)
		{
		case 0:
			pmg->SelectCur(1);
			pmg->List();
			break;
		case 1:
			pmg->SelectCur(0);
			pmg->List();
			break;
		}
	}
}

void MYSHOP::entry()
{
	switch(iSubSelect)
	{
	case 0:
	case 1:
		pmg->List();
		GameState=SHOPMODE;
		break;
	case 2:
		GameState=NORMALMODE;
		break;
	}
}

Name MYSHOP::GetName(int ID)
{
	for(int i=0;i<GOODSNUM;i++)
	{
		if(ID==pmg->Getgd(i).ID)
		{	
			Name name;
			for(int j=0;j<32;j++)
				name.name[j]=pmg->Getgd(i).name[j];
			name.lenth=pmg->Getgd(i).namelenth;
			return name;
		}
	}
}

void MYSHOP::SetShopMode(int mode)
{
	PlaySound("sound/shop.wav",NULL,SND_LOOP|SND_ASYNC);
	switch(mode)
	{
	case 1:
		sg[0].ID=1;
		sg[0].price=20;
		sg[1].ID=2;
		sg[1].price=80;
		sg[2].ID=3;
		sg[2].price=200;
		break;
	case 2:
		sg[0].ID=5;
		sg[0].price=50;
		sg[1].ID=6;
		sg[1].price=100;
		sg[2].ID=7;
		sg[2].price=50;
		sg[3].ID=8;
		sg[3].price=100;
		break;
	}
}

int MYSHOP::GetPrice()
{
	if(iSubSelect==0)
	{
		return sg[iSelect].price;
	}
	else if(iSubSelect==1)
	{
		for(int i=0;i<20;i++)
		{
			if(pmg->Getgshow(0).gd.ID==sg[i].ID)
				return sg[i].price;
		}
		return 1;
	}
}


void MYSHOP::BuySell(int mode)
{
	switch(mode)
	{
	case 0:
		if(man.GetMoney()<sg[iSelect].price)
			nomoney=1;
		else
		{
			man.SetMoney(max(man.GetMoney()-sg[iSelect].price,0));
			pmg->AddGoods(sg[iSelect].ID,1);
		}
		break;
	case 1:
		man.SetMoney(GetPrice()+man.GetMoney());
		pmg->DeleteGoods(pmg->Getgshow(0).seq-1,1);
		break;
	}
}

int MYSHOP::GetiSelect()
{
	return iSelect;
}

int MYSHOP::GetiSubSelect()
{
	return iSubSelect;
}

bool MYSHOP::Getnomoney()
{
	return nomoney;
}

ShopGoods MYSHOP::Getsg(int seq)
{
	return sg[seq];
}