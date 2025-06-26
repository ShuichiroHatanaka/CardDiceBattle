#include "TItle.h"
using namespace Util;

namespace Title {
}

void Title::title() {
	DrawExtendGraph(70, 30, 570, 430, TitleLogo, TRUE);
	if (elapsedTime % 2000 <= 1000&&MenuFlag==0) {
		DrawString(240, 440, "-PRESS X TO START-", Cr);
	}
}