#include "Divine.h"
#include"ApplicationGlobal.h"
Divine* Divine::_divineInstance = nullptr;
Divine::Divine()
{
	_divineInstance = this;
	_vPos = VGet(0,0,100);
	_hitFlag = false;
	_isDash = false;
	SKILL skill[8] =
	{//	�X�L����, ����͈͂�`�悷�邩, �ʒu, �����蔻��p�T�C�Y, �Ĕ����t���[��, �Ĕ����܂ł̃J�E���g, ����p�J�E���g, �����t���O, ��������, ������������, ����J�n����, �G�t�F�N�g������
		{SKILLNAME::BREATH,	   VGet(0,0,0),   0.0f, 320, 0, 0,  30, true, false, 150.0f, 12.0f,  50.0f, new Effect("res/effekseer/bless/bless.efkefc",			   100.0f), "SE_Breath"},
		{SKILLNAME::CIRCLE,	   VGet(0,0,0), 150.0f, 900, 0, 0,   5, true, false, 500.0f, 27.0f, 400.0f, new Effect("res/effekseer/circle/circle.efkefc",			30.0f), "SE_Circle"},
		{SKILLNAME::LASER,	   VGet(0,0,0), 200.0f, 400, 0, 0,   5, true, false, 240.0f, 27.0f, 70.0f,  new Effect("res/effekseer/laser/Laser.efkefc",				30.0f), "SE_Laser"},
		{SKILLNAME::SLASH,	   VGet(0,0,0), 300.0f, 300, 0, 0,  30, true, false,  96.0f, 12.0f,  30.0f, new Effect("res/effekseer/slash/slash2.efkefc",				80.0f), "SE_Slash"},
		{SKILLNAME::EXPLOSION, VGet(0,0,0), 480.0f, 400, 0, 0, 100, true, false, 150.0f, 10.0f,  15.0f, new Effect("res/effekseer/explosion/explosion_new3.efkefc",	70.0f), "SE_Explosion"},
		{SKILLNAME::DASH,	   VGet(0,0,0), 100.0f, 180, 0, 0,  10, true, false,  60.0f, 15.0f,  60.0f, new Effect("res/effekseer/dash/dash.efkefc",				50.0f), "SE_DashAttack"},
		{SKILLNAME::VACUUM,	   VGet(0,0,0),   0.0f, 600, 0, 0,   0, true, false, 350.0f, 30.0f, 120.0f, new Effect("res/effekseer/vacuum/vacuum.efkefc",			50.0f), "SE_Vacuum"},
		{SKILLNAME::SONIC,	   VGet(0,0,0), 200.0f, 360, 0, 0,  20, true, false,  75.0f,  5.0f,  50.0f, new Effect("res/effekseer/sonicwave/sonicwave.efkefc",		50.0f), "SE_Sonic"}
	};
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		_skill[i] = std::move(skill[i]);
	}
}

Divine::~Divine()
{

}

void Divine::Invocation(kindDivine skillname)
{
	int i = static_cast<int>(skillname);
	if (_skill[i].invocationFlag)
	{
		//���������ǂ�����true��
		_skill[i].isPlaying = true;
		//�X�L�������\���ǂ�����false��
		_skill[i].invocationFlag = false;
	}
}

void Divine::Reset()
{
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (_skill[i].isPlaying)
		{
			//���������ǂ�����true��
			_skill[i].isPlaying = false;
			//�X�L�������\���ǂ�����false��
			_skill[i].invocationFlag = false;
			_skill[i].effect->Stop();
		}
		_skill[i].colCnt = 0;
		_isDash = false;
	}
	
}

bool Divine::Calcalate(VECTOR pos, float roty)
{
	MATRIX matrix = MGetRotY(roty);
	VECTOR _all_skill_calc_pos[MAX_SKILL_NUM] =
	{
		VGet(0,0,0),
		VGet(0,100,0),
		VGet(0,100,400 - (24 * _skill[2].colCnt)),
		VGet(0,0,0),
		VGet(0,100,-630),
		//VGet(0,0,0),
		VGet(0,0,0),
		VGet(0,100,-50),
		VGet(0,0,0)
	};
	for (auto i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (_skill[i].isPlaying)
		{
			if (_skill[i].colCnt > _skill[i].startColFrame &&
				_skill[i].colCnt <= _skill[i].endColFrame)
			{
				_skill[i].vPos = VAdd(pos, VTransform(_all_skill_calc_pos[i], matrix));
			}
		}
	}
	return true;
}

bool Divine::Process(VECTOR pos, float roty)
{
	Calcalate(pos, roty);
	//�X�L���̈ʒu
	VECTOR all_skill_pos[MAX_SKILL_NUM] =
	{
		VGet(0,0,0),
		VGet(0,30,0),
		VGet(0,100,-200),
		VGet(0,0,0),
		VGet(0,0,-630),
		//VGet(0,0,0),
		VGet(0,100,-100),
		VGet(0,100,-50),
		VGet(0,0,0)
	};
	//y����]�̂��߂̃}�g���N�X�쐬
	MATRIX matrix = MGetRotY(roty);
	float all_skill_dir[MAX_SKILL_NUM] =
	{
		90.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
	};
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		//�X�L�������\�łȂ��̂Ȃ�J�E���g�𑝂₷
		if (!_skill[i].invocationFlag)
		{
			_skill[i].divineCnt++;
		}
		//�J�E���g������̃t���[���ɒB����
		if(_skill[i].colCnt >= _skill[i].startColFrame + 10)
		{
			//�Đ��\�t���O��false��
			_skill[i].effect->SetUseFlag(false);
		}
		//�J�E���g�������\�t���[���܂ŒB�����Ȃ�
		if (_skill[i].divineCnt >= _skill[i].reInvocationFrame)
		{
			//�G�t�F�N�g�Đ��\�t���O��true��
			_skill[i].effect->SetUseFlag(true);
			//�X�L�������t���O��true��
			_skill[i].invocationFlag = true;
			//�J�E���g���Z�b�g
			_skill[i].divineCnt = 0;
		}
		//�Đ����łȂ���΃R���e�B�j���[
		if (!_skill[i].isPlaying) continue;
		else{ _skill[i].colCnt++;}
		//�G�t�F�N�g�Đ����Ȃ�
		if (_skill[i].effect->GetPlayFlag())
		{
			//�����̒P�ʂ����W�A���ɕύX
			all_skill_dir[i] = Math::DegToRad(all_skill_dir[i]);
			//������ύX����
			_skill[i].effect->SetDir(VGet(0,roty+all_skill_dir[i], 0));
			//�ʒu��ύX
			_skill[i].effect->SetPos(VAdd(pos, VTransform(all_skill_pos[i], matrix)));
			//�v���Z�X����
			_skill[i].effect->Process();
		}
		//�G�t�F�N�g�̍Đ�
		if (_skill[i].colCnt == _skill[i].startColFrame)
		{
			_skill[i].effect->Play();
			//������Đ�����Ȃ��悤�ɏ�����t����
			if (_skill[i].colCnt <= _skill[i].startColFrame + 1)
			{
				SoundItemBase* snditem_se = gGlobal._sndServer.Get(_skill[i].seCode);
				if (snditem_se && snditem_se->IsLoad())
				{	// �Đ������H
					if (snditem_se->IsPlay() == false)
					{	// �Đ�����
						snditem_se->Play();
					}
				}
			}
		}
		//����J�E���g�����������Ԃɓ��B����
		if (_skill[i].colCnt >= _skill[i].invocationFrame)
		{
			//�������Ă��Ȃ��̂�false
			_skill[i].isPlaying = false;
			_isDash = false;
			//�J�E���g���Z�b�g
			_skill[i].colCnt = 0;
		}
	}
	return true;
}

bool Divine::Render()
{
	//�G�t�F�N�g�̕`��
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (_skill[i].effect->GetPlayFlag())
		{
			_skill[i].effect->Draw();
		}
	}
	return true;
}
bool Divine::Debug()
{
	DrawFormatString(300, 0, GetColor(0, 0, 255), "Cnt =%d", _skill[3].divineCnt);
	DrawFormatString(300, 20, GetColor(0, 0, 255), "Cnt =%d", _skill[4].divineCnt);
	return true;
}