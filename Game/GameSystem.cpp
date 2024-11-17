#include "GameSystem.h"
GameSystem* GameSystem::_sysInstance = nullptr;
GameSystem::GameSystem()
{
	_sysInstance = this;
	_koSlot = false;
	_ko = 0;
}

GameSystem::~GameSystem()
{

}

void GameSystem::KOProcess(EnemyManager* en, SkillSlot* slot, int lasttrg)
{
	_ko = en->GetCombo();
	if (_ko >= CHANGE_SKILL_COMBO)
	{
		_koSlot = true;
		en->SetCombo(0);
	}
	if (_koSlot)
	{
		int trg = lasttrg;
		SoundItemBase* snditem_se = gGlobal._sndServer.Get("SE_Slot_Start");
		snditem_se->Play();
		slot->SlotSpin(trg);
		if (!slot->GetSpin())
		{
			_koSlot = false;
		}
	}
}

bool GameSystem::Process(EnemyManager* en, SkillSlot* slot, int lasttrg)
{
	KOProcess(en,slot,lasttrg);
	return true;
}

void GameSystem::DrawKO()
{
	int x = 1600;
	int ko = _ko;
	int loop_cnt = 0;
	while (1)
	{
		int cg = gGlobal._RS->mGetDivGraph()["combo_number"].handle[ko % 10];
		DrawGraph(x, 600, cg, true);
		ko /= 10;
		x -= 60;
		loop_cnt++;
		if (loop_cnt >= 2) { break; }
	}
	int ko_slash = gGlobal._RS->mGetGraph()["KO_slash"]._handle;
	DrawGraph(1640, 630, ko_slash, true);
	int max_ko[2] =
	{
		gGlobal._RS->mGetDivGraph()["combo_number"].handle[CHANGE_SKILL_COMBO % 10],
		gGlobal._RS->mGetDivGraph()["combo_number"].handle[CHANGE_SKILL_COMBO / 10]
	};
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(1730 - (60 * i), 660, max_ko[i], true);
	}
	int ko_hundle = gGlobal._RS->mGetGraph()["KO"]._handle;
	DrawGraph(1790, 700, ko_hundle, true);
}

bool GameSystem::Render()
{
	DrawKO();
	return true;
}


