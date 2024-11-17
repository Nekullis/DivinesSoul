//----------------------------------------------------------------------
// @filename ModeGameClear.h
// @author: Fukuma Kyohei
// @explanation
// クリア後の画像を描画するモード
//----------------------------------------------------------------------
#pragma once
class ModeClear : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

protected:
	//画像
	int _cg;
};

