#include "Player.h"
#include "ApplicationGlobal.h"

Player* Player::_plInstance = nullptr;
Player::Player() {
	_plInstance = this;
	//�ʒu
	_vPos = VGet(0.0f, 0.0f, 0.0f);
	//�p�x
	_vDir = VGet(0.0f, 1.0f, 0.0f);
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	nlohmann::json player_pos = jUtil->Import("res/Json/Player_pos.json").at("Player Start");
	for (auto& data : player_pos)
	{
		data.at("translate").at("x").get_to(_vPos.x);
		data.at("translate").at("z").get_to(_vPos.y);
		data.at("translate").at("y").get_to(_vPos.z);
		_vPos.z *= -1.f;				// ���W�̕ϊ�
		data.at("rotate").at("x").get_to(_vDir.x);
		data.at("rotate").at("z").get_to(_vDir.y);
		data.at("rotate").at("y").get_to(_vDir.z);
		_vDir.x = Math::DegToRad(_vDir.x);	// ��]��degree��radian��
		_vDir.y = Math::DegToRad(_vDir.y);
		_vDir.z = Math::DegToRad(_vDir.z);
	}
	//�ړ�
	_vMove = VGet(0.0f, 0.0f, 0.0f);
	//�J�v�Z���̒���
	_lineSeg = 170.0f;
	//�J�v�Z�����a
	_rCap = 30.0f;
	//�J�v�Z�����_(��)
	_vCapsule[0] = VGet(_vPos.x + 0.0f, _vPos.y + 50.0f, _vPos.z + 0.0f);
	//�J�v�Z�����_(��)
	_vCapsule[1] = VGet(_vPos.x + 0.0f, _vPos.y - 50.0f, _vPos.z + 0.0f);
	//���f���`��
	_model = 0;
	//�Đ����Ԃ̏�����
	_playTime = 0.0f;
	//�A�^�b�`����A�j���[�V�����ԍ�
	_attachIndex = -1;
	//�d�͏�����
	_gravity = -15.0f;
	//�J�E���g������
	_actionCnt = 0;
	//�R���{
	_comboCnt;
	//���[�V�����ԍ�
	_actionNum = 0;
	//����ԍ�������
	_weaponNum = 0;
	//�U������
	_isAttack = false;
	//���G����
	_noDamage = false;
	//�X�L����������
	_isSkill = false;
	//����ł��邩
	_isDie = false;
	//�Q�[���I�[�o�[�t���O
	_gameOverFlag = false;
	//�Ō�ɉ������{�^��
	_lastCommand = -1;
	//����ʒu
	_wPos[0] = VGet(0, 0, 0);
	_wPos[1] = VGet(0, 0, 0);
	//�v���C���[���[�V�������
	_status = ACTION::WAIT;
	_oldAnimation = ANIMATION::WAIT;
	//�ʏ�h���U�����
	Player::ATTACKDATA attackData[ATTACKCOUNT] =
	{   //���[�V��������,	�S�̃t���[��, �P�\�t���[��(�J�n), �P�\�t���[��(�I��), ���[�V�����ύX����, �U���J�n����, �U���I������, �U������, ����͈�, ���̓t���O,  �ύX�t���O,  �h���\��, ����܂ł̃t���[��
		{Player::ANIMATION::NOATTACK,		 0.0f,  0.0f,  0.0f,  0.0f, 1.0f,  2.0f,{VGet(0,0,0)   ,VGet(0,0,0)},	 0.0f,  true,  false, true ,"",""},
		{Player::ANIMATION::FIRSTATTACK,	65.0f, 15.0f, 60.0f, 40.0f, 25.0f, 35.0f,{VGet(90,150,0),VGet(-60,0,0)}, 50.0f,  false, false, true ,"VO_Fe_Attack01","SE_Attack01"},
		{Player::ANIMATION::SECONDATTACK,	72.0f, 15.0f, 70.0f, 28.0f, 5.0f, 30.0f,{VGet(-60,0,0) ,VGet(60,0,0)},	50.0f,  false, false, true ,"VO_Fe_Attack02","SE_Attack02"},
		{Player::ANIMATION::LASTATTACK,		90.0f, 25.0f, 54.0f,  0.0f,31.0f, 54.0f,{VGet(0,0,0)   ,VGet(0,0,0)},	50.0f,  false, false, false,"VO_Fe_Attack03","SE_Attack03"},
	};
	//�R���e�i�v�f������
	//�v���C���[�ʏ�U�����
	for (int i = 0; i < ATTACKCOUNT; i++)
	{
		_attackContainer.emplace(i, attackData[i]);
	}
	//������
	//�U�����
	AttackMotionChange(0);
	_skill = new Divine();
	//�e�p�����[�^����
	_hp = 255;
	_ATK = 0;
	_DEF = 0;
	_SPD = 0;
	_pm = new PP::Parameter();
	_pm->TestJsonLoad("res/Json/test.json");
	_ATK = _pm->GetATK();
	_DEF = _pm->GetDEF();
	_SPD = _pm->GetSPD();
	delete _pm;

}

Player::~Player() {
	_pm = new PP::Parameter();
	_pm->TestJsonLoad("res/Json/test.json");
	_pm->SetATK(_ATK);
	_pm->SetDEF(_DEF);
	_pm->SetSPD(_SPD);
	_pm->TestJsonSave("res/Json/test.json");
	delete _pm;
	delete _skill;
	MV1DetachAnim(_model, _attachIndex);
}

void Player::Initialize(int handle, int weapon) {
	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j	
	_model = handle;
	// 3D���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	_attachIndex = MV1AttachAnim(_model, 0, -1, FALSE);
	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	_totalTime = gGlobal._RS->mGetAttach()["player_stand"]._attach_time;
	//���탂�f���̃��[�h
	_wModel = weapon;
}

void Player::A_Process()
{
	std::string mName;
	//static ANIMATION _old_animation;
	if (_oldAnimation != _animation)
	{
		MV1DetachAnim(_model, _attachIndex);
		switch (_animation)
		{
		case ANIMATION::WAIT:
			// �ҋ@��Ԃ̃A�j���[�V�������A�^�b�`����
			mName = "player_stand";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::WALK:
			// ����A�j���[�V�������A�^�b�`����
			mName = "player_run";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::FIRSTATTACK:
			//�c�a�胂�[�V�������A�^�b�`����
			mName = "player_attack1";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::SECONDATTACK:
			//���a�胂�[�V�������A�^�b�`����
			mName = "player_attack2";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::LASTATTACK:
			//��]�a�胂�[�V�������A�^�b�`����
			mName = "player_attack3";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::SKILL:
			//�f�B�o�C���X�L�����g�p���郂�[�V�������A�^�b�`����
			mName = "player_skill";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::AVOID:
			//������[�V�������A�^�b�`����
			mName = "player_attack1";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::DAMAGE:
			//�_���[�W���[�V�������A�^�b�`����
			mName = "player_damage";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::DIE:
			//���S���[�V�������A�^�b�`����
			mName = "player_blow";
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
		if (_animation==ANIMATION::DIE)
		{
			_playTime = _totalTime;
			_gameOverFlag = true;
		}
		else { _playTime = 0.0f; }
	}
	_oldAnimation = _animation;
}

void Player::AttackMotionChange(int motionId)
{
	//�C�e���[�^�őΉ��L�[��������
	auto itr = _attackContainer.find(motionId);
	if (itr != _attackContainer.end())
	{//�Ή��L�[������������Ή��v�f��������
		_attackData[motionId] = itr->second;
		//���̍ۂ̔ԍ����A�j���[�V�����v���Z�X�Ŏg����悤���
		if (motionId != 0) { _animation = _attackData[motionId].animation; }
		_actionCnt = 0;
	}
}

bool Player::Attack()
{
	//�X�e�[�^�X���U���Ɋւ������
	if (_animation == ANIMATION::FIRSTATTACK 
		|| _animation == ANIMATION::SECONDATTACK 
		|| _animation == ANIMATION::LASTATTACK)
	{
		//true��Ԃ�
		return true;
	}
	else
	{
		//false��Ԃ�
		return false;
	}
	
}

int Player::SetSpeed()
{
	//�X�s�[�h
	int speed = 0;
	//�U����
	if (Attack() || _isSkill)
	{
		//�X�s�[�h��0��
		speed = 0.f;
	}
	//�_�b�V���A�^�b�N��
	else if (_skill->GetIsDash())
	{
		//�X�s�[�h���㏸������
		speed = 30.f;
	}
	else
	{
		speed = 15;
	}
	return speed;
}

void Player::SetWeapon()
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

Player::ANIMATION Player::SkillAnimation()
{
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		int cnt = _skill->GetSkill(i).divineCnt;
		if (cnt > 0 && cnt <= 38)
		{
			switch (_skill->GetSkill(i).skillName)
			{
			case Divine::SKILLNAME::BREATH:
			case Divine::SKILLNAME::CIRCLE:
			case Divine::SKILLNAME::EXPLOSION:
			case Divine::SKILLNAME::LASER:
			case Divine::SKILLNAME::SLASH:
			case Divine::SKILLNAME::SONIC:
			case Divine::SKILLNAME::VACUUM:
				_animation = ANIMATION::SKILL;
				break;
			case Divine::SKILLNAME::DASH:
				_animation = ANIMATION::WALK;
				break;
			}
		}

	}
	return _animation;
} 
void Player::SkillVoice()
{
	std::string voice;
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		switch (_skill->GetSkill(i).skillName)
		{
		case Divine::SKILLNAME::BREATH:
			voice = "VO_Fe_Breath";
			break;
		case Divine::SKILLNAME::CIRCLE:
			voice = "VO_Fe_Circle";
			break;
		case Divine::SKILLNAME::EXPLOSION:
			voice = "VO_Fe_Explosion";
			break;
		case Divine::SKILLNAME::LASER:
			voice = "VO_Fe_Laser";
			break;
		case Divine::SKILLNAME::SLASH:
			voice = "VO_Fe_Slash";
			break;
		case Divine::SKILLNAME::DASH:
			voice = "VO_Fe_Avoid";
			break;
		case Divine::SKILLNAME::SONIC:
			voice = "VO_Fe_Slash";
			break;
		case Divine::SKILLNAME::VACUUM:
			voice = "VO_Fe_Attack03";
			break;
		}
		if (_skill->GetSkill(i).divineCnt > 0 && _skill->GetSkill(i).divineCnt < 10)
		{
			SoundItemBase* snditem_voice = gGlobal._sndServer.Get(voice);
			if (snditem_voice && snditem_voice->IsLoad())
			{
				if (!snditem_voice->IsPlay())
				{
					snditem_voice->Play();
				}
			}
		}
	}
}

void Player::PlayerMove(int key, VECTOR campos, VECTOR camtarget)
{
	// �L�����ړ�(�J�����ݒ�ɍ��킹��)
	// �J�����̌����Ă���p�x���擾      
	float sx = campos.x - camtarget.x;
	float sz = campos.z - camtarget.z;
	float camrad = atan2(sz, sx);
	// �ړ����������߂�
	_vMove = { 0,0,0 };
	//���鑬�x�̐ݒ�
	float mvSpeed = SetSpeed();
	//�ړ�����������
	if (key & PAD_INPUT_DOWN) { _vMove.x = 1; }
	if (key & PAD_INPUT_UP) { _vMove.x = -1; }
	if (key & PAD_INPUT_LEFT) { _vMove.z = -1; }
	if (key & PAD_INPUT_RIGHT) { _vMove.z = 1; }
	// v��rad����]������
	float length = 0.f;
	if (VSize(_vMove) > 0.f)
	{
		length = mvSpeed;
	}
	float rad = atan2(_vMove.z, _vMove.x);
	_vMove.x = cos(rad + camrad) * length;
	_vMove.z = sin(rad + camrad) * length;
	// v�̕��ړ�
	_vPos = VAdd(_vPos, _vMove);
	_vPos.y += _gravity;
	// �ړ��ʂ����̂܂܃L�����̌����ɂ���
	if (VSize(_vMove) > 0.f)
	{
		// �ړ����Ă��Ȃ����͖������邽��
		// �v���C���[�̃X�e�[�^�X���uWALK�v�ɕύX
		_animation = ANIMATION::WALK;
		_vDir = _vMove;
	}
	// �v���C���[�̃X�e�[�^�X���uWAIT�v�ɕύX
	else { _animation = ANIMATION::WAIT; }
	if (_vPos.y <= 0)
	{
		_vPos.y = 0;
	}
	
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);
	_vDir.y = vRot.y;
	// �ʒu
	MV1SetPosition(_model, _vPos);
}

void Player::PlayerAttack(int trg)
{
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(_attackData[_actionNum].voiceCode);
	SoundItemBase* snditem_se = gGlobal._sndServer.Get(_attackData[_actionNum].seCode);
	//�J�E���g�𑝂₷
	if (_actionNum != 0) { _actionCnt++; }
	//�t���[���J�E���g�����͗P�\�t���[�����Ȃ��
	if (_actionCnt >= _attackData[_actionNum].pushButtonStartFrame && _actionCnt <= _attackData[_actionNum].pushButtonEndFrame)
	{//�{�^�����̓t���O��true�ɂ���
		_attackData[_actionNum].pushFlug = true;
		// �ǂݍ��݊������Ă��邩�H
		if (snditem_voice && snditem_voice->IsLoad())
		{
			// �Đ������H
			if (!snditem_voice->IsPlay())
			{
				// �Đ�����
				snditem_voice->Play();
			}
		}
		if (snditem_se && snditem_se->IsLoad())
		{
			// �Đ������H
			if (!snditem_se->IsPlay())
			{
				// �Đ�����
				snditem_se->Play();
			}
		}
	}
	//�ʏ�U���{�^������������
	//�_���[�W���ł͂Ȃ�
	if (trg & PAD_INPUT_4)
	{
		//�{�^�����̓t���O��true�̏ꍇ
		if (_attackData[_actionNum].pushFlug)
		{//���[�V�����ύX�t���O��true�ɕύX
			_attackData[_actionNum].changeFlug = true;
		}
	}
	//���[�V�����ύX�t���O��true
	if (_attackData[_actionNum].changeFlug)
	{//�����[�V�������؂�ւ��t���[���J�E���g�ɓ��B����
		if (_actionCnt >= _attackData[_actionNum].motionChangeStartFrame)
		{
			//�����̍U�����h���\�Ȃ��
			if (_attackData[_actionNum].isDerivasion)
			{//�J�E���g�𑝂₵�ă��[�V�����ύX
				if (_actionCnt != 0)
				{
					snditem_voice->Stop();
					snditem_se->Stop();
				}
				_actionNum++;
				AttackMotionChange(_actionNum);
			}
		}
	}
	//�U����
	if (_actionNum != 0)
	{//�J�E���g�����t���[���ɓ��B���Ă��Ȃ�
		if (_actionCnt != _attackData[_actionNum].motionAllFrame)
		{//��Ԃ����̂܂܂�
			_status = ACTION::ATTACK;
		}
		if (_actionCnt == 0 || _actionCnt == _attackData[_actionNum].motionAllFrame)
		{
			int frame_index = MV1SearchFrame(_model, "Character1_Hips");
			//�ʒu�����[�J������O���[�o���ɕϊ�����}�g���b�N�X���쐬
			MATRIX matrix = MV1GetFrameLocalWorldMatrix(_model, frame_index);
			VECTOR vec = VTransform(VGet(0, 0, 0), matrix);
			_vPos = VGet(vec.x, 0, vec.z);
		}
	}
	//�������͂����J�E���g���g�[�^���t���[���ɒB����
	if (_actionCnt == _attackData[_actionNum].motionAllFrame)
	{//���[�V�������U�����Ă��Ȃ���Ԃ�
		if (_actionCnt != 0)
		{
			snditem_voice->Stop();
			snditem_se->Stop();
		}
		_actionNum = 0;
		AttackMotionChange(_actionNum);
		//�J�E���g�����Z�b�g
		_actionCnt = 0;
		_status = ACTION::WAIT;
	}
}



void Player::PlayerSkill(int trg, int key, int rel, SkillSlot* slot,  VECTOR campos, VECTOR camtarget)
{
	std::array<kindDivine, 3> _slot = slot->Getslot();

	if (trg & PAD_INPUT_1)
	{
		_skill->Invocation(_slot[1]);
		_lastCommand = 1;
	}
	if (trg & PAD_INPUT_2)
	{
		_skill->Invocation(_slot[0]);
		_lastCommand = 0;
	}
	if (trg & PAD_INPUT_3)
	{
		_skill->Invocation(_slot[2]);
		_lastCommand = 2;
	}
	// ��������Y����]���Z�o
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);
	_vDir.y = vRot.y;
	//���f���̉�]�l�����f���ɑ��
	MV1SetRotationXYZ(_model, vRot);
	_skill->Process(_vPos, _vDir.y);
	SkillVoice();
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (_skill->GetSkill(i).divineCnt > 0 && _skill->GetSkill(i).divineCnt < 54)
		{
			_status = ACTION::SKILL;
			if (_skill->GetSkill(i).skillName == Divine::SKILLNAME::DASH)
			{
				PlayerMove(key, campos, camtarget);
			}
			_animation = SkillAnimation();
		}
		if (_skill->GetSkill(i).colCnt > 54 && _skill->GetSkill(i).colCnt < 55)
		{
			_status = ACTION::WAIT;
		}
	}
}

void Player::Damage(VECTOR pos, int subpoint)
{
	std::string se_code_damage[3] =
	{
		"VO_Fe_Damage1",
		"VO_Fe_Damage2",
		"VO_Fe_Damage3",
	};
	std::string se_code_die[2] =
	{
		"VO_Fe_Blow1",
		"VO_Fe_Blow2"
	};
	_hp = _hp - subpoint;
	if (_hp <= 0)
	{
		//�X�e�[�^�X�����S��
		_status = ACTION::DIE;
		_animation = ANIMATION::DIE;
		SoundItemBase* snditem_voice = gGlobal._sndServer.Get(se_code_die[rand() % 2]);
		snditem_voice->SetVolume(255);
		if (snditem_voice && snditem_voice->IsLoad())
		{// �Đ������H
			if (snditem_voice->IsPlay() == false)
			{// �Đ�����
				snditem_voice->Play();
			}
		}
	}
	if (_hp > 0)
	{
		//�X�e�[�^�X���_���[�W��
		_status = ACTION::DAMAGE;
		SoundItemBase* snditem_voice = gGlobal._sndServer.Get(se_code_damage[rand() % 3]);
		snditem_voice->SetVolume(255);
		if (snditem_voice && snditem_voice->IsLoad())
		{// �Đ����łȂ��Ȃ�
			if (snditem_voice->IsPlay() == false)
			{// �Đ�����
				snditem_voice->Play();
			}
		}
	}
	VECTOR v = VSub(_vPos, pos);
	v = VScale(VNorm(v), 50);
	_vMove = VAdd(_vMove, v);
	_vPos = VAdd(_vPos, v);
	_actionNum = 0;
	AttackMotionChange(_actionNum);
	_skill->Reset();
}

void Player::PlayerDie()
{
	_noDamage = true;
	_isDie = true;
}

void Player::Invincible()
{
	if (!_isDie)
	{
		if (_noDamage)_invincibleCnt++;
		if (_invincibleCnt > 0 && _invincibleCnt <= 42)
		{
			_animation = ANIMATION::DAMAGE;
		}
		if (_invincibleCnt > 42)
		{
			_status = ACTION::WAIT;
		}
		if (_invincibleCnt > 80)
		{
			_noDamage = false;
			_invincibleCnt = 0;
		}
	}
	
}

void Player::ActionProcess(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	// �ړ����������߂�
	_vMove = { 0,0,0 };
	bool attack = false;
	bool move = false;
	bool skill = false;
	switch (_status)
	{
	case ACTION::WAIT:
		_animation = ANIMATION::WAIT;
		move = true;
		attack = true;
		skill = true;
		break;
	case ACTION::WALK:
		_animation = ANIMATION::WALK;
		move = true;
		attack = true;
		skill = true;
		break;
	case ACTION::ATTACK:
		_animation = _attackData[_actionNum].animation;
		move = false;
		attack = true;
		skill = true;
		break;
	case ACTION::SKILL:
		attack = true;
		move = false;
		skill = true;
		break;
	case ACTION::AVOID:
		_animation = ANIMATION::AVOID;
		attack = false;
		move = false;
		skill = false;
		break;
	case ACTION::DAMAGE:
		attack = false;
		move = false;
		skill = false;
		break;
	case ACTION::DIE:
		_animation = ANIMATION::DIE;
		PlayerDie();
		attack = false;
		move = false;
		skill = false;
		break;
	}
	if (attack)
	{
		PlayerAttack(trg);
	}
	if (move)
	{
		PlayerMove(key, campos, camtarget);
	}
	if (skill)
	{
		PlayerSkill(trg, key, rel, slot, campos, camtarget);
	}
	if (_hp <= 0)
	{
		_status = ACTION::DIE;
		_animation = ANIMATION::DIE;
	}
	Invincible();
	SetWeapon();
}

void Player::C_Process() 
{
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
}

void Player::Process(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	A_Process();
	ActionProcess(trg, key, rel, campos, camtarget,slot);
	C_Process();
}

void Player::Render() 
{
	_skill->Render();
	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(_model, _attachIndex, _playTime);
	// ���f����`�悷��
	MV1DrawModel(_model);
	MV1DrawModel(_wModel);
}


void Player::PlDebug()
{
	clsDx();
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", _invincibleCnt);
	DrawCapsule3D(VAdd(_vCapsule[0], VGet(0, _rCap, 0)), _vCapsule[1], _rCap, 5, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	
	DrawFormatString(0, 100, GetColor(255, 255, 255), "%f,%f,%f", _wPos[0].x, _wPos[0].y, _wPos[0].z);
}