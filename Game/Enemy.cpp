#include "enemy.h"
Enemy::Enemy(int model, int weapon,VECTOR vpos, VECTOR vdir)
{
	_model = MV1DuplicateModel(model);
	_wModel = MV1DuplicateModel(weapon);
	//初期値を設定
	_vPos = vpos;
	_vDir = vdir;
	_vMove = VGet(0, 0, 0);
	MV1SetPosition(_model, _vPos);
	MV1SetRotationXYZ(_model, _vDir);
	//判定カプセル内の要素を初期化
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, 150, 0));
	_radius = 0;
	_lineSeg = 0;
	_wPos[0] = VGet(0, 0, 0);
	_wPos[1] = VGet(0, 0, 0);
	_wSize = 0;
	//体力
	_hp = 0;
	_ap = 0;
	_die = false;
	_deleteFlag = false;
	//カウント初期化
	_actionCnt = 0;
	_invincibleCnt = 0;
	nextFrame = 1;
	_timeCnt = 0;
	//攻撃中ではないのでfalseに
	_isAttack = false;
	//ダメージを受けていないので
	_damage = false;
	_noDamage = false;
	//再生時間の初期化
	_playTime = 0.0f;
	//総再生時間の初期化
	_totalTime = 0;
	//アタッチするアニメーション番号の初期化
	_attachIndex = -1;
	_type = ENEMYTYPE::NOCHARA;
}
Enemy::~Enemy()
{
	MV1DeleteModel(_model);
}

bool Enemy::Process(VECTOR pl_pos)
{
	return true;
}
bool Enemy::Render()
{
	return true;
}
bool Enemy::Debug()
{
	return true;
}
bool Enemy::Delete()
{
	MV1DeleteModel(_model);
	return true;
}

bool Enemy::Damage(VECTOR pl_pos, int subpoint,int nextframe)
{
	
	return true;
}

bool Enemy::Suction(VECTOR pl_pos, int nextframe)
{
	return true;
}

void Enemy::ChangeStatus(STATUS en_status)
{

}
