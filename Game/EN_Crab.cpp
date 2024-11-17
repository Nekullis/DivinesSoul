#include "EN_Crab.h"
EN_Crab::EN_Crab(int model, int weapon, VECTOR vpos, VECTOR vdir) : base(model, weapon, vpos, vdir)
{
	//�����l��ݒ�
	MV1SetPosition(_model, _vPos);
	//�ړ���
	_vMove = VGet(0, 0, 0);
	//�̗�
	_hp = 60;
	//�U����
	_ap = 5;
	//����J�v�Z�����̗v�f��������
	//�J�v�Z���̔��a
	_radius = 43;
	//�����̒���
	_lineSeg = 170;
	//�J�v�Z���̈ʒu
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//�X�e�[�^�X��ҋ@��Ԃ�
	ChangeStatus(STATUS::WAIT);
	_type = ENEMYTYPE::CRAB;
}
EN_Crab::~EN_Crab()
{
	MV1DeleteModel(_model);
}

void EN_Crab::ChangeStatus(STATUS en_status)
{
	//�X�e�[�^�X�̑��
	_data.status = en_status;
	//�J�E���g���Z�b�g
	_actionCnt = 0;
	_timeCnt = 0;
	//�e��Ԃ̑����[�V�����t���[���ƒT���͈͂̑��
	switch (_data.status)
	{
	//�ҋ@
	case STATUS::WAIT:
		_data.motionTotalFrame = 0;
		_data._searchArea = 2000;
		break;
	//�U��
	case STATUS::ATTACK:
		_data.motionTotalFrame = 0;
		_data._searchArea = 100;
		break;
	//�x�e
	case STATUS::REST:
		_data.motionTotalFrame = 60;
		_data._searchArea = 100;
		break;
	//���S
	case STATUS::DIE:
		_data.motionTotalFrame = 60;
		_data._searchArea = 100;
		break;
	}
}

bool EN_Crab::C_Process(VECTOR pl_pos)
{
	//�J�E���g�̉��Z
	_actionCnt++;
	_timeCnt++;
	//�X�e�[�^�X���f�[�^���̕ύX���ꂽ�X�e�[�^�X��
	_status = _data.status;
	//�����蔻��J�v�Z���̈ʒu��ύX
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//���[�J���ϐ��̏�����
	VECTOR v = VGet(0, 0, 0);
	float len = 0;
	//�ړ����x
	float speed = 0;
	//��Ԃɂ���ď�����ύX�@
	switch (_status)
	{
		//�ҋ@
	case STATUS::WAIT:
		//�ړ����Ȃ����ߑ��x��0��
		speed = 0;
		//�v���C���[�ƓG�̈ʒu�̍������o��
		v = VSub(_vPos, pl_pos);
		//�x�N�g���̃T�C�Y���v�Z
		len = VSize(v);
		//�G����v���C���[�̋������T���͈͓�
		if (len * len <= _data._searchArea * _data._searchArea)
		{
			//�X�e�[�^�X���U����
			ChangeStatus(STATUS::ATTACK);
		}
		break;
		//�U��
	case STATUS::ATTACK:
		//�U�����Ȃ̂Ńt���O��true��
		_isAttack = true;
		//���[�J���ϐ�
		VECTOR vec_pl_pos = VGet(0, 0, 0);
		VECTOR vector = VGet(0, 0, 0);
		//�ړ����x��ݒ�
		speed = 2;
		//0.5�b�ɂP�񏈗�
		if (_timeCnt >= 30)
		{
			//���g�̈ʒu�ƃv���C���[�̃x�N�g�����쐬
			vec_pl_pos = VSub(_vPos, pl_pos);
			//�����x�N�g���ƃv���C���[�Ƃ̈ʒu�x�N�g���̍����x�N�g�����o���Ă���2���̃x�N�g�����o��
			vector = VScale(VSub(_vDir, vec_pl_pos), 0.2);
			//�����x�N�g���ƕ����x�N�g�����������邱�Ƃňړ������̃x�N�g�����ł���
			vector = VAdd(vector, _vDir);
			//�����x�N�g���̐��K�����A�����x�N�g����
			_vDir = VNorm(vector);
			//�J�E���g���Z�b�g
			_timeCnt = 0;
		}
		//�����x�N�g���ɃX�s�[�h�����������̂��ړ��x�N�g���Ƃ���
		_vMove = VScale(_vDir, speed);
		//�ʒu�x�N�g���Ɉړ��x�N�g�������Z
		_vPos = VAdd(_vPos, _vMove);
		break;
	case STATUS::REST:
		if (_actionCnt > _data.motionTotalFrame)
		{
			//�X�e�[�^�X���U����
			ChangeStatus(STATUS::ATTACK);
		}
		break;
	case STATUS::DAMAGE:
		//�J�E���g�����t���[���ɒB����
		if (_actionCnt >= _data.motionTotalFrame)
		{
			//�X�e�[�^�X�𑖍s��
			ChangeStatus(STATUS::RUN);
		}
		break;
	case STATUS::DIE:
		_isAttack = false;
		_die = true;
		Delete();
		break;
	}
	if (_noDamage) { _invincibleCnt++; }
	if (_invincibleCnt >= nextFrame)
	{
		_noDamage = false;
		_invincibleCnt = 0;
	}
	//���܂�Ȃ��悤�Ɉʒu�𒲐�
	if (_vPos.y <= 0 || _vPos.y >= 0)
	{
		_vPos.y = 0;
	}
	if (_die)
	{
		float rate = 1;
		_status = STATUS::DIE;
		for (rate; rate >= 0; rate -= 0.05)
		{
			MV1SetOpacityRate(_model, rate);
		}
		if (rate < 0)
		{
			Delete();
			_deleteFlag = true;
		}
	}
	else { _playTime = 0; }
	//���f���̈ʒu��ݒ�
	MV1SetPosition(_model, _vPos);
	//���f���̌�����ݒ�
	//�p�x�����߂�̂������W�n���Ⴄ�̂ŕύX
	float angle = atan2(-_vDir.x, -_vDir.z);
	MV1SetRotationXYZ(_model, VGet(0,angle,0));
	return true;
}
bool EN_Crab::Damage(VECTOR pl_pos, int subpoint, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal._sndServer.Get("SE_Damage_Crab");
	snditem_se->SetVolume(200);
	if (snditem_se && snditem_se->IsLoad())
	{// �Đ������H
		if (snditem_se->IsPlay() == false)
		{// �Đ�����
			snditem_se->Play();
		}
	}
	VECTOR v = VSub(_vPos, pl_pos);
	_hp = _hp - subpoint;
	if (_hp <= 0)
	{
		v = VScale(VNorm(v), 100);
		//�X�e�[�^�X�����S��
		ChangeStatus(STATUS::DIE);
	}
	else if (_hp > 0)
	{
		v = VScale(VNorm(v), 200);
	}
	_vPos = VAdd(_vPos, v);
	nextFrame = nextframe;
	return true;
}

bool EN_Crab::Suction(VECTOR pl_pos, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal._sndServer.Get("SE_Damage");
	if (snditem_se && snditem_se->IsLoad())
	{
		// �Đ������H
		if (snditem_se->IsPlay() == false)
		{
			// �Đ�����
			snditem_se->Play();
		}
	}
	VECTOR v = VSub(_vPos, pl_pos);
	v = VScale(VNorm(v), -5);
	_vPos = VAdd(_vPos, v);
	nextFrame = nextframe;
	_noDamage = true;
	return true;
}

bool EN_Crab::Process(VECTOR pl_pos)
{
	C_Process(pl_pos);
	return true;
}

bool EN_Crab::Render()
{
	MV1SetAttachAnimTime(_model, _attachIndex, _playTime);
	MV1DrawModel(_model);
	return true;
}

bool EN_Crab::Debug()
{
	base::Debug();
	return true;
}

bool EN_Crab::Delete()
{
	base::Delete();
	return true;
}






