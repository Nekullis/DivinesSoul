#pragma once
#include "EnemyManager.h"
#include "SkillSlot.h"
constexpr auto CHANGE_SKILL_COMBO = 30;
class GameSystem
{
public:
	GameSystem();
	virtual ~GameSystem();
	//�C���X�^���X
	static GameSystem* _sysInstance;
	bool Process(EnemyManager* en, SkillSlot* slot, int lasttrg);
	bool Render();
public:
	//���j���Ɋւ���v���Z�X
	void KOProcess(EnemyManager* en, SkillSlot* slot, int lasttrg);
	void DrawKO();
	//�Q�b�^�[
	static GameSystem* GetInstance(){ return _sysInstance; }
protected:
	int _ko;
	bool _koSlot;
};
