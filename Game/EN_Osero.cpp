#include "EN_Osero.h"
EN_Osero::EN_Osero(int model, int weapon, VECTOR vpos, VECTOR vdir) : base(model, weapon, vpos, vdir)
{
	//�����l��ݒ�
	MV1SetPosition(_model, _vPos);
	//�̗�
	_hp = 80;
	//�U����
	_ap = 8;
	//����ł��邩
	_die = false;
	//�J�v�Z���̔��a
	_radius = 35;
	//�����̒���
	_lineSeg = 191;
	//�J�v�Z���̈ʒu
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//�A�^�b�`����A�j���[�V�����ԍ��̏�����
	_attachIndex = MV1AttachAnim(_model, 6, -1, FALSE);
	//���Đ����Ԃ̏�����
	_totalTime = gGlobal._RS->mGetAttach()["osero_stand"]._attach_time;
	//����T�C�Y
	_wSize = 50;
	//�X�e�[�^�X��ҋ@��Ԃ�
	ChangeStatus(STATUS::WAIT);
	_type = ENEMYTYPE::OSERO;
}
EN_Osero::~EN_Osero()
{
	MV1DeleteModel(_model);
	MV1DetachAnim(_model, _attachIndex);
}
void EN_Osero::ChangeStatus(STATUS en_status)
{
	_actionCnt = 0;
	_timeCnt = 0;
	//�X�e�[�^�X�̑��
	_status = en_status;
	//�e��Ԃ̑����[�V�����t���[���ƒT���͈͂̑��
	switch (_status)
	{
	//�ҋ@
	case WAIT:
		_data.motionTotalFrame = 0;
		_data._searchArea = 1000;
		break;
	//�_���[�W
	case DAMAGE:
		_data.motionTotalFrame = 42;
		_data._searchArea = 0;
		break;
	//�x��
	case CAUTION:
		_data.motionTotalFrame = 0;
		_data._searchArea = 0;
		break;
	//�U��
	case ATTACK:
		_data.motionTotalFrame = 38;
		_data._searchArea = 200;
		break;
	//���s
	case RUN:
		_data.motionTotalFrame = 31;
		_data._searchArea = 200;
		break;
	}
}



bool EN_Osero::A_Process()
{
	//std::string mName;
	std::string name[2] =
	{
		"osero_walk_left",
		"osero_walk_right",
	};
	//1�t���[���O�̃X�e�[�^�X�ƈႤ�̂Ȃ珈��
	if (_oldStatus != _status)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(_model, _attachIndex);
		//�X�e�[�^�X�ɂ���ăA�^�b�`����A�j���[�V�����̕ύX
		switch (_status)
		{
		//�ҋ@
		case STATUS::WAIT:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_stand";
			_attachIndex = MV1AttachAnim(_model,gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�_���[�W
		case STATUS::DAMAGE:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_damage";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�x��
		case STATUS::CAUTION:
			//�L�[����v�����邽�߂ɕ��������
			mName = name[rand() % 2];
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�U��
		case STATUS::ATTACK:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_attack1";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//���s
		case STATUS::RUN:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_run";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
			//���s
		case STATUS::DIE:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_die";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = gGlobal._RS->mGetAttach()[mName]._attach_time;
		_playTime = 0.0f;
	}
	
	// �Đ����Ԃ�i�߂�
	_playTime += 1.0f;
	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (_playTime >= _totalTime)
	{
		if (_die)
		{
			_playTime = _totalTime;
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
		//_playTime = 0;
	}
	//�ꎞ�I�ȃX�e�[�^�X�̕ύX
	_oldStatus = _status;
	return true;
}
void EN_Osero::WaitProcess(VECTOR pl_pos)
{
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(_vPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	//�G����v���C���[�̋������T���͈͓�
	if (len * len <= _data._searchArea * _data._searchArea)
	{
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::RUN);
	}
}


void EN_Osero::Move(float speed, VECTOR pl_pos)
{
	//���[�J���ϐ���ݒ�
	VECTOR vec_pl_pos = VGet(0, 0, 0);
	VECTOR vector = VGet(0, 0, 0);
	//���g�̈ʒu�ƃv���C���[�̃x�N�g�����쐬
	vec_pl_pos = VSub(pl_pos, _vPos);
	//�x�N�g���𐳋K��
	VECTOR vunit = VNorm(vec_pl_pos);
	//���K�������x�N�g����
	vector = vunit;
	//������ݒ肷�邽�߂ɑ��
	_vDir = vec_pl_pos;
	//�����x�N�g���ɃX�s�[�h�����������̂��ړ��x�N�g���Ƃ���
	_vMove = VScale(vector, speed);
	//�ʒu�x�N�g���Ɉړ��x�N�g�������Z
	_vPos = VAdd(_vPos, _vMove);
}

void EN_Osero::RunProcess(VECTOR pl_pos)
{
	float speed = 10;
	Move(speed, pl_pos);
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(_vPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	//�G����v���C���[�̋������T���͈͓�
	if (len * len <= _data._searchArea * _data._searchArea)
	{
		//�X�e�[�^�X���x����
		ChangeStatus(STATUS::CAUTION);
	}
	if (len >= 2100)
	{
		//�X�e�[�^�X��ҋ@��
		ChangeStatus(STATUS::WAIT);
	}

}
void EN_Osero::CautionProcess(VECTOR pl_pos)
{
	_actionCnt++;
	float attack_frame = 70 * (rand() % 1 + 1);
	if (mName == "osero_walk_left")
	{
		_vPos.x += 0.1;
	}
	if (mName == "osero_walk_right")
	{
		_vPos.x -= 0.1;
	}
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(pl_pos, _vPos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	//�v���C���[�ƓG�̔���J�v�Z����
	float add_radius = _data._searchArea + 30;
	MATRIX m = MGetRotY(_vDir.y);
	VECTOR vec = VGet(m.m[2][0], m.m[2][1], m.m[2][2]);
	vec = VScale(vec, -1);
	//�v���C���[���G�̍��G�͈͂ɓ�����
	if (MathCollision::CollisionPointAndFan(vec, v, 50))
	{
		//�J�E���g���U���܂ł̃t���[���ɒB����
		if (_actionCnt >= attack_frame)
		{
			//�X�e�[�^�X���U����
			ChangeStatus(STATUS::ATTACK);
		}
	}
	if (len >= 300)
	{
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::RUN);
	}
}
void EN_Osero::AttackProcess()
{
	_actionCnt++;
	//�U�����Ȃ̂Ńt���O��true��
	_isAttack = true;
	//�J�E���g�������[�V�����t���[���ɒB����
	if (_actionCnt >= _data.motionTotalFrame)
	{
		//�U�����I������̂Ńt���O��false��
		_isAttack = false;
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::RUN);
	}
}

void EN_Osero::DamageProcess()
{
	_actionCnt++;
	//�J�E���g�����t���[���ɒB����
	if (_actionCnt >= _data.motionTotalFrame)
	{
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::RUN);
	}
}

void EN_Osero::DieProcess()
{
	_die = true;
	_isAttack = false;
}
void EN_Osero::SetWeapon()
{
	//�v���C���[�̃��f�����畐��𑕔�����t���[����T��
	int frame_index = MV1SearchFrame(_model, "joint_sword");
	//�ʒu�����[�J������O���[�o���ɕϊ�����}�g���b�N�X���쐬
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(_model, frame_index);
	_wPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	_wPos[1] = VTransform(VGet(0, 100, 0), weapon_matrix);
	//����̈ʒu����̃t���[���ɐݒ�
	MV1SetMatrix(_wModel, weapon_matrix);
}

void EN_Osero::Invincible(int nextframe)
{
	//���G���Ԓ��̂݃J�E���g�𑝂₷
	if (_noDamage) { _invincibleCnt++; }
	if (_invincibleCnt >= nextFrame)
	{
		_noDamage = false;
		_invincibleCnt = 0;
	}
}
VECTOR EN_Osero::AttackPos()
{
	return VECTOR();
}
bool EN_Osero::C_Process(VECTOR pl_pos)
{
	
	//�J�E���g�̉��Z
	_timeCnt++;
	//�����蔻��J�v�Z���̈ʒu��ύX
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//��Ԃɂ���ď�����ύX
	switch (_status)
	{
	//�ҋ@
	case STATUS::WAIT:
		WaitProcess(pl_pos);
		break;
	//���s
	case STATUS::RUN:
		RunProcess(pl_pos);
		break;
	//�_���[�W
	case STATUS::DAMAGE:
		DamageProcess();
		break;
	//�x��
	case STATUS::CAUTION:
		CautionProcess(pl_pos);
		break;
	//�U��
	case STATUS::ATTACK:
		AttackProcess();
		break;
	//���S
	case STATUS::DIE:
		DieProcess();
		break;
	}
	//���܂�Ȃ��悤�Ɉʒu�𒲐�
	_vPos.y -= 10;
	if (_vPos.y <= 0)
	{
		_vPos.y = 0;
	}
	//���G���Ԓ��̂݃J�E���g�𑝂₷
	Invincible(nextFrame);
	SetWeapon();
	//���f���̈ʒu��ݒ�
	MV1SetPosition(_model, _vPos);
	//�p�x�����߂�̂������W�n���Ⴄ�̂ŕύX
	float angle = atan2(-_vDir.x, -_vDir.z);
	//���f���̌�����ݒ�
	MV1SetRotationXYZ(_model, VGet(0,angle,0));
	return true;
}
bool EN_Osero::Process(VECTOR pl_pos)
{
	A_Process();
	C_Process(pl_pos);
	return true;
}
bool EN_Osero::Damage(VECTOR pl_pos,int subpoint, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal._sndServer.Get("SE_Damage");
	snditem_se->SetVolume(200);
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
	_hp = _hp - subpoint;
	if (_hp <= 0)
	{
		v = VScale(VNorm(v), 100);
		//�X�e�[�^�X�����S��
		ChangeStatus(STATUS::DIE);
	}
	else if (_hp > 0)
	{
		v = VScale(VNorm(v), 85);
		ChangeStatus(STATUS::DAMAGE);
	}
	_vPos = VAdd(_vPos, v);
	_isAttack = false;
	nextFrame = nextframe;
	_noDamage = true;
	return true;
}

bool EN_Osero::Suction(VECTOR pl_pos, int nextframe)
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
	ChangeStatus(STATUS::DAMAGE);
	VECTOR v = VSub(_vPos, pl_pos);
	v = VScale(VNorm(v), -5);
	_vPos = VAdd(_vPos, v);
	nextFrame = nextframe;
	_noDamage = true;
	return true;
}

bool EN_Osero::Render()
{
	MV1SetAttachAnimTime(_model, _attachIndex, _playTime);
	MV1SetRotationXYZ(_wModel, VGet(0, 0.5, 0));
	MV1DrawModel(_model);
	MV1DrawModel(_wModel);
	return true;
}
bool EN_Osero::Debug()
{
	base::Debug();
	DrawFormatString(0, 200, GetColor(255, 255, 255), "cnt=%d", _actionCnt);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "time=%d", _playTime);
	return true;
}
bool EN_Osero::Delete()
{
	base::Delete();
	return true;
}
