#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "DxLib.h"
#include "Util.h"
#include "battle.h"
#include "Create.h"
#include "CardList.h"
#include "Title.h"

using namespace Util;
using namespace Battle;
using namespace Create;
using namespace CardFolder;
using namespace Title;

int startTime = GetNowCount();//開始時刻を得る


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//SetGraphMode(1920, 1080, 32);

	ChangeWindowMode(TRUE);		//WindowModeかFullScreenか
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面表示
	//SetFontSize(10);


	LoadGeneralData();
	Judge = LoadCard();
	if (Judge == false) {
		DxLib_End();				// ＤＸライブラリ使用の終了処理
	}

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 &&/* CheckHitKey(KEY_INPUT_ESCAPE) == 0 &&*/ gpUpdateKey() == 0 &&UpdateMouse()==0 && Judge == true) {

		switch (Mode) {
		case -1:
			title();
			break;
		case 0:
			battle();
			break;
		case 1:
			CreateCard();
			break;
		case 2:
			ViewCards();
			break;
		default:
			DrawFormatString(0, 0, Cr, "Default");
		}

		GetMousePoint(&MouseX, &MouseY);

		if (Mode != 0) {
			ResetRoulette();
		}

		if (Key[KEY_INPUT_A] == 1) {
			if (Mode == -1) {
				Mode = 0;
			}
			else {
				Mode = -1;
			}
		}
		//デバッグ用
		//if (Key[KEY_INPUT_0] == 1) {
		//	Mode = 0;
		//	AtkFirst = -1;
		//}
		//if (Key[KEY_INPUT_1] == 1) {
		//	Mode = 1;
		//}
		//if (Key[KEY_INPUT_2] == 1) {
		//	Mode = 2;
		//}

		if (Key[KEY_INPUT_X] == 1) {
			MenuFlag = (MenuFlag + 1) % 2;
		}
		if (MenuFlag == 1) {
			Menu();
		}




		nowTime = GetNowCount();
		elapsedTime = nowTime - startTime;
		//DrawFormatString(500, 0, Cr, "Time:%07d(ms)", elapsedTime);
		Sleep(7); // 7[ms]待機
	}
	ReleaseCard();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了 
}