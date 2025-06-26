#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tchar.h>
#include "DxLib.h"
#define Max 125

namespace Util {

    extern int Key[256];
    extern int Pad;
    extern int Mouse[3];
    extern int Mode;
    extern unsigned int Cr; 
    extern unsigned int Black;
    extern int MouseX, MouseY;
    extern int button;
    extern int UpButton;
    extern int DownButton;
    extern int SelectButton;
    extern int Count;
    extern int nowTime;
    extern int elapsedTime;

    extern int Player[2];
    extern int Character_Rand[2];
    extern int AtkFirst;

    extern int CreateFlag;
    extern int ReCreateFlag;
    extern int ReCreateID;

    extern int Win, Lose;

    extern int TitleLogo;
    extern int MenuFlag;

    extern bool Judge;

    extern int BattleIcon[6];

    int safe_stoi(const std::string& str, int default_val = 0);
    float safe_stof(const std::string& str, float default_val = 0);
    void DrawCard(int, int, int);

	typedef struct {
		int ID;	//カードID
		std::string NN;//ニックネーム
        int HP;
        int MaxHP;
        std::string Move[6];
		int MovePower[6];
        int MoveType[6];
        std::string Pass;
        int Image;
	}Card;
	extern Card* CardList[125];
    extern Card BattleCard[2];

    bool LoadCard();
    void SaveAllCard();
    void ReleaseCard();

    void LoadGeneralData();//Data全般の読み込み
    void LoadBattleCard(int,int);
    int gpUpdateKey();
    int UpdateMouse();
    void Menu();
}