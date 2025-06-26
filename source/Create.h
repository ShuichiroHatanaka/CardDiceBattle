#pragma once
#include "Util.h"
using namespace Util;

namespace Create {
	void CreateCard();
	extern int newCardID;
	extern Card* newCardList[30];
	void DrawNewCard();
	void SaveNewCard();
	void SaveCard();
	void Button();
	extern int Type[6];
	void DrawButtons();
	void ChangeName();
}