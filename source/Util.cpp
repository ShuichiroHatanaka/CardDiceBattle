#include "Util.h"
namespace Util {
	int Key[256] = {};
	int Pad = 0;
	int Mouse[3] = {};
	int Mode = -1;//mode管理
	unsigned int Cr = 0, Black = 0;
	int CommandMode = -1;
	int SelectCommand = 0;
	int Icon[3] = {};
	int Cursor;
	Card* CardList[125] = {};
	Card BattleCard[2] = {};
	int MouseX, MouseY;
	int button;
	int UpButton;
	int DownButton;
	int SelectButton;

	int Count;

	int nowTime;
	int elapsedTime;

	int Player[2] = {0,1};
	int Character_Rand[2] = {};
	int AtkFirst = -1;

	int CreateFlag = 0;
	int ReCreateFlag = 0;
	int ReCreateID = 0;

	int Win;
	int Lose;

	int TitleLogo;


	int MenuFlag = 0;
	int menu = 0;
	int SelectMenuCommand = 0;
	char MenuStr[4][31] = { "バトル","新規カード作成","カードリスト","終了" };
	int Select = 0;

	bool Judge = true;

	int BattleIcon[6];
}

int Util::safe_stoi(const std::string& str, int default_val) {
	try {
		return std::stoi(str);
	}
	catch (...) {
		return default_val;
	}
}

float Util::safe_stof(const std::string& str, float default_val) {
	try {
		return std::stof(str);
	}
	catch (...) {
		return default_val;
	}
}

void Util::LoadGeneralData() {
	Cr = GetColor(255, 255, 255);
	Black = GetColor(0, 0, 0);
	button = LoadGraph("img/button.png");
	UpButton = LoadGraph("img/UpButton.png");
	DownButton = LoadGraph("img/DownButton.png");
	SelectButton = LoadGraph("img/SelectButton.png");
	Win = LoadGraph("img/Win.png");
	Lose = LoadGraph("img/Lose.png");
	TitleLogo = LoadGraph("img/TitleLogo.png");
	LoadDivGraph("img/BattleIcons.png", 6, 6, 1, 30, 30, BattleIcon);
}

// キーの入力状態を更新する
int Util::gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

// マウスの入力状態を更新する
int Util::UpdateMouse() {
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		Mouse[0]++;
	}
	else {
		Mouse[0] = 0;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		Mouse[1]++;
	}
	else {
		Mouse[1] = 0;
	}
	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0) {
		Mouse[2]++;
	}
	else {
		Mouse[2] = 0;
	}
	//DrawFormatString(0, 300, Cr, "%d/%d/%d", Mouse[0],Mouse[1],Mouse[2]);
	return 0;
}

void Util::DrawCard(int X,int Y, int No) {
	DrawBox(X, Y, X+300, Y+400, Cr, TRUE);
	DrawFormatString(X+10, Y+5, Black, "%s",CardList[No]->NN.c_str());
	DrawExtendGraph(X + 75, Y + 30, X + 225, Y + 180, CardList[No]->Image, TRUE);
	DrawBox(X + 10, Y + 30, X + 290, Y + 180, Black, FALSE);
	DrawFormatString(X + 120, Y + 185, Black, "%3d/%3d", CardList[No]->HP, CardList[No]->MaxHP);
	for (int i = 0; i < 6; i++) {
		DrawGraph(X + 5, Y + 212 + 30 * i, BattleIcon[CardList[No]->MoveType[i]], TRUE);
		DrawFormatString(X + 40, Y + 220 + 30 * i, Black, " %s",CardList[No]->Move[i].c_str());
		DrawFormatString(X + 265, Y + 220 + 30 * i, Black, "%3d", CardList[No]->MovePower[i]);
	}
}

bool Util::LoadCard() {
	std::ifstream CardPic("CSV/CardList.csv");
	if (!CardPic.is_open()) {
		std::cerr << "ファイルが開けません: CSV/CardList.csv" << std::endl;
		return false;
	}

	std::string line;
	for (int i = 0; i < Max && std::getline(CardPic, line); i++) {
		CardList[i] = new Util::Card{};
		std::stringstream ss(line);
		std::string temp;

		std::getline(ss, temp, ','); CardList[i]->ID = safe_stoi(temp);
		std::getline(ss, CardList[i]->NN, ',');
		std::getline(ss, temp, ','); CardList[i]->MaxHP = safe_stoi(temp);
		CardList[i]->HP = CardList[i]->MaxHP;
		for (int j = 0; j < 6; j++) {
			std::getline(ss, CardList[i]->Move[j], ',');
		}
		for (int j = 0; j < 6; j++) {
			std::getline(ss, temp, ','); CardList[i]->MovePower[j] = safe_stoi(temp);
		}
		for (int j = 0; j < 6; j++) {
			std::getline(ss, temp, ','); CardList[i]->MoveType[j] = safe_stoi(temp);
		}
		std::getline(ss, CardList[i]->Pass, ',');
		char buffer[256];
		strncpy_s(buffer, sizeof(buffer), CardList[i]->Pass.c_str(), _TRUNCATE);
		buffer[sizeof(buffer) - 1] = '\0';  // 念のため終端
		CardList[i]->Image = LoadGraph(buffer);
		Count = i;
	}

	CardPic.close();

	LoadBattleCard(0, 0);
	LoadBattleCard(0, 1);
	return true;
}

void Util::ReleaseCard() {
	SaveAllCard();
	for (int i = 0; i < Max; i++) {
		delete CardList[i];
	}
}

void Util::LoadBattleCard(int ID,int Party) {
	BattleCard[Party] = *CardList[ID];
}

void Util::Menu() {
	DrawBox(220, 240, 420, 400, Black, TRUE);
	DrawBox(223, 243, 417, 397, Cr, FALSE);
	for (int i = 0; i < 4; i++) {
		if (i == SelectMenuCommand) {
			Select = 20;
		}
		else {
			Select = 0;
		}
		DrawFormatString(235 + Select, 255 + 35 * i, Cr, "%s", MenuStr[i]);
	}
	DrawString(235, 255 + 35 * SelectMenuCommand, "○", Cr);
	if (Key[KEY_INPUT_SPACE] == 1) {
		MenuFlag = 0;
		if (SelectMenuCommand != 3) {
			Mode = SelectMenuCommand;
			AtkFirst = -1;
			CreateFlag = 0;
			ReCreateID = -1;
		}
		else {
			Judge = false;
		}
		SelectMenuCommand = 0;
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		SelectMenuCommand++;
		if (SelectMenuCommand == 4) {
			SelectMenuCommand = 0;
		}
	}
	if (Key[KEY_INPUT_UP] == 1) {
		SelectMenuCommand--;
		if (SelectMenuCommand == -1) {
			SelectMenuCommand = 3;
		}
	}
}

void Util::SaveAllCard() {
	//Box情報書き出し
	std::ofstream fout("CSV/CardList.csv");
	if (!fout.is_open()) {
		std::cerr << "ファイルが開けません\n";
	}
	for (int i = 0; i < Max&&CardList[i]!=nullptr; i++) {
		fout << i << ",";
		fout << CardList[i]->NN << ",";
		fout << CardList[i]->HP << ",";
		for (int j = 0; j < 6; j++) {
			fout << CardList[i]->Move[j] << ",";
		}

		for (int j = 0; j < 6; j++) {
			fout << CardList[i]->MovePower[j] << ",";
		}
		for (int j = 0; j < 6; j++) {
			fout << CardList[i]->MoveType[j] << ",";
		}
		fout << CardList[i]->Pass << "\n";
	}

	fout.close();

}