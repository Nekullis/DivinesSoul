#pragma once
#include "appframe.h"
#include "ApplicationGlobal.h"
#include "EnumInfo.h"
#include "Player.h"
class GameUI
{
public:
	GameUI();
	virtual ~GameUI();
	void Process();
	void IntervalDraw(std::array<kindDivine, 3> slot);
	void Draw(std::array<kindDivine, 3> slot);
protected:
	int _uiPlHp;
	int _uiPlHpBarFrame;
	int _uiEnHp;
	int _uiEnHpBarFrame;
	int _uiSkillIcon[7];
	std::unordered_map<kindDivine, int> _uiDIcon;
	int _uiWeaponIcon[3];
	int _uiIconFrame[4];
};

