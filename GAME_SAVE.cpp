#include"stdafx.h"
#include"GAME_SAVE.h"
using namespace std;

extern int GameState;
extern MAN man;
extern MAP map;
extern GAMENPC npc;
extern bool GameBool[GAMEBOOLNUM]; 

void SAVEGAME::Init(ACTIVITY* ac)
{
	act=ac;
}

void SAVEGAME::Savegame()
{
	strcpy(savedata.mappath,act->GetCurrentMap());
	savedata.pt=man.Getpos();
	ofstream sav("save/sav.dat");
	sav<<savedata.mappath<<endl;
	sav<<savedata.pt.x<<endl;
	sav<<savedata.pt.y<<endl;
	sav<<man.GetMand().name<<endl;
	sav<<man.GetMand().path<<endl;
	sav<<man.GetMand().sex<<endl;
	sav<<man.GetMoney()<<endl;
	sav<<man.GetMand().Level<<endl;
	sav<<man.GetMand().Exp<<endl;
	sav<<man.GetMand().Health<<endl;
	sav<<man.GetMand().Power<<endl;
	sav<<man.GetMand().Define<<endl;
	sav<<man.GetMand().Speed<<endl;
	sav<<man.GetEquipe().hand<<endl;
	sav<<man.GetEquipe().body<<endl;
	sav<<man.GetEquipe().foot<<endl;
	for(int i=0;i<20;i++)
	{
		sav<<man.Getpk(i).ID<<" "<<man.Getpk(i).num<<endl;
	}
	for(int i=0;i<GAMEBOOLNUM;i++)
		sav<<GameBool[i]<<endl;
}

void SAVEGAME::Loadgame()
{
	FILE* fp=NULL;
	char temp[32]={};
	POINT pt;
	ManData md;
	Equipe eq;
	fp=fopen("save/sav.dat","r+");
	fgets(temp,32,fp);
	sscanf(temp,"%s",savedata.mappath);
	act->SetCurrentMap(savedata.mappath);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&pt.x);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&pt.y);
	man.Setopos(pt.x/32,(pt.y+16)/32);
	fgets(temp,32,fp);
	sscanf(temp,"%s",md.name);
	fgets(temp,32,fp);
	sscanf(temp,"%s",md.path);
	fgets(temp,32,fp);
	sscanf(temp,"%s",md.sex);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&savedata.pt.x);
	man.SetMoney(savedata.pt.x);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&md.Level);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&md.Exp);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&md.Health);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&md.Power);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&md.Define);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&md.Speed);
	man.SetMand(md);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&eq.hand);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&eq.body);
	fgets(temp,32,fp);
	sscanf(temp,"%d",&eq.foot);
	man.SetEquipe(eq);
	for(int i=0;i<20;i++)
	{
		Pocket pk;
		fgets(temp,32,fp);
		sscanf(temp,"%d%d",&savedata.pt.x,&savedata.pt.y);
		pk.ID=savedata.pt.x;
		pk.num=savedata.pt.y;
		man.Setpk(i,pk);
	}
	for(int i=0;i<GAMEBOOLNUM;i++)
	{
		fgets(temp,32,fp);
		sscanf(temp,"%d",&GameBool[i]);
	}
	fclose(fp);
	iSavlod=1;
}

void SAVEGAME::SetiSavlod(bool tf)
{
	iSavlod=tf;
}

bool SAVEGAME::GetiSavlod()
{
	return iSavlod;
}