//----------------------------------------------------------------------
// @filename EN_Crab.h
// @author: Fukuma Kyohei
// @explanation
// 敵派生クラス
// カブトガニ型の敵の処理クラス
//----------------------------------------------------------------------
#pragma once
#include "Enemy.h"
class EN_Crab : public Enemy
{
	using base = Enemy;
public:
	EN_Crab(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~EN_Crab();
	bool C_Process(VECTOR pl_pos);
	bool Process(VECTOR pl_pos) override;
	bool Render() override;
	bool Debug() override;
	bool Delete() override;
public:
	//当たり判定クラスに使うダメージ関数
	bool Damage(VECTOR pl_pos,int subpoint, int nextframe)override;
	bool Suction(VECTOR pl_pos, int nextframe)override;
	//ステータス変更
	void ChangeStatus(STATUS en_status)override;

protected:
	//crabのデータ
	ACTIONDATA _data;
	//行動のデータ
	STATUS _status;
};

