#pragma once

#include"GAME_BITMAP.h"
#include<string>
#include<stdio.h>
using namespace std;

struct IToS
{
	char snum[8];
	int lenth;
};
struct TextData
{
	int TextID;
	int termform;
	int size;
	char TextTemp[512];
	int fun;
	int param1;
	int param2;
	int param3;
};

struct Name
{
	char name[32];
	int lenth;
};

struct Font
{
	HFONT hfont,temphfont;
	COLORREF textColor,BkColor,tmptxcolor,tmpbkcolor;
	int height;
	int wight;
	//int BkMode;
	bool bTransparentMode;
};

class TEXTPRINT : public MYBITMAP
{
private:
	HBITMAP* phcombmp;
	HDC* phdcmem;
	HWND hwnd;
	TextData txd[TEXTNUM];
	TextData txtemp,txtmp[64];
	char text[512],name[32];
	int Size;
	int textnum;
	bool btalk;    //检测对话转向
public:
	TEXTPRINT();
	~TEXTPRINT();
	void Load(char* textpath);
	void Init(HINSTANCE hinstance,HWND hWnd,HBITMAP* hcombm,HDC* hdcme);
	void SelectText(int id);
	void Print(HDC hdc);
	IToS itos(int i);     //将数字转化为输出用字符串
	Font SetFont(COLORREF textColor,int height,int wight);
	Font SetFont(COLORREF textColor,COLORREF BkColor,int height,int wight);
	void TextOutTx(__in HDC hdc, __in int x, __in int y, __in_ecount(c) LPCSTR lpString, __in int c,Font ft);
	void SetText(char* ch,int size);
	TextData Gettxtemp();
	bool Getbtalk();
	void Setbtalk(bool tf);
};