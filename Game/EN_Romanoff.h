//----------------------------------------------------------------------
// @filename EN_Romanoff.h
// @author: Fukuma Kyohei
// @explanation
// 敵派生クラス
// ボス敵の処理クラス
//----------------------------------------------------------------------
#pragma once
#include "Enemy.h"
class EN_Romanoff :public Enemy
{
	using base = Enemy;
public:
	enum class ANIMATION :int
	{
		WAIT,
		RUN,
		FIRSTATTACK,
		SECONDATTACK,
		SKILL,
		DAMAGE,
		DIE
	};
public:
	EN_Romanoff(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~EN_Romanoff();
	static EN_Romanoff* _bossInstance;
	bool Process(VECTOR pl_pos) override;
	bool Render() override;
	bool Debug() override;
	bool Delete() override;
public:
	//アニメーションプロセス
	bool A_Process();
	//計算系プロセス
	bool C_Process(VECTOR pl_pos);
	void DiscoveryProcess(VECTOR pl_pos);
	void WaitProcess();
	void AttackProcess();
	void AssaultProcess(VECTOR pl_pos);
	void DamageProcess();
	void DieProcess();
	void RunProcess(VECTOR pl_pos);
	void SetWeapon();
	void Move(float speed,VECTOR pl_pos);
	void Invincible(int nextframe);
	VECTOR AttackPos();
	bool Attack();
	bool Assult();
	//当たり判定クラスに使うダメージ関数
	bool Damage(VECTOR pl_pos, int subpoint, int nextframe)override;
	bool Suction(VECTOR pl_pos, int nextframe)override;
	//ステータス変更
	void ChangeStatus(STATUS en_status)override;
	//ゲッター
	static EN_Romanoff* GetInstance() { return _bossInstance; }
protected:
	//romanoffの状態
	STATUS _status;
	//行動のデータ
	ACTIONDATA _data;
	ANIMATION  _animation;
	ANIMATION  _oldAnimation;
	int _damageCnt;
};

