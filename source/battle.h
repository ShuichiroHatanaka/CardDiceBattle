#pragma once
#include "Util.h"

namespace Battle {

	extern int Rand_Result[2];

	extern int AtkPhase;

	void battle();
	void Roulette();
	void ResetRoulette();
	void JudgeFirst();
	void ChangeAtk();
	void Attack();
	void FinishGame();
	void DrawBattleCard(int, int, int, int);
	void DrawBattleLog();
	void DrawJudge();

	//デバッグ用
	void Attack_Q();
}