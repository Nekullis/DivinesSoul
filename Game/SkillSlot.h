//----------------------------------------------------------------------
// @filename SkillSlot.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// スキルスロット
// 使用できるスキルを変更させるためのクラス
//----------------------------------------------------------------------
#pragma once
#include "AppFrame.h"
#include "ResourceServer.h"
#include "JsonUtility.h"
#include "EnumInfo.h"
#include  <map>

constexpr float _to_nextdiv = 10000.0f;
//追加
constexpr auto MAX_VOICE = 8;

class SkillSlot{
public:
	//追加
	struct CALLVOICE
	{
		int callCnt;
		int maxCallCnt;
		bool isCall;
		std::string voiceCode;
	};
public:

	SkillSlot();
	virtual ~SkillSlot();
	void divineToNext(int slotnum);
	void divineToPrevious(int slotnum);
	//ボイス登録
	void RegisterCall();
	//ボイス出力
	void SlotVoice(int i);
	//ボイス再生関連処理
	void CallProcess();
	//スロット回転処理
	void SlotSpin(int slotnum);
	//スロット関連処理まとめ
	void Process();
	//スロット描画
	void Render();

	std::array<kindDivine, 3> Getslot() { return _slot; }

	bool GetSpin() { return _isSpin; }

protected:

	int _slotdivine;

	int _spinspeed;

	int _reeltime;

	int _voiceNum;

	bool _isSpin;

	CALLVOICE _call[MAX_VOICE];

	std::array<kindDivine, 3> _slot;

};