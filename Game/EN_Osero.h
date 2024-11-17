#pragma once
#include "Enemy.h"
#include"cmath"
class EN_Osero : public Enemy
{
	using base = Enemy;
public:
	EN_Osero(int model,int weapon,VECTOR vpos, VECTOR vdir);
	virtual ~EN_Osero();
	//アニメーションプロセス
	bool A_Process();
	//計算系プロセス
	bool C_Process(VECTOR pl_pos);
	bool Process(VECTOR pl_pos) override;
	bool Render() override;
	bool Debug() override;
	bool Delete() override;
public:
	void WaitProcess(VECTOR pl_pos);
	void RunProcess(VECTOR pl_pos);
	void CautionProcess(VECTOR pl_pos);
	void AttackProcess();
	void DamageProcess();
	void DieProcess();
	
	void SetWeapon();
	void Move(float speed, VECTOR pl_pos);
	void Invincible(int nextframe);
	VECTOR AttackPos();
	//当たり判定クラスに使うダメージ関数
	bool Damage(VECTOR pl_pos, int subpoint, int nextframe)override;
	bool Suction(VECTOR pl_pos, int nextframe)override;
	//ステータス変更
	void ChangeStatus(STATUS en_status)override;
protected:
	//oseroの状態
	STATUS _status;
	STATUS _oldStatus;
	//行動のデータ
	ACTIONDATA _data;
	
};

