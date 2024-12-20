//----------------------------------------------------------------------
// @filename ModeLogo.h
// @author: Fukuma Kyohei
// @explanation
// ロゴ画像を描画するモード
//----------------------------------------------------------------------
#pragma once
#include "appFrame.h"
class ModeLogo : public ModeBase
{
	using base = ModeBase;
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;
protected:
	//ロゴハンドル
	int _cgLogo;
	//カウント
	int _modeCnt;

};

