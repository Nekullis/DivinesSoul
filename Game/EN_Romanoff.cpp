#include "EN_Romanoff.h"
#include "GameEvent.h"
EN_Romanoff* EN_Romanoff::_bossInstance = nullptr;
EN_Romanoff::EN_Romanoff(int model, int weapon, VECTOR vpos, VECTOR vdir) :base(model, weapon, vpos, vdir)
{
	_bossInstance = this;
	//�����l��ݒ�
	MV1SetPosition(_model, _vPos);
	//�̗�
	_hp = 4000;
	//�U����
	_ap = 10;
	//����ł��邩
	_die = false;
	//����J�v�Z�����̗v�f��������
	//�J�v�Z���̔��a
	_radius = 45;
	//�����̒���
	_lineSeg = 191;
	//�J�v�Z���̈ʒu
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//�A�^�b�`����A�j���[�V�����ԍ��̏�����
	_attachIndex = MV1AttachAnim(_model, 6, -1, FALSE);
	mName = "romanoff_stand";
	//���Đ����Ԃ̏�����
	_totalTime = gGlobal._RS->mGetAttach()[mName]._attach_time;
	//����T�C�Y
	_wSize = 50;
	_damageCnt = 5;
	//�X�e�[�^�X�𖢔�����
	ChangeStatus(STATUS::NODISCOVERY);
	_type = ENEMYTYPE::ROMANOFF;
}

EN_Romanoff::~EN_Romanoff()
{
	MV1DeleteModel(_model);
	MV1DetachAnim(_model, _attachIndex);
}

void EN_Romanoff::ChangeStatus(STATUS en_status)
{
	//�X�e�[�^�X�̑��
	_data.status = en_status;
	//�J�E���g���Z�b�g
	_actionCnt = 0;
	_timeCnt = 0;
	switch (_data.status)
	{
	case STATUS::DAMAGE:
		_data.motionTotalFrame = 42;
	}
}

bool EN_Romanoff::A_Process()
{
	//1�t���[���O�̃X�e�[�^�X�ƈႤ�̂Ȃ珈��
	if (_oldAnimation != _animation)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(_model, _attachIndex);
		//�X�e�[�^�X�ɂ���ăA�^�b�`����A�j���[�V�����̕ύX
		switch (_animation)
		{
		//�ҋ@
		case ANIMATION::WAIT:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_stand";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�_���[�W
		case ANIMATION::DAMAGE:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_damage";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�U��
		case ANIMATION::FIRSTATTACK:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_attack1";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::SECONDATTACK:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_attack2";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//���s
		case ANIMATION::RUN:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_run";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//���s
		case ANIMATION::DIE:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_die";
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
	}
	//�ꎞ�I�ȃX�e�[�^�X�̕ύX
	_oldAnimation = _animation;
	return true;
}

void EN_Romanoff::DiscoveryProcess(VECTOR pl_pos)
{
	float dis_discovery = 2000.0f;
	_animation = ANIMATION::WAIT;
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(_vPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	if (len <= dis_discovery)
	{
		ChangeStatus(STATUS::WAIT);
		GameEvent::GetInstance()->SetEvent(1);
	}

}

void EN_Romanoff::WaitProcess()
{
	int action_num = rand() % 10;
	_animation = ANIMATION::WAIT;
	_actionCnt++;
	if (_actionCnt >= 110)
	{
		if (action_num < 7)
		{
			//�X�e�[�^�X�𑖍s��
			ChangeStatus(STATUS::RUN);
		}
		else if (action_num >= 7)
		{
			//�X�e�[�^�X��ˌ���
			ChangeStatus(STATUS::ASSAULT);
		}
		
	}
}

void EN_Romanoff::Move(float speed, VECTOR pl_pos)
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

void EN_Romanoff::RunProcess(VECTOR pl_pos)
{
	//�A�j���[�V�����𑖍s��
	_animation = ANIMATION::RUN;
	//�X�s�[�h��ݒ�
	float speed = 8.5;
	//�J�E���g���Z
	_actionCnt++;
	//�ړ�����
	Move(speed, pl_pos);
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(_vPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	//�J�E���g���K�萔�A�������̓x�N�g���T�C�Y���K��ȓ�
	if (len <= 100)
	{
		//�X�e�[�^�X���U���ɕύX
		ChangeStatus(STATUS::ATTACK);
	}
	else if (_actionCnt >= 360 && len >= 100)
	{
		//�X�e�[�^�X���U���ɕύX
		ChangeStatus(STATUS::ASSAULT);
	}

}

VECTOR EN_Romanoff::AttackPos()
{
	VECTOR vec = { 0 };
	int frame_index = MV1SearchFrame(_model, "Character1_Hips");
	//�ʒu�����[�J������O���[�o���ɕϊ�����}�g���b�N�X���쐬
	MATRIX matrix = MV1GetFrameLocalWorldMatrix(_model, frame_index);
	vec = VTransform(VGet(0, 0, 0), matrix);
	return VGet(vec.x, 0, vec.z);
}

bool EN_Romanoff::Attack()
{
	if (_actionCnt >= 25 && _actionCnt <= 35 ||
		_actionCnt >= 45 && _actionCnt <= 70)
	{
		return true;
	}
	return false;
}

void EN_Romanoff::AttackProcess()
{
	_actionCnt++;
	std::string se_voice = "VO_Ro_Attack";
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(se_voice);
	if (Attack())
	{
		//_vPos = AttackPos();
		_isAttack = true;
	}
	else
	{
		_isAttack = false;
	}
	if (_actionCnt >= 0 && _actionCnt < 40)
	{
		_animation = ANIMATION::FIRSTATTACK;
		if (snditem_voice && snditem_voice->IsLoad())
		{
			// �Đ������H
			if (snditem_voice->IsPlay() == false)
			{
				// �Đ�����
				snditem_voice->Play();
			}
		}
	}
	else if (_actionCnt >= 40 && _actionCnt < 112)
	{
		_animation = ANIMATION::SECONDATTACK;
	}
	else if (_actionCnt == 112)
	{
		ChangeStatus(STATUS::WAIT);
	}
}

bool EN_Romanoff::Assult()
{
	if (_actionCnt >= 85 && _actionCnt <= 95)
	{
		return true;
	}
	return false;
}

void EN_Romanoff::AssaultProcess(VECTOR pl_pos)
{
	//�X�s�[�h��ݒ�
	float speed = 30.0;
	float finish_frame = 125;
	float assult_start_frame = 40;
	float dis_assult = 100;
	std::string voice[3] =
	{
		"VO_Ro_Divine1",
		"VO_Ro_DIvine2",
		"VO_Ro_DIvine3"
	};
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(voice[rand() % 3]);
	//�J�E���g���Z
	_actionCnt++;
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(_vPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	if (_actionCnt == 1)
	{
		snditem_voice->Play();
	}
	if (_actionCnt < assult_start_frame)
	{
		//�A�j���[�V�����𑖍s��
		Move(speed, pl_pos);
		_animation = ANIMATION::RUN;
	}
	else if (_actionCnt == assult_start_frame)
	{
		_animation = ANIMATION::FIRSTATTACK;
	}
	else if (_actionCnt == finish_frame)
	{
		ChangeStatus(STATUS::WAIT);
	}
	
	if (Assult())
	{
		//_vPos = AttackPos();
		_isAttack = true;
	}
	if (_actionCnt < 85 || _actionCnt > 95)
	{
		_isAttack = false;
	}

}


void EN_Romanoff::DieProcess()
{
	std::string se_voice = "VO_Ro_Blow";
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(se_voice);
	_animation = ANIMATION::DIE;
	if (snditem_voice && snditem_voice->IsLoad())
	{
		// �Đ������H
		if (snditem_voice->IsPlay() == false)
		{
			// �Đ�����
			snditem_voice->Play();
		}
	}
	_die = true;
}

void EN_Romanoff::DamageProcess()
{
	_actionCnt++;
	_animation = ANIMATION::DAMAGE;
	//�J�E���g�����t���[���ɒB����
	if (_actionCnt >= _data.motionTotalFrame)
	{
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::WAIT);
	}

}

bool EN_Romanoff::Damage(VECTOR pl_pos, int subpoint, int nextframe)
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
	_damageCnt--;
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
		v = VScale(VNorm(v), 50);
		//�X�e�[�^�X���_���[�W��
		if (_damageCnt <= 0)
		{
			ChangeStatus(STATUS::DAMAGE);
			_damageCnt = 5;
		}
	}
	_vPos = VAdd(_vPos, v);
	nextFrame = nextframe;
	_noDamage = true;
	return true;
}

bool EN_Romanoff::Suction(VECTOR pl_pos, int nextframe)
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

void EN_Romanoff::SetWeapon()
{
	//�v���C���[�̃��f�����畐��𑕔�����t���[����T��
	int frame_index = MV1SearchFrame(_model, "joint_axe");
	//�ʒu�����[�J������O���[�o���ɕϊ�����}�g���b�N�X���쐬
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(_model, frame_index);
	MATRIX weapon_dir_matrix = MGetRotY(1.75);
	weapon_matrix = MMult(weapon_dir_matrix,weapon_matrix);
	//����ʒu�̐ݒ�
	_wPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	_wPos[1] = VTransform(VGet(0, 150, 0), weapon_matrix);
	//����̈ʒu����̃t���[���ɐݒ�
	MV1SetMatrix(_wModel, weapon_matrix);
}

void EN_Romanoff::Invincible(int nextframe)
{
	//���G���Ԓ��̂݃J�E���g�𑝂₷
	if (_noDamage) { _invincibleCnt++; }
	//�J�E���g���K�萔�ɒB����
	if (_invincibleCnt >= nextframe)
	{
		//���G�t���O��false��
		_noDamage = false;
		//�J�E���g���Z�b�g
		_invincibleCnt = 0;
	}
}

bool EN_Romanoff::C_Process(VECTOR pl_pos)
{
	_status = _data.status;
	//�J�E���g�̉��Z
	_timeCnt++;
	//�����蔻��J�v�Z���̈ʒu��ύX
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//��Ԃɂ���ď�����ύX
	switch (_status)
	{
	case STATUS::NODISCOVERY:
		DiscoveryProcess(pl_pos);
		break;
	//�ҋ@
	case STATUS::WAIT:
		WaitProcess();
		break;
	//���s
	case STATUS::RUN:
		RunProcess(pl_pos);
		break;
	//�_���[�W
	case STATUS::DAMAGE:
		DamageProcess();
		break;
	//�U��
	case STATUS::ATTACK:
		AttackProcess();
		break;
	//�ˌ�
	case STATUS::ASSAULT:
		AssaultProcess(pl_pos);
		break;
	//���S
	case STATUS::DIE:
		DieProcess();
		break;
	}
	//���܂�Ȃ��悤�Ɉʒu�𒲐�
	if (_vPos.y <= 0|| _vPos.y >= 0)
	{
		_vPos.y = 0;
	}
	Invincible(nextFrame);
	SetWeapon();
	//�p�x�����߂�̂������W�n���Ⴄ�̂ŕύX
	float angle = atan2(-_vDir.x, -_vDir.z);
	//���f���̌�����ݒ�
	MV1SetRotationXYZ(_model, VGet(0, angle, 0));
	MV1SetPosition(_model, _vPos);
	return true;
}

bool EN_Romanoff::Process(VECTOR pl_pos)
{
	C_Process(pl_pos);
	A_Process();
	return true;
}

bool EN_Romanoff::Render()
{
	MV1SetAttachAnimTime(_model, _attachIndex, _playTime);
	MV1DrawModel(_model);
	MV1DrawModel(_wModel);
	return true;
}

bool EN_Romanoff::Debug()
{
	return true;
}

bool EN_Romanoff::Delete()
{
	return true;
}








