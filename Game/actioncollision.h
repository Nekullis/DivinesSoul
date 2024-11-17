#pragma once
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "EN_Osero.h"
#include "EN_Crab.h"
#include "divine.h"
#include "MathCollision.h"
#include <cmath>
#include <list>
class ActionCollision
{
public:
	ActionCollision();
	virtual ~ActionCollision();
	bool Process(Player* pl, EnemyManager* _enemy);
	//キャラとマップの押し出し
	bool MapColProcess(Player* pl, EnemyManager* _enemy);
	//各押し出し関数のまとめ
	bool ActionColProcess(Player* pl, EnemyManager* _enemy);
	//スキルを用いた判定の処理
	bool DivineColProcess(Player* pl, EnemyManager* _enemy);
	//描写
public:
	//マップ押し出し処理
	bool MapColPlayer(Player* pl);
	bool MapColEnemy(EnemyManager* _enemy);
	//playerとenemyの押し出し、攻撃判定処理
	bool PtoEColProcess(Player* pl, EnemyManager* _enemy);
	//enemy同士の押し出し処理
	bool EntoEnColProcess(EnemyManager* _enemy);
	//スキルの当たり判定の各関数
	bool DivineColCircle(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r);
	bool DivineColBreath(VECTOR p_pos, VECTOR p_fvec, VECTOR e_pos, float cos);
	bool DivineColLaser(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r);
	bool DivineColSlash(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r);
	bool DivineColExplosion(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r);
	bool DivineColDash(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r);
	bool DivineColVacuum(VECTOR p_pos, VECTOR p_fvec, VECTOR e_pos, float cos);
	bool DivineColSonic(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r);
	//デバッグ
	bool Debug(Player* pl);
protected:
	//スキルとカプセルの最短距離
	float _disDivinetoCap;
	int _stageModel;
};