#include "ModeLogo.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModeFade.h"
bool ModeLogo::Initialize()
{
	if (!base::Initialize()) { return false; }
	_cgLogo = LoadGraph("res/Graph/Logo.png");
	ModeServer::GetInstance()->Add(new ModeFade(1), 100, "fade");
	_modeCnt = 0;
	return true;
}

bool ModeLogo::Terminate()
{
	base::Terminate();
	return true;
}

bool ModeLogo::Process()
{
	base::Process();
	_modeCnt++;
	if (gGlobal._gTrg & PAD_INPUT_3)
	{
		_modeCnt = 300;
	}
	if (gGlobal._isLoad && _modeCnt >= 300)
	{
		// ‚±‚Ìƒ‚[ƒh‚ðíœ—\–ñ
		ModeServer::GetInstance()->Del(this);
		// ŽŸ‚Ìƒ‚[ƒh‚ð“o˜^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}
	return true;
}

bool ModeLogo::Render()
{
	base::Render();
	DrawGraph(0, 0, _cgLogo, TRUE);
	return true;
}
