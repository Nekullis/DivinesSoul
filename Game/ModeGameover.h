//----------------------------------------------------------------------
// @filename ModeGameOver.h
// @author: Fukuma Kyohei
// @explanation
// プレイヤー死亡後の画像を描画するモード
//----------------------------------------------------------------------
#pragma once
#include"ModeTitle.h"
class ModeGameover : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

protected:
	//画像
	int _cg[2];
	//選択番号
	int _selection;

};

