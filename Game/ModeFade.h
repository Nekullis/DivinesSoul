//----------------------------------------------------------------------
// @filename ModeFade.h
// @author: Fukuma Kyohei
// @explanation
// クリア後の映像を描画するクラス
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
class ModeFade :public ModeBase
{
	using base = ModeBase;
public:
	//true:fadein,false:fadeout
	ModeFade(bool fade);
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;
protected:
	//開始数値
	int _alphaStart;
	//終了数値
	int _alphaEnd;
	//時間(ミリ秒単位)
	int _nowTime;
	//フェード数値
	int _alphaFade;
	//フェードインかフェードアウトか
	bool _isFade;
};

