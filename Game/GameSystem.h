//----------------------------------------------------------------------
// @filename GameSystem.h
// @author: Fukuma Kyohei
// @explanation
// ゲーム内共通システムクラス
// ガチャの回転のためのコンボ数などゲーム内での共通ギミック処理を行うクラス
//----------------------------------------------------------------------
#pragma once
#include "EnemyManager.h"
#include "SkillSlot.h"
constexpr auto CHANGE_SKILL_COMBO = 30;
class GameSystem
{
public:
	GameSystem();
	virtual ~GameSystem();
	//インスタンス
	static GameSystem* _sysInstance;
	bool Process(EnemyManager* en, SkillSlot* slot, int lasttrg);
	bool Render();
public:
	//撃破数に関するプロセス
	void KOProcess(EnemyManager* en, SkillSlot* slot, int lasttrg);
	void DrawKO();
	//ゲッター
	static GameSystem* GetInstance(){ return _sysInstance; }
protected:
	int _ko;
	bool _koSlot;
};

