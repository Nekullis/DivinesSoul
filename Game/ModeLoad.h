//----------------------------------------------------------------------
// @filename ModeLoad.h
// @author: Fukuma Kyohei
// @explanation
// ロード画面を描画するモード
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
class ModeLoad : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;
protected:
	int _changePage;
};

