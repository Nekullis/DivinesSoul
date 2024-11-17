#include "GameEvent.h"
#include "ApplicationGlobal.h"
GameEvent* GameEvent::_evInstance = nullptr;
GameEvent::GameEvent()
{
	_evInstance = this;
	//�N���X������
	_enManager = new EnemyManager();
	//�G�A���탂�f��
	_handle[0] = gGlobal.mGetModel()["EN_Osero"]._handle;
	_handle[1] = gGlobal.mGetModel()["EN_Crab"]._handle;
	_handle[2] = gGlobal.mGetModel()["EN_Romanoff"]._handle;
	_wModel[0] = gGlobal.mGetModel()["W_Sword"]._handle;
	_wModel[1] = gGlobal.mGetModel()["W_Axe"]._handle;
	//�C�x���gUI
	_handleQuestFeld[0]     = gGlobal.mGetGraph()["UI_Feld_Quest_01"]._handle;
	_handleQuestFeld[1]     = gGlobal.mGetGraph()["UI_Feld_Quest_02"]._handle;
	_handleQuestFeld[2]     = gGlobal.mGetGraph()["UI_Feld_Quest_03"]._handle;
	_handleQuestFeld[3]     = gGlobal.mGetGraph()["UI_Feld_Quest_04"]._handle;
	_handleQuestFeld[4]     = gGlobal.mGetGraph()["UI_Feld_Quest_05"]._handle;
	_handleQuestFeld[5]     = gGlobal.mGetGraph()["UI_Feld_Quest_06"]._handle;
	_handleQuestFeld[6]     = gGlobal.mGetGraph()["UI_Feld_Quest_07"]._handle;
	_handleQuestFeld[7]     = gGlobal.mGetGraph()["UI_Feld_Quest_08"]._handle;
	_handleQuestFeld[8]     = gGlobal.mGetGraph()["UI_Feld_Quest_09"]._handle;
	_handleQuestFeld[9]     = gGlobal.mGetGraph()["UI_Feld_Quest_10"]._handle;
	_handleQuestFeld[10]    = gGlobal.mGetGraph()["UI_Feld_Quest_11"]._handle;
	_hamdleQuestRomanoff[0] = gGlobal.mGetGraph()["UI_Romanoff_Quest_01"]._handle;
	_hamdleQuestRomanoff[1] = gGlobal.mGetGraph()["UI_Romanoff_Quest_02"]._handle;
	_hamdleQuestRomanoff[2] = gGlobal.mGetGraph()["UI_Romanoff_Quest_03"]._handle;
	_hamdleQuestRomanoff[3] = gGlobal.mGetGraph()["UI_Romanoff_Quest_04"]._handle;
	_hamdleQuestRomanoff[4] = gGlobal.mGetGraph()["UI_Romanoff_Quest_05"]._handle;
	_hamdleQuestRomanoff[5] = gGlobal.mGetGraph()["UI_Romanoff_Quest_06"]._handle;
	_hamdleQuestRomanoff[6] = gGlobal.mGetGraph()["UI_Romanoff_Quest_07"]._handle;
	//wave�ԍ�
	_initNum = 0;
	_questNum = -1;
	_divineEv = 0;
	//����wave
	EnemyWaveInit(_initNum);
	//�C�x���g�p
	_storyEv = 0;
	_waveEv = 0;
	_hpEv = -1;
	_hpCast = 3000;
	_timeCnt = 0;
	RegisterEvent();
	
}
GameEvent::~GameEvent()
{

}

bool GameEvent::GameOver()
{
	if (gGlobal._PM->P_GetDie())
	{
		int begin_game_over_time = 120;
		_timeCnt++;
		if (_timeCnt >= begin_game_over_time) 
		{ 
			_timeCnt = 0;
			return true; 
		}
	}
	return false;
}

bool GameEvent::GameClear(EN_Romanoff* en)
{
	if (_storyEv >= 1)
	{
		if (en->GetDeleteFlag())
		{
			int begin_game_over_time = 60;
			_timeCnt++;
			if (_timeCnt >= begin_game_over_time) 
			{ 
				_timeCnt = 0;
				return true; 
			}
		}
	}
	return false;
}

void GameEvent::RegisterEvent()
{	//�C�x���g�\���̂̍쐬
	EVENT ev[MAX_EVENT_NUM] =
	{
		{_handleQuestFeld[0],	  0, 150, false, "VO_Fe_Quest_01"},
		{_handleQuestFeld[1],	  0, 300, false, "VO_Fe_Quest_02"},
		{_handleQuestFeld[2],	  0, 180, false, "VO_Fe_Quest_03"},
		{_handleQuestFeld[3],	  0, 300, false, "VO_Fe_Quest_04"},
		{_handleQuestFeld[4],	  0, 480, false, "VO_Fe_Quest_05"},
		{_handleQuestFeld[5],	  0, 180, false, "VO_Fe_Quest_06"},
		{_handleQuestFeld[6],	  0, 300, false, "VO_Fe_Quest_07"},
		{_handleQuestFeld[7],	  0, 360, false, "VO_Fe_Quest_08"},
		{_handleQuestFeld[8],	  0, 300, false, "VO_Fe_Quest_09"},
		{_handleQuestFeld[9],	  0, 120, false, "VO_Fe_Quest_10"},
		{_handleQuestFeld[10],	  0, 120, false, "VO_Fe_Quest_11"},
		{_hamdleQuestRomanoff[0], 0, 300, false, "VO_Ro_Quest_01"},
		{_hamdleQuestRomanoff[1], 0, 480, false, "VO_Ro_Quest_02"},
		{_hamdleQuestRomanoff[2], 0, 480, false, "VO_Ro_Quest_03"},
		{_hamdleQuestRomanoff[3], 0, 480, false, "VO_Ro_Quest_04"},
		{_hamdleQuestRomanoff[4], 0, 480, false, "VO_Ro_Quest_05"},
		{_hamdleQuestRomanoff[5], 0, 600, false, "VO_Ro_Quest_06"},
		{_hamdleQuestRomanoff[6], 0, 900, false, "VO_Ro_Quest_07"},
	};
	for (int i = 0; i < MAX_EVENT_NUM; i++)
	{	//�����o�ϐ��Ɉړ�
		_event[i] = std::move(ev[i]);
	}
}

bool GameEvent::WaveNum(int i)
{	//wave�Ɋւ���C�x���g�ԍ�
	if (i == 2 || i == 3 || i == 4 || i == 5 || i == 6)
	{
		return true;
	}
	return false;
}

bool GameEvent::StoryNum(int i)
{	//�X�g�[���[�Ɋւ���C�x���g�ԍ�
	if (i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 14)
	{
		return true;
	}
	return false;
}

bool GameEvent::DivineNum(int i)
{	//�f�B�o�C���Ɋւ���C�x���g�ԍ�
	if (i == 0 || i == 1 )
	{
		return true;
	}
	return false;
}

void GameEvent::OccurEvent(int i)
{	//�C�x���g����
	//�ԍ��̑��
	_questNum = i;
	//�C�x���g�������Ȃ̂�true��
	_event[_questNum].isOccur = true;
	//���̔ԍ��̃{�C�X����
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(_event[_questNum].voiceCode);
	//���ʒ���
	snditem_voice->SetVolume(255);
	if (_event[_questNum].eventCnt <= 10)
	{
		if (snditem_voice && snditem_voice->IsLoad())
		{	// �Đ����łȂ��Ȃ�
			if (snditem_voice->IsPlay() == false)
			{	// �Đ�����
				snditem_voice->Play();
			}
		}
	}
}

void GameEvent::OccurProcess()
{	//�ԍ��������l�łȂ�
	if (_questNum != -1)
	{	//�C�x���g�������Ȃ炻�̔ԍ��̃C�x���g�J�E���g�����Z
		if (_event[_questNum].isOccur) { _event[_questNum].eventCnt++; }
		//�C�x���g�J�E���g���K��l�܂ŒB����
		if (_event[_questNum].eventCnt >= _event[_questNum].maxEventCnt)
		{	//�����I�������̂�false��
			_event[_questNum].isOccur = false;
			//�J�E���g���Z�b�g
			_event[_questNum].eventCnt = 0;
			//�ԍ�����
			int old_num = _questNum;
			//�ԍ�������
			_questNum = -1;
			//�e�C�x���g�J�E���g�̉��Z
			if(WaveNum(old_num))
			{
				_waveEv++;
			}
			if(StoryNum(old_num))
			{
				_storyEv++;
			}
			if(DivineNum(old_num))
			{
				_divineEv++;
			}
		}
	}
}

void GameEvent::EnemyWaveInit(int i)
{
	//�L�[
	std::string wave[6] =
	{
		"Enemy_Wave1",
		"Enemy_Wave2",
		"Enemy_Wave3",
		"Enemy_Wave4",
		"Enemy_Wave5",
		"Enemy_Wave8",
	};
	//�ʒu
	VECTOR pos = VGet(0, 0, 0);
	//�p�x
	VECTOR dir = VGet(0, 0, 0);
	//json�̏�����
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	//json�̃C���|�[�g
	nlohmann::json enemy_pos = jUtil->Import("res/Json/Enemy_pos.json").at(wave[i]);
	//�C���|�[�g���ꂽ�G�̈ʒu�̕��J��Ԃ�
	for (auto& data : enemy_pos)
	{
		std::string name;
		//���O�̎擾
		data.at("objectName").get_to(name);
		//���W���e�v�f�Ŏ擾
		data.at("translate").at("x").get_to(pos.x);
		data.at("translate").at("z").get_to(pos.y);
		data.at("translate").at("y").get_to(pos.z);
		data.at("rotate").at("x").get_to(dir.x);
		data.at("rotate").at("z").get_to(dir.y);
		data.at("rotate").at("y").get_to(dir.z);
		dir.x = Math::DegToRad(dir.x);	// ��]��degree��radian��
		dir.y = Math::DegToRad(dir.y);
		dir.z = Math::DegToRad(dir.z);
		//UE5�ł͍��W�n���Ⴄ�̂ŕϊ�����
		pos.z *= -1;
		//�擾�������O�ŃX�|�[��������G��ς���
		if (name == "EN_Osero")
		{	//osero�̃X�|�[��
			_enManager->Spawn(new EN_Osero(_handle[0], _wModel[0], pos, dir));
		}
		else if (name == "EN_Crab")
		{	//crab�̃X�|�[��
			_enManager->Spawn(new EN_Crab(_handle[1], -1, pos, dir));
		}
		else if (name == "EN_Romanoff")
		{	//romanoff�̃X�|�[��
			_enManager->Spawn(new EN_Romanoff(_handle[2], _wModel[1], pos, dir));
		}
	}
}

void GameEvent::WaveProcess()
{
	//�X�|�[�����邽�߂̓G���i�[���Ă���R���e�i���擾
	std::list<Enemy*> list = _enManager->GetEnemyList();
	//�}�l�[�W���[�̃v���Z�X�����s
	_enManager->Process(gGlobal._PM->P_GetPos());
	//�G�̐���0�ɂȂ���
	if (list.size() <= 0)
	{
		//wave�ԍ����X�V
		_initNum++;
		if (_storyEv == 0)
		{
			_waveEv++;
		}
		//wavw�ԍ���wave�ω��\����
		if (_initNum < MAX_SPAWN_WAVE)
		{	//wave���X�V����
			EnemyWaveInit(_initNum);
		}
	}
}

void GameEvent::EventProcess()
{
	OccurProcess();
	//wave�Ɋւ���C�x���g�ԍ�
	switch (_waveEv)
	{
	case 0:
		OccurEvent(2);
		break;
	case 2:
		OccurEvent(3);
		break;
	case 4:
		OccurEvent(4);
		break;
	case 6:
		OccurEvent(5);
		break;
	case 8:
		OccurEvent(6);
		break;
	}
	//�X�g�[���[�Ɋւ���C�x���g�ԍ�
	switch (_storyEv)
	{
	case 1:
		OccurEvent(11);
		break;
	case 2:
		OccurEvent(7);
		break;
	case 4:
		OccurEvent(12);
		break;
	case 5:
		OccurEvent(13);
		break;
	case 6:
		OccurEvent(8);
		break;
	case 7:
		OccurEvent(14);
		break;
	}
	//�f�B�o�C���Ɋւ���C�x���g�ԍ�
	switch (_divineEv)
	{
	case 1:
		OccurEvent(0);
		break;
	case 2:
		OccurEvent(1);
		break;
	}

}

void GameEvent::CastEnemy(int i)
{
	std::string cast[3] =
	{
		"Boss_Cast_Wave1",
		"Boss_Cast_Wave2",
		"Boss_Cast_Wave3",
	};
	//�ʒu
	VECTOR pos = VGet(0, 0, 0);
	//�p�x
	VECTOR dir = VGet(0, 0, 0);
	//json�̏�����
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	//json�̃C���|�[�g
	nlohmann::json enemy_pos = jUtil->Import("res/Json/Boss_Cast_Enemy.json").at(cast[i]);
	//�C���|�[�g���ꂽ�G�̈ʒu�̕��J��Ԃ�
	for (auto& data : enemy_pos)
	{
		std::string name;
		//���O�̎擾
		data.at("objectName").get_to(name);
		//���W���e�v�f�Ŏ擾
		data.at("translate").at("x").get_to(pos.x);
		data.at("translate").at("z").get_to(pos.y);
		data.at("translate").at("y").get_to(pos.z);
		data.at("rotate").at("x").get_to(dir.x);
		data.at("rotate").at("z").get_to(dir.y);
		data.at("rotate").at("y").get_to(dir.z);
		dir.x = Math::DegToRad(dir.x);	// ��]��degree��radian��
		dir.y = Math::DegToRad(dir.y);
		dir.z = Math::DegToRad(dir.z);
		//UE5�ł͍��W�n���Ⴄ�̂ŕϊ�����
		pos.z *= -1;
		//�擾�������O�ŃX�|�[��������G��ς���
		if (name == "EN_Osero")
		{	//osero�̃X�|�[��
			_enManager->Spawn(new EN_Osero(_handle[0], _wModel[0], pos, dir));
		}
		else if (name == "EN_Crab")
		{	//crab�̃X�|�[��
			_enManager->Spawn(new EN_Crab(_handle[1], -1, pos, dir));
		}
	}
}

void GameEvent::CastProcess()
{
	//�X�g�[���[�Ɋւ���C�x���g�ԍ���0�ȏ�
	if (_storyEv >= 1)
	{	//�{�X�̗͔̑�r�p�ϐ����K��l�ȏ�
		if (_hpCast >= 1000)
		{	//�{�X�̗̑͂���r�ϐ��l��菬����
			if (EN_Romanoff::GetInstance()->GetHp() <= _hpCast)
			{	//hp�C�x���g���Z
				_hpEv++;
				//�G�̏���
				CastEnemy(_hpEv);
				//�̗͔�r�ϐ����K��l
				if (_hpCast == 2000)
				{	//�X�g�[���[�C�x���g���Z
					_storyEv++;
				}
				//��r�p�ϐ�������
				_hpCast -= 1000;
			}
		}
	}
	
}

void GameEvent::Process()
{
	//�G�����Ɋւ��鏈��
	CastProcess();
	//�C�x���g�Ɋւ��鏈��
	EventProcess();
	//�E�F�[�u�Ɋւ��鏈��
	WaveProcess();
}

void GameEvent::DrawQuest()
{
	if (_questNum != -1)
	{	//�C�x���g�������Ȃ�
		if (_event[_questNum].isOccur)
		{	//�摜�\��
			DrawGraph(0, 0, _event[_questNum].handleUI, TRUE);
		}
	}
}

void GameEvent::DrawWave()
{	//wave�̕����`�ʗp�n���h��
	int cg_wave= gGlobal._RS->mGetGraph()["UI_wave"]._handle;
	//��wave���`�ʗp�n���h��
	int cg_wave_num = gGlobal._RS->mGetDivGraph()["wave_number"].handle[_initNum + 1];
	int cg_wave_slash = gGlobal._RS->mGetGraph()["wave_slash"]._handle;
	///�ő�wave���`�ʗp�n���h��
	int cg_wave_max = gGlobal._RS->mGetDivGraph()["wave_number"].handle[MAX_SPAWN_WAVE];
	DrawGraph(30, 196, cg_wave, true);
	DrawGraph(55, 270, cg_wave_num, true);
	DrawGraph(100, 300, cg_wave_slash, true);
	DrawGraph(130, 330, cg_wave_max, true);
}

void GameEvent::DrawEventUI()
{
	DrawQuest();
	DrawWave();
}

void GameEvent::Render()
{
	//�G�̕`��
	_enManager->Render();
	
}