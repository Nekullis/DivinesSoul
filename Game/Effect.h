//----------------------------------------------------------------------
// @filename Effect.h
// @author: Fukuma Kyohei
// @explanation
// エフェクト管理クラス
// スキル発動時のエフェクトを管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include "EffekseerForDXLib.h"
#include <string>
#include <map>
class Effect
{
public:
	Effect(std::string handle, float size);
	virtual ~Effect();
	static Effect* efInstance;
	bool Play();
	bool Stop();
	bool Process();
	bool Draw();
	bool Debug();
	//何回も呼び出す必要のない関数なのでこの関数はマネージャーあるいはゲームメインに置くこと
	bool Update();
	//ゲッター
	bool GetUseFlag() { return useFlag; }
	bool GetPlayFlag() { return playFlag; }
	static Effect* GetInstance() { return efInstance; }
	//セッター
	void SetPos(VECTOR v) { Pos=v; }
	void SetSize(float s) { Size = s; }
	void SetDir(VECTOR v)  { Dir = v; }
	void SetUseFlag(bool f) { useFlag = f; }
protected:
	//エフェクトをロードする
	int effectResourceHandle;
	//再生用ハンドル
	int playEffectHandle;
	//位置
	VECTOR Pos;
	//サイズ
	float Size;
	//向き
	VECTOR Dir;
	//再生可能フラグ
	bool useFlag;
	//再生中のフラグ
	bool playFlag;
};

