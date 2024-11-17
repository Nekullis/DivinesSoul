#pragma once
#include "Player.h"
// �v���C���[�Ɋւ������ێ����A������v���C���[�ɓK�p����N���X�i��F�~������ɂ�����K�`���Ȃǁj���[�h�T�[�o�[�ɓo�^���ĕs�v�Ȏ��͎~�߂Ă����������H
// �܂��X�e�[�W�ɂ�����v���C���[�̌Ăяo�����s��(�K�`���Ȃǂ̖{�ҊO�̃X�e�[�^�X�����Z���ČĂяo��)

class PlayerManager
{public:
	PlayerManager();
	virtual ~PlayerManager();
	void Initialize();
	void Process();
	void Render(); // �v���C���[�`��܂ށA�����f�o�b�O����`�悷��̂ł���΂܂Ƃ߂�
	void DebugRender();
public:
	//�v���C���[�N���X���玝���Ă����������K�w���グ�ă}�l�[�W���[���璼�Ɏg����悤�ɂ��Ă���
	void P_Materialize(); // �Q�[���{�҂ɓ����Ă����Ƃ��A�v���C���[���o��������E����܂łɎ󂯎�������l�ŏ�����
	void P_Delete();
	void P_Initialize(int handle, int weapon);
	void P_Process(int trg, int key, int rel, VECTOR campos, VECTOR camtarget,SkillSlot* slot);
	//void P_Gravity();
	void P_Move(int key, VECTOR campos, VECTOR camtarget);
	void P_Action(int trg);
	void P_AnimProcess();
	void P_CalcuProcess();
	void P_ActionProcerss(int trg, int key, int rel, VECTOR campos, VECTOR camtarget,SkillSlot* slot);
	void P_Damage(VECTOR pos,int subpoint);
	// �����_�[�͒��Ƀ}�l�[�W���[�̃����_�[�ɓ\���Ă܂�
	//�ʂɂƂ邩���̂łƂ邩�͔Y�ݒ�
	Player* P_Get() { return _pl; }
	////////////////////////////////////////
	VECTOR P_GetMove() { return _pl->GetMove(); }
	VECTOR P_GetPos() { return _pl->GetPos(); }
	VECTOR P_GetDir() { return _pl->GetDir(); }
	Divine* P_GetSkill() { return _pl->GetDivine(); }
	int P_GetHp() { return _pl->GetHp(); }
	bool P_GetDie() { return _pl->GetGameOver(); }
	int P_GetCommand() { return _pl->GetLastCommand(); }
	void P_SetPos(VECTOR any) { _pl->SetPos(any); }
	void P_SetPos_y(float y) { _pl->SetPos_y(y); }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	Player* _pl;
};

