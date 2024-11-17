#include "GameUI.h"
#include "GameEvent.h"
#include "EN_Romanoff.h"
#include "GameSystem.h"
GameUI::GameUI()
{
	_uiPlHp = gGlobal._RS->mGetGraph()["UI_playerhp"]._handle;
	_uiPlHpBarFrame = gGlobal._RS->mGetGraph()["UI_playerhp_bar"]._handle;
	_uiEnHp = gGlobal._RS->mGetGraph()["UI_enemyhp"]._handle;
	_uiEnHpBarFrame = gGlobal._RS->mGetGraph()["UI_enemyhp_bar"]._handle;
	_uiIconFrame[0] = gGlobal._RS->mGetGraph()["UI_icon_frame_01"]._handle;
	_uiIconFrame[1] = gGlobal._RS->mGetGraph()["UI_icon_frame_02"]._handle;
	_uiIconFrame[2] = gGlobal._RS->mGetGraph()["UI_icon_frame_03"]._handle;
	_uiIconFrame[3] = gGlobal._RS->mGetGraph()["UI_icon_frame_04"]._handle;
	_uiDIcon[kindDivine::BLEATH] = gGlobal._RS->mGetGraph()["UI_skill_bleath"]._handle;
	_uiDIcon[kindDivine::LASER] = gGlobal._RS->mGetGraph()["UI_skill_lasar"]._handle;
	_uiDIcon[kindDivine::CIRCLE] = gGlobal._RS->mGetGraph()["UI_skill_sircle"]._handle;
	_uiDIcon[kindDivine::SLASH] = gGlobal._RS->mGetGraph()["UI_skill_slash"]._handle;
	_uiDIcon[kindDivine::DASH] = gGlobal._RS->mGetGraph()["UI_skill_dashattack"]._handle;
	_uiDIcon[kindDivine::SONIC_WAVE] = gGlobal._RS->mGetGraph()["UI_skill_sonic"]._handle;
	_uiDIcon[kindDivine::EXPLOSION] = gGlobal._RS->mGetGraph()["UI_skill_explosion"]._handle;
	_uiDIcon[kindDivine::VACCUM] = gGlobal._RS->mGetGraph()["UI_skill_vacuum"]._handle;
	_uiWeaponIcon[0] = gGlobal._RS->mGetGraph()["UI_weapon_sword"]._handle;
	_uiWeaponIcon[1] = gGlobal._RS->mGetGraph()["UI_weapon_lockon"]._handle;
	_uiWeaponIcon[2] = gGlobal._RS->mGetGraph()["UI_weapon_lockon"]._handle;
	
}

GameUI::~GameUI()
{
	
}

void GameUI::Process()
{

}

void GameUI::IntervalDraw(std::array<kindDivine, 3> slot)
{
	//�C���^�[�o���摜�̃n���h������
	int cg = gGlobal._RS->mGetGraph()["UI_skill_interval"]._handle;
	//for���Ŏg�����߂�std::tuple�ŕ`��ʒu��������
	std::tuple<int, int, int> pos[3] =
	{
		{1650,1730,880},
		{1560,1640,970},
		{1650,1730,1060}
	};
	//enum��int�ɕϊ�
	int i[3] =
	{
		static_cast<int>(slot[0]),
		static_cast<int>(slot[1]),
		static_cast<int>(slot[2]),
	};
	//�X���b�g�̕������J��Ԃ�
	for (int j = 0; j < 3; j++)
	{
		//�X�L���̍Ĕ����܂ł̃J�E���g���C���^�[�o���J�E���g�Ƃ���
		float interval = static_cast<float>(gGlobal._PM->P_GetSkill()->GetSkill(i[j]).divineCnt);
		//�X�L���Ĕ����t���[���𑍃C���^�[�o���J�E���g�Ƃ���
		float max_interval = gGlobal._PM->P_GetSkill()->GetSkill(i[j]).reInvocationFrame;
		//���������߂�̂�������͋t�̊������g��
		float ratio = 1 - interval / max_interval;
		//�X�L�������t���O��false�Ȃ�
		if (!gGlobal._PM->P_GetSkill()->GetSkill(i[j]).invocationFlag)
		{
			//�摜�̋�`�`��
			DrawExtendGraph(std::get<0>(pos[j]), std::get<2>(pos[j]) - 80 * ratio, std::get<1>(pos[j]), std::get<2>(pos[j]), cg, false);
		}
	}
}

void GameUI::Draw(std::array<kindDivine, 3> slot)
{
	DrawGraph(0, 900, _uiPlHpBarFrame, TRUE);
	for (int i = 0; i < gGlobal._PM->P_GetHp(); i++)
	{
		DrawGraph(55 + i * 2.15, 915, _uiPlHp, TRUE);
	}
	if (GameEvent::GetInstance()->GetEvent() >= 1)
	{
		for (int i = 0; i < EN_Romanoff::GetInstance()->GetHp(); i++)
		{
			DrawGraph(460 + i * 0.23, 60, _uiEnHp, TRUE);
		}
		DrawGraph(450, 50, _uiEnHpBarFrame, TRUE);
	}
	GameEvent::GetInstance()->DrawEventUI();
	GameSystem::GetInstance()->DrawKO();
	//�t���[���̕`��
	DrawGraph(1640, 790, _uiIconFrame[1], TRUE);
	DrawGraph(1550, 880, _uiIconFrame[0], TRUE);
	DrawGraph(1640, 970, _uiIconFrame[2], TRUE);
	DrawGraph(1730, 880, _uiIconFrame[3], TRUE);
	//�A�C�R���̕`��
	DrawGraph(1650, 800, _uiDIcon[slot[0]], TRUE);
	DrawGraph(1560, 890, _uiDIcon[slot[1]], TRUE);
	DrawGraph(1650, 980, _uiDIcon[slot[2]], TRUE);
	DrawGraph(1740, 890, _uiWeaponIcon[0], TRUE);
	IntervalDraw(slot);
	
	
}