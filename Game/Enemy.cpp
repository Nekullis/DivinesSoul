#include "enemy.h"
Enemy::Enemy(int model, int weapon,VECTOR vpos, VECTOR vdir)
{
	_model = MV1DuplicateModel(model);
	_wModel = MV1DuplicateModel(weapon);
	//�����l��ݒ�
	_vPos = vpos;
	_vDir = vdir;
	_vMove = VGet(0, 0, 0);
	MV1SetPosition(_model, _vPos);
	MV1SetRotationXYZ(_model, _vDir);
	//����J�v�Z�����̗v�f��������
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, 150, 0));
	_radius = 0;
	_lineSeg = 0;
	_wPos[0] = VGet(0, 0, 0);
	_wPos[1] = VGet(0, 0, 0);
	_wSize = 0;
	//�̗�
	_hp = 0;
	_ap = 0;
	_die = false;
	_deleteFlag = false;
	//�J�E���g������
	_actionCnt = 0;
	_invincibleCnt = 0;
	nextFrame = 1;
	_timeCnt = 0;
	//�U�����ł͂Ȃ��̂�false��
	_isAttack = false;
	//�_���[�W���󂯂Ă��Ȃ��̂�
	_damage = false;
	_noDamage = false;
	//�Đ����Ԃ̏�����
	_playTime = 0.0f;
	//���Đ����Ԃ̏�����
	_totalTime = 0;
	//�A�^�b�`����A�j���[�V�����ԍ��̏�����
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
