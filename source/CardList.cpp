#include "CardList.h"
using namespace Util;

namespace CardFolder {
	int ViewMode = 0;
	int P_Mode = 0;
	int SelectCard = 0;
	int SelectCommand = 0;
}

void CardFolder::ViewCards() {
	DrawCardList_String(SelectCard);
	switch (ViewMode) {
	case 0:
		if (MenuFlag == 0) {
			if (Key[KEY_INPUT_RIGHT] == 1 || Key[KEY_INPUT_LEFT] == 1) {
				P_Mode = (P_Mode + 1) % 2;
			}
			if (Key[KEY_INPUT_DOWN] == 1 || (Key[KEY_INPUT_DOWN] >= 40 && Key[KEY_INPUT_DOWN] % 10 == 1)) {
				SelectCard++;
				if (SelectCard == Count + 1) {
					SelectCard = 0;
				}
			}
			else if (Key[KEY_INPUT_UP] == 1 || (Key[KEY_INPUT_UP] >= 40 && Key[KEY_INPUT_UP] % 10 == 1)) {
				SelectCard--;
				if (SelectCard == -1) {
					SelectCard = Count;
				}
			}
			if (Key[KEY_INPUT_SPACE] == 1) {
				ViewMode = 1;
			}
		}
		break;
	case 1:
		DrawBox(30, 410, 290, 460, Black, TRUE);
		DrawBox(33, 413, 287, 457, Cr, FALSE);
		DrawString(55, 428,"セット" ,Cr);
		DrawString(135, 428, "編集", Cr);
		DrawString(215, 428, "削除", Cr);
		DrawString(38 + 80 * SelectCommand, 428, "○", Cr);
		if (MenuFlag == 0) {
			if (Key[KEY_INPUT_RIGHT] == 1 || (Key[KEY_INPUT_RIGHT] >= 40 && Key[KEY_INPUT_RIGHT] % 10 == 1)) {
				SelectCommand++;
				if (SelectCommand == 3) {
					SelectCommand = 0;
				}
			}
			else if (Key[KEY_INPUT_LEFT] == 1 || (Key[KEY_INPUT_LEFT] >= 40 && Key[KEY_INPUT_LEFT] % 10 == 1)) {
				SelectCommand--;
				if (SelectCommand == -1) {
					SelectCommand = 2;
				}
			}
			if (Key[KEY_INPUT_SPACE] == 1) {
				switch (SelectCommand) {
				case 0:
					Player[P_Mode] = SelectCard;
					if (Key[KEY_INPUT_SPACE] == 1) {
						ViewMode = 0;
					}
					break;
				case 1:
					ViewMode = (ViewMode + 1) % 2;
					ReCreateID = SelectCard;
					ReCreateFlag = 1;
					Mode = 1;
					if (Key[KEY_INPUT_SPACE] == 1) {
						ViewMode = 0;
					}
					break;
				case 2:
					delete CardList[SelectCard];
					for (int i = SelectCard; i < Count; ++i) {
						CardList[i] = CardList[i + 1];  // 後ろの要素を1つ前へシフト
						if (Player[0] == i) {
							Player[0]--;
						}
					}
					CardList[Count] = nullptr;
					Count--;
					if (Key[KEY_INPUT_SPACE] == 1) {
						ViewMode = 0;
					}
					break;
				}
			}
		}
		break;

	}
}

void CardFolder::DrawCardList_String(int SelectCard) {
	DrawFormatString(5, 10, Cr, "P_%dカード選択中", P_Mode + 1);
	for (int i = 0; i <= Count; i++) {
		if (i == SelectCard) {
			DrawFormatString(30, 40 + 20 * i, Cr, "%s", CardList[i]->NN.c_str());
			DrawCard(300, 50, i);
		}
		else {
			DrawFormatString(10, 40 + 20 * i, Cr, "%s", CardList[i]->NN.c_str());
		}
		if (i == Player[0]) {
			if ((P_Mode == 0 && elapsedTime % 1500 > 750) == FALSE) {
				DrawString(190, 40 + 20 * i, "P_1", GetColor(0, 191, 255));
			}
		}
		if (i == Player[1]) {
			if ((P_Mode == 1 && elapsedTime % 1500 > 750) == FALSE) {
				DrawString(230, 40 + 20 * i, "P_2", GetColor(255, 20, 20));
			}
		}
	}
}

