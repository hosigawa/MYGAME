#include"stdafx.h"
#include"GAME_KEY.h"
#include"GAME_TEXT.h"

extern int GameState;
extern MAN man;
extern MAP map;
extern GAMENPC npc;
extern bool GameBool[GAMEBOOLNUM]; 

void KEYPROC::Init(ACTIVITY* act,MAINFACE* mf,MENUFACE* mef,MYBATTLE* mb,MYGOODS* mg,TEXTPRINT* tx,MYCONFIRM* mc,MANSTATE* ms,MYSHOP* sp)
{
	pact=act;
	pmf=mf;
	pmef=mef;
	pmb=mb;
	pmg=mg;
	ptx=tx;
	pmc=mc;
	pms=ms;
	pmsp=sp;
}

void KEYPROC::KeyDwon(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	hwnd=hWnd;
	switch(GameState)
	{
	case NORMALMODE:
		KeyNormal(hWnd,wParam,lParam);
		break;
	case FACEMODE:
		KeyFace(hWnd,wParam);
		break;
	case MENUMODE:
		KeyMenu(hWnd,wParam);
		break;
	case TALKMODE:
		KeyTalk(hWnd,wParam);
		break;
	case GOODSMODE:
		KeyGoods(hWnd,wParam);
		break;
	case BATTLEMODE:
		KeyBattle(hWnd,wParam);
		break;
	case BATTLEMENUMODE:
		KeyBattleMenu(hWnd,wParam);
		break;
	case STATEMODE:
		KeyState(hWnd,wParam);
		break;
	case BATTLESUBMENUMODE:
		KeyBattleSubMenu(hWnd,wParam);
		break;
	case CONFIRMMODE:
		KeyConfirm(hWnd,wParam);
		break;
	case SHOPMODE:
		KeyShop(hWnd,wParam);
		break;
	case SHOPSUBMODE:
		KeyShopSub(hWnd,wParam);
		break;
	case GAMEOVER:
	case GAMEEND:
		GameState=FACEMODE;
		break;
	}
}

void KEYPROC::KeyUp()
{
	//man.bRolerun=0;
}

void KEYPROC::KeyNormal(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if(!man.GetbRolerun())
	{
		int wen=man.Getwens();
		switch(wParam)
		{
		case VK_RIGHT:
			man.Setwens(2);
			if(wen==man.Getwens())
				man.SetbRolerun(true);
			break;
		case VK_LEFT:
			man.Setwens(1);
			if(wen==man.Getwens())
				man.SetbRolerun(true);
			break;
		case VK_UP:
			man.Setwens(3);
			if(wen==man.Getwens())
				man.SetbRolerun(true);
			break;
		case VK_DOWN:
			man.Setwens(0);
			if(wen==man.Getwens())
				man.SetbRolerun(true);
			break;
		case VK_RETURN:
			Selecttx=pact->SerchText();
			if(Selecttx!=-1)
			{
				ptx->Setbtalk(true);
				ptx->SelectText(npc.man[Selecttx].GetMand().Id);
			}
			break;
		case VK_ESCAPE:
			GameState=MENUMODE;
			break;
		case VK_SPACE:/*
			if(iChangeCloth==0)
			{
				pact->OnMan("pic/role/sailormoon.bmp");
				iChangeCloth++;
				if(iChangeCloth==3)
					iChangeCloth=0;
			}
			else if(iChangeCloth==1)
			{
				pact->OnMan("pic/role/princess.bmp");
				iChangeCloth++;
				if(iChangeCloth==3)
					iChangeCloth=0;
			}
			else if(iChangeCloth==2)
			{
				pact->OnMan("pic/role/usagitsukino.bmp");
				iChangeCloth++;
				if(iChangeCloth==3)
					iChangeCloth=0;
			}*/
			break;
			//default:
		}
	}
}

void KEYPROC::KeyFace(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_UP:
		pmf->SelectCur(0,3);
		break;
	case VK_DOWN:
		pmf->SelectCur(1,3);
		break;
	case VK_RETURN:
		pmf->Entry();
		break;
	}
}

void KEYPROC::KeyMenu(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_UP:
		pmef->SelectCur(0,6);
		break;
	case VK_DOWN:
		pmef->SelectCur(1,6);
		break;
	case VK_ESCAPE:
		GameState=NORMALMODE;
		break;
	case VK_RETURN:
		pmef->Entry();
		break;
	}
}

void KEYPROC::KeyTalk(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_RETURN:
		SetAction(ptx->Gettxtemp());
		break;
	}
}

void KEYPROC::KeyGoods(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_ESCAPE:
		GameState=NORMALMODE;
		break;
	case VK_UP:
		pmg->SelectCur(0);
		break;
	case VK_DOWN:
		pmg->SelectCur(1);
		break;
	case VK_RETURN:
		if(pmg->Getgshow(0).gd.ID&&(pmg->Getgshow(0).gd.bEquipe||pmg->Getgshow(0).gd.bUseful))
			pmc->Confirm(GameState,0);
		break;
	}
}

void KEYPROC::KeyBattle(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	/*case VK_RETURN:
		GameState=BATTLEMENUMODE;
		break;
	case VK_ESCAPE:
		GameState=NORMALMODE;
		break;
		*/
	}
}

void KEYPROC::KeyBattleMenu(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_UP:
		if(!pmb->Getbwin())
			pmb->SelectCur(0,3);
		break;
	case VK_DOWN:
		if(!pmb->Getbwin())
			pmb->SelectCur(1,3);
		break;
	case VK_RETURN:
		if(!pmb->Getbwin())
		{
			pmg->List();
			pmb->Entry();
		}
		else
		{
			GameState=NORMALMODE;
		}
		break;
	case VK_ESCAPE:
		//GameState=NORMALMODE;
		break;
	}
}

void KEYPROC::KeyBattleSubMenu(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_UP:
		pmg->SelectCur(0);
		break;
	case VK_DOWN:
		pmg->SelectCur(1);
		break;
	case VK_RETURN:
		if(pmg->Getgshow(0).gd.bUseful)
		{
			pmb->SetbUseGoods(0,1);
			GameState=BATTLEMODE;
			pmg->UseGoods();
		}
		else
			GameState=BATTLEMENUMODE;
		break;
	case VK_ESCAPE:
		GameState=BATTLEMENUMODE;
		break;
	}
}

void KEYPROC::KeyState(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_UP:
		pms->SetCur(0);
		break;
	case VK_DOWN:
		pms->SetCur(1);
		break;
	case VK_RETURN:
		if(pmg->Getequipe(pms->GetiSelect()).ID)
			pmc->Confirm(GameState,pms->GetiSelect());
		break;
	case VK_ESCAPE:
		GameState=NORMALMODE;
		break;
	}
}


void KEYPROC::SetAction(TextData txtmp)///执行文本脚本中读出来的函数
{
	ManData md;
	switch(txtmp.fun)
	{
	case 0:
		GameState=NORMALMODE;
		break;
	case 1:
		GameBool[txtmp.param2]=true;
		if(!txtmp.param1)
			GameState=NORMALMODE;
		else
		{
			if(Selecttx<64)
				ptx->SelectText(npc.man[Selecttx].GetMand().Id);
			else
				ptx->SelectText(0);
		}
		break;
	case 2:
		pmb->GetEnemy(Selecttx,txtmp.param3);
		GameState=BATTLEMENUMODE;
		break;
	case 3:
		pmg->AddGoods(txtmp.param1,txtmp.param2);
		if(txtmp.param3)
			GameBool[txtmp.param3]=true;
		GameState=NORMALMODE;
		break;
	case 4:
		break;
	case 6:
		pact->SetbPlaysound(true);
		pmsp->SetShopMode(txtmp.param1);
		GameState=SHOPSUBMODE;
		break;
	case 7:
		npc.man[Selecttx].MovePlace(txtmp.param1);
		if(txtmp.param3)
			GameBool[txtmp.param3]=true;
		GameState=NORMALMODE;
		break;
	case 8:
		man.SetMoney(man.GetMoney()+txtmp.param1);
		if(txtmp.param3)
			GameBool[txtmp.param3]=true;
		GameState=NORMALMODE;
		break;
	case 9:
		GameState=GAMEEND;
		break;
	}
}

void KEYPROC::KeyConfirm(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_LEFT:
		pmc->SelectCur(1);
		break;
	case VK_RIGHT:
		pmc->SelectCur(0);
		break;
	case VK_RETURN:
		pmc->entry();
		break;
	case VK_ESCAPE:
		GameState=pmc->Getigamestate();
		break;
	}
}

void KEYPROC::KeyShop(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
		case VK_UP:
			pmsp->SetCur(1);
			break;
		case VK_DOWN:	
			pmsp->SetCur(0);
			break;
		case VK_LEFT:
			pmsp->SetCur(3);
			break;
		case VK_RIGHT:
			pmsp->SetCur(2);
			break;
		case VK_RETURN:
			if(pmsp->GetiSubSelect()==1&&pmg->Getgshow(0).gd.ID)
				pmc->Confirm(GameState,pmsp->GetiSubSelect(),pmsp->GetiSelect());
			else if(pmsp->GetiSubSelect()==0&&pmsp->Getsg(pmsp->GetiSelect()).ID)
				pmc->Confirm(GameState,pmsp->GetiSubSelect(),pmsp->GetiSelect());
			break;
		case VK_ESCAPE:
			GameState=SHOPSUBMODE;
			break;
	}
}

void KEYPROC::KeyShopSub(HWND hWnd,WPARAM wParam)
{
	switch(wParam)
	{
		case VK_LEFT:
			pmsp->SetSubCur(1);
			break;
		case VK_RIGHT:
			pmsp->SetSubCur(0);
			break;
		case VK_RETURN:
			pmsp->entry();
			break;
		case VK_ESCAPE:
			//GameState;
			break;
	}
}

void KEYPROC::SetSelecttx(int i)
{
	Selecttx=i;
}

int KEYPROC::GetSelecttx()
{
	return Selecttx;
}
