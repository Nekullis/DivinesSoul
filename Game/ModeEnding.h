//----------------------------------------------------------------------
// @filename ModeEnding.h
// @author: Fukuma Kyohei
// @explanation
// クリア後の映像を描画するクラス
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
class ModeEnding : public ModeBase
{
	using base = ModeBase;
public:
	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

protected:
	int _handleMovie;
};

