#include "battle.h"
using namespace Util;

namespace Battle {
	int Rand_Result[2] ={-1,-1};
	int AtkPhase;
	int FinishFlag = 2;
	int ChargeFlag[2] = {-1,-1};
	int BattleMode = 0;
	int SelectBattleCommand = 0;
	int CommandDecision = -1;
	int FinishMenuCommand = 0;
	char FinishMenuStr[4][31]={"再戦","新規カード作成","カードリスト","終了" };
}

void Battle::battle() {
	if (AtkFirst == -1) {
		for (int i = 0; i < 2; i++) {
			if (Character_Rand[i] == 1) {
				Player[i] = GetRand(Count);
			}
			LoadBattleCard(Player[i], i);
			Rand_Result[i] = -1;
			ChargeFlag[i] = -1;
		}
		JudgeFirst();
		FinishFlag = 2;
		BattleMode = 0;
		SelectBattleCommand = 0;
	}
 
	//カードの表示
	for (int i = 0; i < 2; i++) {
		DrawBattleCard(10+320*i, 10, i,ChargeFlag[i]);
	}


	//下部文字枠表示
	DrawBox(30, 415, 610, 475, Black, TRUE);
	DrawBox(33, 418, 607, 472, Cr, FALSE);

	//Roulette結果の表示領域
	DrawBox(282, 13, 307, 38, Black, TRUE);
 	DrawBox(602, 13, 627, 38, Black, TRUE);
	if (MenuFlag == 0) {
		switch (BattleMode) {
		case 0:
			DrawString(50 + 100 * SelectBattleCommand, 436, "〇", Cr);
			DrawString(70, 436, "攻撃", Cr);
			DrawString(170, 436, "道具", Cr);
			//DrawString(270, 436, "必殺技", Cr);
			//if (Key[KEY_INPUT_RIGHT] == 1) {
			//	SelectBattleCommand++;
			//	if (SelectBattleCommand == 3) {
			//		SelectBattleCommand = 0;
			//	}
			//}
			//else if (Key[KEY_INPUT_LEFT] == 1) {
			//	SelectBattleCommand--;
			//	if (SelectBattleCommand == -1) {
			//		SelectBattleCommand = 2;
			//	}
			//}
			if (Key[KEY_INPUT_SPACE] == 1||Key[KEY_INPUT_Q]==1) {
				CommandDecision = SelectBattleCommand;
			}
			break;
		case 1:
			CommandDecision = -1;
			FinishGame();

			break;
		}
	}
	switch (CommandDecision) {
	case 0:
		if (Key[KEY_INPUT_SPACE] == 1) {
			DrawBox(30, 415, 610, 475, Black, TRUE);
			DrawBox(33, 418, 607, 472, Cr, FALSE);
			Roulette();
			ChangeAtk();
		}
		//デバッグ用高速周回
		if (Key[KEY_INPUT_Q] == 1) {
			Attack_Q();
			ChangeAtk();
		}
		break;
	default:
		//DrawBox(30, 415, 610, 475, Black, TRUE);
		//DrawBox(33, 418, 607, 472, Cr, FALSE);

		break;
	}

	//Roulette動作表示
	switch (AtkPhase) {
	case 0:
		DrawFormatString(290, 18, Cr, "%d", nowTime % 6 + 1);
		DrawFormatString(610, 18, Cr, "%d", Rand_Result[1] + 1);
		break;
	case 1:
		DrawFormatString(290, 18, Cr, "%d", Rand_Result[0] + 1);
		DrawFormatString(610, 18, Cr, "%d", nowTime % 6 + 1);
		break;
	}

}

void Battle::Roulette() {
	Rand_Result[AtkPhase] = GetRand(5);
	for (int i = 0; i < 2; i++) {
		DrawFormatString(290 + 320 * i, 18, Cr, "%d", Rand_Result[i] + 1);
	}
	DrawBattleLog();
	BattleMode = 0;
	SelectBattleCommand = 0;
	CommandDecision = -1;
	Attack();
}


void Battle::ResetRoulette() {
	for (int i = 0; i < 2; i++) {
		Rand_Result[i] = -1;
	}
}

void Battle::Attack() {
  		if (ChargeFlag[AtkPhase] == -1) {
			switch (BattleCard[AtkPhase].MoveType[Rand_Result[AtkPhase]]) {
			//通常攻撃
			case 0:
				BattleCard[(AtkPhase+1)%2].HP -= BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]];
				if (BattleCard[(AtkPhase + 1) % 2].HP <= 0) {
					BattleCard[(AtkPhase + 1) % 2].HP = 0;
					FinishFlag = AtkPhase;
					BattleMode = 1;
				}
				break;
			//バフ
			case 1:
				for (int i = 0; i < 6; i++) {
					if (BattleCard[AtkPhase].MoveType[i] == 0) {
						BattleCard[AtkPhase].MovePower[i] += BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]];
					}
					else if (BattleCard[AtkPhase].MoveType[i] == 4) {
						BattleCard[AtkPhase].MovePower[i] += BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]] * 4;
					}
				}
				break;
			//デバフ
			case 2:
				for (int i = 0; i < 6; i++) {
					if (BattleCard[(AtkPhase + 1) % 2].MoveType[i] == 0 || BattleCard[(AtkPhase + 1) % 2].MoveType[i] == 4) {
						BattleCard[(AtkPhase + 1) % 2].MovePower[i] -= BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]];
						if (BattleCard[(AtkPhase + 1) % 2].MovePower[i] < 0) {
							BattleCard[(AtkPhase + 1) % 2].MovePower[i] = 0;
						}
					}
				}
				break;
			//回復
			case 3:
				BattleCard[AtkPhase].HP += BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]];
				if (BattleCard[AtkPhase].HP > BattleCard[AtkPhase].MaxHP) {
					BattleCard[AtkPhase].HP = BattleCard[AtkPhase].MaxHP;
				}
				break;
			//溜め
			case 4:
				if (ChargeFlag[AtkPhase] == -1) {
					ChargeFlag[AtkPhase] = Rand_Result[AtkPhase];
				}
				break;
			}
		}
		else {
			if (ChargeFlag[AtkPhase] == Rand_Result[AtkPhase]) {
				BattleCard[(AtkPhase + 1) % 2].HP -= BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]];
				if (BattleCard[(AtkPhase + 1) % 2].HP <= 0) {
					BattleCard[(AtkPhase + 1) % 2].HP = 0;
					FinishFlag = AtkPhase;
					BattleMode = 1;
				}
				ChargeFlag[AtkPhase] = -1;
			}
		}
		if (ChargeFlag[AtkPhase] != Rand_Result[AtkPhase]) {
			ChargeFlag[AtkPhase] = -1;
		}
}


void Battle::JudgeFirst() {
	AtkFirst = GetRand(1);
	AtkPhase = AtkFirst;
}

void Battle::ChangeAtk() {
	AtkPhase = (AtkPhase + 1) % 2;
}

void Battle::FinishGame() {
	int Select;

	DrawBox(220, 240, 420, 400, Black, TRUE);
	DrawBox(223, 243, 417, 397, Cr, FALSE);
	for (int i = 0; i < 4; i++) {
		if (i == FinishMenuCommand) {
			Select = 20;
		}
		else {
			Select = 0;
		}
		DrawFormatString(235 + Select, 255 + 35 * i, Cr, "%s", FinishMenuStr[i]);
	}
	DrawString(235, 255 + 35 * FinishMenuCommand, "○", Cr);
	if (Key[KEY_INPUT_SPACE] == 1) {
		if (FinishMenuCommand != 3) {
			Mode = FinishMenuCommand;
			AtkFirst = -1;
		}
		else {
			Judge = false;
		}
		FinishMenuCommand = 0;
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		FinishMenuCommand++;
		if (FinishMenuCommand == 4) {
			FinishMenuCommand = 0;
		}
	}
	if (Key[KEY_INPUT_UP] == 1) {
		FinishMenuCommand--;
		if (FinishMenuCommand == -1) {
			FinishMenuCommand = 3;
		}
	}

	DrawJudge();
	//ScreenFlip();
	//WaitKey();
}

void Battle::DrawBattleCard(int X,int Y,int No,int ChargeFlag) {
	DrawBox(X, Y, X + 300, Y + 400, Cr, TRUE);
	DrawFormatString(X + 10, Y + 5, Black, "%s", BattleCard[No].NN.c_str());
	DrawExtendGraph(X + 75, Y + 30, X + 225, Y + 180, BattleCard[No].Image, TRUE);
	DrawBox(X + 10, Y + 30, X + 290, Y + 180, Black, FALSE);
	DrawFormatString(X + 120, Y + 185, Black, "%3d/%3d", BattleCard[No].HP, BattleCard[No].MaxHP);
	if (ChargeFlag != -1) {
		for (int i = 0; i < 6; i++) {
			if (i == ChargeFlag) {
				DrawGraph(X + 5, Y + 212 + 30 * i, BattleIcon[4], TRUE);
				DrawString(X + 40, Y + 220 + 30 * i, "成功", Black);
				DrawFormatString(X + 265, Y + 220 + 30 * i, Black, "%3d", BattleCard[No].MovePower[i]);
			}
			else {
				DrawGraph(X + 5, Y + 212 + 30 * i, BattleIcon[5], TRUE);
				DrawString(X + 40, Y + 220 + 30 * i, "失敗", Black);
				DrawString(X + 265, Y + 220 + 30 * i, "  0", Black);
			}
		}
	}
	else {
		for (int i = 0; i < 6; i++) {
			DrawGraph(X + 5, Y + 212 + 30 * i, BattleIcon[BattleCard[No].MoveType[i]], TRUE);
			//技名の表示
			DrawFormatString(X + 40, Y + 220 + 30 * i, Black, " %s",BattleCard[No].Move[i].c_str());
			//技威力の表示
			DrawFormatString(X + 265, Y + 220 + 30 * i, Black, "%3d", BattleCard[No].MovePower[i]);
		}
	}
}

void Battle::DrawBattleLog() {
	
	if (Rand_Result[AtkPhase] != -1) {
		DrawBox(12 + 320 * AtkPhase, 221 + 30 * Rand_Result[AtkPhase], 308 + 320 * AtkPhase, 253 + 30 * Rand_Result[AtkPhase], Black, FALSE);
	}
	if (ChargeFlag[AtkPhase] == -1) {
		DrawFormatString(45, 425, Cr, "%sの%s", BattleCard[AtkPhase].NN.c_str(), BattleCard[AtkPhase].Move[Rand_Result[AtkPhase]].c_str());
		switch (BattleCard[AtkPhase].MoveType[Rand_Result[AtkPhase]]) {
		case 0:
			DrawFormatString(45, 447, Cr, "%sに%dのダメージ！", BattleCard[(AtkPhase + 1) % 2].NN.c_str(), BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]]);
			break;
		case 1:
			DrawFormatString(45, 447, Cr, "%sの与えるダメージが%d増加！", BattleCard[AtkPhase].NN.c_str(), BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]]);
			break;
		case 2:
			DrawFormatString(45, 447, Cr, "%sの与えるダメージが%d減少！", BattleCard[(AtkPhase + 1) % 2].NN.c_str(), BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]]);
			break;
		case 3:
			DrawFormatString(45, 447, Cr, "%sの体力が%d回復！", BattleCard[AtkPhase].NN.c_str(), BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]]);
			break;
		case 4:
			DrawFormatString(45, 447, Cr, "%sは力を溜めている！", BattleCard[AtkPhase].NN.c_str(), BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]]);
		}
	}
	else {
		DrawFormatString(45, 425, Cr, "%sの%s", BattleCard[AtkPhase].NN.c_str(), BattleCard[AtkPhase].Move[ChargeFlag[AtkPhase]].c_str());
		if (Rand_Result[AtkPhase] == ChargeFlag[AtkPhase]) {
			DrawFormatString(45, 447, Cr, "%sに%dの超ダメージ！", BattleCard[(AtkPhase + 1) % 2].NN.c_str(), BattleCard[AtkPhase].MovePower[Rand_Result[AtkPhase]]);
		}
		else {
			DrawString(45, 447, "しかし失敗してしまった！", Cr);
		}
	}
	ScreenFlip();
	WaitKey();
}

void Battle::DrawJudge() {
	DrawGraph(10+323*FinishFlag, 45, Win, TRUE);
	DrawGraph(10 + 323 * ((FinishFlag + 1) % 2), 45, Lose, TRUE);
}



//デバッグ用
void Battle::Attack_Q() {
	Rand_Result[AtkPhase] = 0;
	BattleCard[(AtkPhase + 1) % 2].HP =0;
	FinishFlag = AtkPhase;
	BattleMode = 1;
}