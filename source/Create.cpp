#include "Create.h"
using namespace Util;
#define MaxPoint 1000

namespace Create {
    char Name[31];
	int HP=200;
	char Move[6][31];
	int Flag = -1;
	Card* newCardList[30];
	int newCardID = -1;
	int Type[6] = {};
	int MovePower[6] = {};
	int Remain = MaxPoint - HP;
	int Image;
	char Pass[255];
}

void Create::CreateCard() {
	if (CreateFlag == 0) {
		Name[0] = '\0';
		HP = 200;
		for (int i = 0; i < 6; i++) {
			Move[i][0] = '\0';
			Type[i] = 0;
			MovePower[i] = 0;
		}
		Flag = -1;
		newCardID = -1;
		Image = 0;
		Pass[0] = '\0';
		Remain = MaxPoint - HP;
		CreateFlag = 1;
	}
	if (ReCreateFlag == 1) {
		strcpy_s(Name, sizeof(Name), CardList[ReCreateID]->NN.c_str());
		HP = CardList[ReCreateID]->HP;
		for (int i = 0; i < 6; i++) {
			strcpy_s(Move[i], sizeof(Move[i]), CardList[ReCreateID]->Move[i].c_str());
			Type[i] = CardList[ReCreateID]->MoveType[i];
			MovePower[i] = CardList[ReCreateID]->MovePower[i];
		}
		Image = CardList[ReCreateID]->Image;
		strcpy_s(Pass, sizeof(Pass), CardList[ReCreateID]->Pass.c_str());


		Remain = MaxPoint - HP;
		for (int i = 0; i < 6; i++) {
			Remain -= MovePower[i];
		}

		ReCreateFlag = 2;
	}

    DrawNewCard();

	DrawButtons();
	if (MenuFlag == 0) {
		if (Mouse[0] == 1 || (Mouse[0] > 40 && Mouse[0] % 15 == 0)) {
			Button();
			Remain = MaxPoint - HP;
			for (int i = 0; i < 6; i++) {
				Remain -= MovePower[i];
			}
		}

		ChangeName();
	}
}


void Create::DrawNewCard() {
	int X = 160, Y = 40;
	DrawBox(X, Y, X+300, Y+400, Cr, TRUE);
	DrawFormatString(X+10, Y+5, Black, "%s",Name);
	DrawExtendGraph(X + 75, Y + 30, X + 225, Y + 180, Image, TRUE);
	DrawBox(X + 10, Y + 30, X + 290, Y + 180, Black, FALSE);
	DrawFormatString(X + 120, Y + 185, Black, "%3d/%3d", HP, HP);
	for (int i = 0; i < 6; i++) {
		DrawGraph(X + 5, Y + 212 + 30 * i, BattleIcon[Type[i]], TRUE);
		DrawFormatString(X + 40, Y + 220 + 30 * i, Black, " %s", Move[i]);
	}
}

void Create::SaveNewCard() {
	Count++;
	CardList[Count] = new Util::Card{};
	CardList[Count]->ID = Count;
	CardList[Count]->NN = Name;
	CardList[Count]->HP = HP;
	CardList[Count]->MaxHP = HP;
	for (int i = 0; i < 6; i++) {
		CardList[Count]->Move[i] = Move[i];
		CardList[Count]->MovePower[i] = MovePower[i];
		CardList[Count]->MoveType[i] = Type[i];
	}
	CardList[Count]->Pass = Pass;
	CardList[Count]->Image = LoadGraph(Pass);


	//Box��񏑂��o��
	std::ofstream fout("CSV/CardList.csv");
	if (!fout.is_open()) {
		std::cerr << "�t�@�C�����J���܂���\n";
	}
	for (int i = 0; i < Max; i++) {
		if (!CardList[i]) continue;  // nullptr�`�F�b�N

		fout << CardList[i]->ID << ",";
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
	//�J�[�h���X�g�ֈړ�
	Mode = 2;
}

void Create::SaveCard() {
	CardList[ReCreateID] = new Util::Card{};
	CardList[ReCreateID]->ID = Count;
	CardList[ReCreateID]->NN = Name;
	CardList[ReCreateID]->HP = HP;
	CardList[ReCreateID]->MaxHP = HP;
	for (int i = 0; i < 6; i++) {
		CardList[ReCreateID]->Move[i] = Move[i];
		CardList[ReCreateID]->MovePower[i] = MovePower[i];
		CardList[ReCreateID]->MoveType[i] = Type[i];
	}
	CardList[ReCreateID]->Pass = Pass;
	CardList[ReCreateID]->Image = LoadGraph(Pass);


	//Box��񏑂��o��
	std::ofstream fout("CSV/CardList.csv");
	if (!fout.is_open()) {
		std::cerr << "�t�@�C�����J���܂���\n";
	}
	for (int i = 0; i < Max; i++) {
		if (!CardList[i]) continue;  // nullptr�`�F�b�N

		fout << CardList[i]->ID << ",";
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
	//�J�[�h���X�g�ֈړ�
	Mode = 2;
}

void Create::Button() {

	//���O�E�Z�ύX
	if (Flag == -1) {
		if (MouseX >= 400 && MouseX <= 460 && MouseY >= 40 && MouseY <= 70) {
			Flag = 0;
		}
		if (MouseX >= 400 && MouseX <= 460 && MouseY >= 255 && MouseY < 285) {
			Flag = 1;
		}
		if (MouseX >= 400 && MouseX <= 460 && MouseY >= 285 && MouseY < 315) {
			Flag = 2;
		}
		if (MouseX >= 400 && MouseX <= 460 && MouseY >= 315 && MouseY < 345) {
			Flag = 3;
		}
		if (MouseX >= 400 && MouseX <= 460 && MouseY >= 345 && MouseY < 375) {
			Flag = 4;
		}
		if (MouseX >= 400 && MouseX <= 460 && MouseY >= 375 && MouseY < 405) {
			Flag = 5;
		}
		if (MouseX >= 400 && MouseX <= 460 && MouseY >= 405 && MouseY < 435) {
			Flag = 6;
		}
		if (MouseX >= 400 && MouseX <= 460 && MouseY >= 190 && MouseY <= 220) {
			Flag = 7;
		}
	}
	
	//�Z�^�C�v�ύX
	if (MouseX >= 105 && MouseX <= 165 && MouseY >= 255 && MouseY < 285) {
		Type[0]++;
		if (Type[0] == 5) {
			Type[0] = 0;
		}
	}
	if (MouseX >= 105 && MouseX <= 165 && MouseY >= 285 && MouseY < 315) {
		Type[1]++;
		if (Type[1] == 5) {
			Type[1] = 0;
		}
	}
	if (MouseX >= 105 && MouseX <= 165 && MouseY >= 315 && MouseY < 345) {
		Type[2]++;
		if (Type[2] == 5) {
			Type[2] = 0;
		}
	}
	if (MouseX >= 105 && MouseX <= 165 && MouseY >= 345 && MouseY < 375) {
		Type[3]++;
		if (Type[3] == 5) {
			Type[3] = 0;
		}
	}
	if (MouseX >= 105 && MouseX <= 165 && MouseY >= 375 && MouseY < 405) {
		Type[4]++;
		if (Type[4] == 5) {
			Type[4] = 0;
		}
	}
	if (MouseX >= 105 && MouseX <= 165 && MouseY >= 405 && MouseY < 435) {
		Type[5]++;
		if (Type[5] == 5) {
			Type[5] = 0;
		}
	}

	//�ۑ�
	if (MouseX >= 520 && MouseX <= 580 && MouseY >= 450 && MouseY <= 480) {
		if (Remain >= 0) {
			if (ReCreateID == -1) {
				SaveNewCard();
			}
			else {
				SaveCard();
			}
		}
		else {
			DrawBox(150, 250, 480, 400, Black, TRUE);
			DrawBox(153, 253, 477, 397, Cr, FALSE);
			DrawString(300, 255, "ERROR", Cr);
			DrawString(240, 330, "�|�C���g�I�[�o�[�ł�", Cr);
			DrawString(240, 370, "�L�[�������Ă�������", Cr);
			ScreenFlip();
			WaitKey();
		}
	}

	//HP�ύX
	if (MouseX >= 463 && MouseX <= 493 && MouseY >= 225 && MouseY < 255) {
		HP -= 10;
	}
	if (MouseX >= 530 && MouseX <= 560 && MouseY >= 225 && MouseY < 255) {
		HP += 10;
	}


	//�Z�З͕ύX
	if (MouseX >= 463 && MouseX <= 493 && MouseY >= 255 && MouseY < 285) {
		MovePower[0]-= 10;
	}
	if (MouseX >= 463 && MouseX <= 493 && MouseY >= 285 && MouseY < 315) {
		MovePower[1] -= 10;
	}
	if (MouseX >= 463 && MouseX <= 493 && MouseY >= 315 && MouseY < 345) {
		MovePower[2] -= 10;
	}
	if (MouseX >= 463 && MouseX <= 493 && MouseY >= 345 && MouseY < 375) {
		MovePower[3] -= 10;
	}
	if (MouseX >= 463 && MouseX <= 493 && MouseY >= 375 && MouseY < 405) {
		MovePower[4] -= 10;
	}
	if (MouseX >= 463 && MouseX <= 493 && MouseY >= 405 && MouseY < 435) {
		MovePower[5] -= 10;
	}
	for (int i = 0; i < 6; i++) {
		if (MovePower[i] < 0) {
			MovePower[i] = 0;
		}
	}


	if (MouseX >= 530 && MouseX <= 560 && MouseY >= 255 && MouseY < 285) {
		MovePower[0] += 10;
	}
	if (MouseX >= 530 && MouseX <= 560 && MouseY >= 285 && MouseY < 315) {
		MovePower[1] += 10;
	}
	if (MouseX >= 530 && MouseX <= 560 && MouseY >= 315 && MouseY < 345) {
		MovePower[2] += 10;
	}
	if (MouseX >= 530 && MouseX <= 560 && MouseY >= 345 && MouseY < 375) {
		MovePower[3] += 10;
	}
	if (MouseX >= 530 && MouseX <= 560 && MouseY >= 375 && MouseY < 405) {
		MovePower[4] += 10;
	}
	if (MouseX >= 530 && MouseX <= 560 && MouseY >= 405 && MouseY < 435) {
		MovePower[5] += 10;
	}
}

void Create::DrawButtons() {
	//���O�ύX�{�^��
	DrawGraph(400, 40, button, TRUE);
	DrawString(413, 48, "�ύX", Black);

	//�摜�ύX�{�^��
	DrawGraph(400, 190, button, TRUE);
	DrawString(413, 198, "�摜", Black);

	//�Z���ύX�{�^��
	for (int i = 0; i < 6; i++) {
		DrawGraph(400, 255 + 30 * i, button, TRUE);
		DrawString(413, 263 + 30 * i, "�ύX", Black);
	}

	//�Z�^�C�v�ύX�{�^��
	for (int i = 0; i < 6; i++) {
		DrawGraph(105, 255 + 30 * i, button, TRUE);
		switch (Type[i]) {
		case 0:
			DrawString(118, 263 + 30 * i, "�U��", Black);
			break;
		case 1:
			DrawString(118, 263 + 30 * i, "����", Black);
			break;
		case 2:
			DrawString(118, 263 + 30 * i, "�㉻", Black);
			break;
		case 3:
			DrawString(118, 263 + 30 * i, "��", Black);
			break;
		case 4:
			DrawString(118, 263 + 30 * i, "����", Black);
			break;
		}
	}

	//�c��|�C���g�\��
	DrawFormatString(475, 205, Cr, "�c��F%3d", Remain);


	//HP�ύX�{�^��
	DrawGraph(463, 225, DownButton, TRUE);
	DrawFormatString(498, 235, Cr, "%3d", HP);
	DrawGraph(530, 225, UpButton, TRUE);

	//�Z�З͕ύX�{�^��
	for (int i = 0; i < 6; i++) {
		DrawGraph(463, 255 + 30 * i, DownButton, TRUE);
		DrawFormatString(498, 265 + 30 * i, Cr, "%3d", MovePower[i]);
		DrawGraph(530, 255 + 30 * i, UpButton, TRUE);
	}


	//�ۑ��{�^��
	DrawGraph(520, 450, button, TRUE);
	DrawString(533, 458, "�ۑ�", Black);
}

void Create::ChangeName() {
	switch (Flag) {
	case 0:
		// ���O���͎w��������̕`��
		DrawString(0, 0, "���O����͂��Ă�������", GetColor(255, 255, 255));

		// ���O�̓���
		KeyInputString(0, 16, 30, Name, FALSE);

		// ��ʂ̏�����
		ClearDrawScreen();

		//Flag��߂�
		Flag = -1;
		break;

	case 1:
		DrawString(0, 0, "�Z������͂��Ă�������", GetColor(255, 255, 255));
		// ���O�̓���
		KeyInputString(0, 16, 30, Move[0], FALSE);

		// ��ʂ̏�����
		ClearDrawScreen();

		//Flag��߂�
		Flag = -1;
		break;

	case 2:
		DrawString(0, 0, "�Z������͂��Ă�������", GetColor(255, 255, 255));
		// ���O�̓���
		KeyInputString(0, 16, 30, Move[1], FALSE);

		// ��ʂ̏�����
		ClearDrawScreen();

		//Flag��߂�
		Flag = -1;
		break;

	case 3:
		DrawString(0, 0, "�Z������͂��Ă�������", GetColor(255, 255, 255));
		// ���O�̓���
		KeyInputString(0, 16, 30, Move[2], FALSE);

		// ��ʂ̏�����
		ClearDrawScreen();

		//Flag��߂�
		Flag = -1;
		break;

	case 4:
		DrawString(0, 0, "�Z������͂��Ă�������", GetColor(255, 255, 255));
		// ���O�̓���
		KeyInputString(0, 16, 30, Move[3], FALSE);

		// ��ʂ̏�����
		ClearDrawScreen();

		//Flag��߂�
		Flag = -1;
		break;

	case 5:
		DrawString(0, 0, "�Z������͂��Ă�������", GetColor(255, 255, 255));
		// ���O�̓���
		KeyInputString(0, 16, 30, Move[4], FALSE);

		// ��ʂ̏�����
		ClearDrawScreen();

		//Flag��߂�
		Flag = -1;
		break;

	case 6:
		DrawString(0, 0, "�Z������͂��Ă�������", GetColor(255, 255, 255));
		// ���O�̓���
		KeyInputString(0, 16, 30, Move[5], FALSE);

		// ��ʂ̏�����
		ClearDrawScreen();

		//Flag��߂�
		Flag = -1;
		break;
	case 7:
		DrawString(0, 0, "�摜�̃t�@�C��������͂��Ă�������", GetColor(255, 255, 255));
		// ���O�̓���
		KeyInputString(0, 16, 30, Pass, FALSE);

		std::string fullPath = "img/" + std::string(Pass);
		strncpy_s(Pass, fullPath.c_str(), sizeof(Pass) - 1);
		Pass[sizeof(Pass) - 1] = '\0';

		Image = LoadGraph(Pass);
		// ��ʂ̏�����

		ClearDrawScreen();

		//Flag��߂�
		Flag = -1;
		break;
	}
}